import math
import tkinter as tk
from tkinter import ttk
from tkinter import scrolledtext
import serial
import threading
import datetime
import sys
import time
import matplotlib
matplotlib.use("TkAgg")
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Default configuration
DEFAULT_PORT = 'COM4'
BAUD_RATE = 921600

class DroneMonitorApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Drone Monitor & PID Tuner")
        self.root.geometry("900x700")

        self.serial_port = None
        self.reading_thread = None
        self.running = False
        
        self.is_recording = False
        self.log_file = None
        self.recording_trajectory_type = ""
        self.recorded_data = []
        self.record_start_time = None
        self.record_amplitude = 10.0
        self.record_frequency = 0.2

        # --- Connection Frame ---
        conn_frame = ttk.LabelFrame(root, text="Connection")
        conn_frame.pack(fill="x", padx=10, pady=5)

        ttk.Label(conn_frame, text="Port:").pack(side="left", padx=5)
        self.port_entry = ttk.Entry(conn_frame)
        self.port_entry.insert(0, DEFAULT_PORT)
        self.port_entry.pack(side="left", padx=5)

        self.connect_btn = ttk.Button(conn_frame, text="Connect", command=self.toggle_connection)
        self.connect_btn.pack(side="left", padx=5)
        
        self.status_lbl = ttk.Label(conn_frame, text="Disconnected", foreground="red")
        self.status_lbl.pack(side="left", padx=10)

        # --- PID Control Frame ---
        pid_frame = ttk.LabelFrame(root, text="Roll PID Settings")
        pid_frame.pack(fill="x", padx=10, pady=5)

        ttk.Label(pid_frame, text="P:").pack(side="left", padx=5)
        self.p_entry = ttk.Entry(pid_frame, width=10)
        self.p_entry.pack(side="left", padx=5)

        ttk.Label(pid_frame, text="I:").pack(side="left", padx=5)
        self.i_entry = ttk.Entry(pid_frame, width=10)
        self.i_entry.pack(side="left", padx=5)

        ttk.Label(pid_frame, text="D:").pack(side="left", padx=5)
        self.d_entry = ttk.Entry(pid_frame, width=10)
        self.d_entry.pack(side="left", padx=5)

        self.send_pid_btn = ttk.Button(pid_frame, text="Update PID", command=self.send_pid)
        self.send_pid_btn.pack(side="left", padx=10)
        self.send_pid_btn.configure(state="disabled")

        # --- Trajectory / Calibration Frame ---
        traj_frame = ttk.LabelFrame(root, text="Trajectory & Identification")
        traj_frame.pack(fill="x", padx=10, pady=5)

        ttk.Label(traj_frame, text="Type:").pack(side="left", padx=5)
        self.traj_type_var = tk.StringVar(value="Step")
        self.traj_type_combo = ttk.Combobox(traj_frame, textvariable=self.traj_type_var, values=["Step", "Sine"], state="readonly", width=10)
        self.traj_type_combo.pack(side="left", padx=5)

        ttk.Label(traj_frame, text="Amp:").pack(side="left", padx=5)
        self.amp_entry = ttk.Entry(traj_frame, width=5)
        self.amp_entry.insert(0, "10.0")
        self.amp_entry.pack(side="left", padx=5)

        ttk.Label(traj_frame, text="Freq:").pack(side="left", padx=5)
        self.freq_entry = ttk.Entry(traj_frame, width=5)
        self.freq_entry.insert(0, "0.2")
        self.freq_entry.pack(side="left", padx=5)

        self.start_traj_btn = ttk.Button(traj_frame, text="Start Trajectory", command=self.start_trajectory)
        self.start_traj_btn.pack(side="left", padx=10)
        self.start_traj_btn.configure(state="disabled")

        self.error_lbl = ttk.Label(traj_frame, text="Error: N/A")
        self.error_lbl.pack(side="left", padx=10)

        # --- Throttle Control Frame ---
        throttle_frame = ttk.LabelFrame(root, text="Throttle Control")
        throttle_frame.pack(fill="x", padx=10, pady=5)

        self.throttle_val = tk.DoubleVar()
        self.throttle_scale = ttk.Scale(throttle_frame, from_=0, to=10, variable=self.throttle_val, command=self.send_throttle)
        self.throttle_scale.pack(side="left", fill="x", expand=True, padx=5, pady=5)
        
        self.throttle_lbl = ttk.Label(throttle_frame, text="0.0")
        self.throttle_lbl.pack(side="right", padx=5)

        # --- Monitor Output ---
        term_frame = ttk.LabelFrame(root, text="Monitor Output")
        term_frame.pack(fill="both", expand=True, padx=10, pady=5)

        self.terminal = scrolledtext.ScrolledText(term_frame, state='disabled', height=20)
        self.terminal.pack(fill="both", expand=True, padx=5, pady=5)
        
        # Autoscroll checkbox
        self.autoscroll_var = tk.BooleanVar(value=True)
        self.autoscroll_check = ttk.Checkbutton(term_frame, text="Autoscroll", variable=self.autoscroll_var)
        self.autoscroll_check.pack(side="bottom", anchor="w", padx=5)

        # --- Plot Frame ---
        self.plot_frame = ttk.LabelFrame(root, text="Trajectory Plot")
        self.plot_frame.pack(fill="both", expand=True, padx=10, pady=5)
        self.canvas = None

    def toggle_connection(self):
        if not self.running:
            self.connect()
        else:
            self.disconnect()

    def connect(self):
        port = self.port_entry.get()
        try:
            self.serial_port = serial.Serial(port, BAUD_RATE, timeout=1)
            self.running = True
            
            self.connect_btn.configure(text="Disconnect")
            self.status_lbl.configure(text="Connected", foreground="green")
            self.send_pid_btn.configure(state="normal")
            self.start_traj_btn.configure(state="normal")
            
            self.reading_thread = threading.Thread(target=self.read_serial_loop, daemon=True)
            self.reading_thread.start()
            
            self.log_message(f"Connected to {port} at {BAUD_RATE} baud.")
            
        except serial.SerialException as e:
            self.log_message(f"Connection Failed: {e}")
            self.status_lbl.configure(text="Error", foreground="red")

    def disconnect(self):
        self.running = False
        if self.serial_port:
            try:
                self.serial_port.close()
            except Exception:
                pass
            self.serial_port = None
            
        self.connect_btn.configure(text="Connect")
        self.status_lbl.configure(text="Disconnected", foreground="red")
        self.send_pid_btn.configure(state="disabled")
        self.start_traj_btn.configure(state="disabled")
        self.log_message("Disconnected.")

    def read_serial_loop(self):

        while self.running and self.serial_port and self.serial_port.is_open:
            try:
                if self.serial_port.in_waiting:
                    line = self.serial_port.readline()
                    if line:
                        msg = line.decode('utf-8', errors='replace').strip()
                        timestamp = datetime.datetime.now().strftime('%H:%M:%S.%f')[:-3]
                        # print(f"[{timestamp}] {msg}")

                        # Output to terminal only
                        # Data Collection for Trajectory Error
                        if self.is_recording and msg.startswith('#'):
                            if self.log_file:
                                self.log_file.write(f"{msg}\n")

                            # Expected format: #Roll, Pitch, Yaw, RollTarget, ... (tab separated)
                            parts = msg[1:].split('\t')
                            try:
                                roll_meas = float(parts[0])
                                roll_target = float(parts[3])
                                roll_model = float(parts[11])
                                self.recorded_data.append((time.time(), roll_target, roll_meas, roll_model))
                            except ValueError:
                                print(f"[{timestamp}] Data Parse Error: {msg}", flush=True)

                            passed_time = time.time() - self.record_start_time if self.record_start_time else 0

                            FREQUENCY = self.record_frequency # Hz
                            value = self.record_amplitude * math.sin(2 * math.pi * FREQUENCY * passed_time) if self.recording_trajectory_type == "Sine" else self.record_amplitude
                            
                            value_in_radians = math.radians(value)

                            msg = f"#TR;{value_in_radians}\n".encode('utf-8')
                            # print(f"[{timestamp}] Sending: {msg.decode().strip()}", flush=True)

                            self.serial_port.write(msg)
                        else:
                            print(line)
                else:
                    time.sleep(0.01)
            except Exception as e:
                self.root.after(0, self.log_message, f"Read Error: {e}")
                self.root.after(0, self.disconnect)
                break

    def log_message(self, message, is_data=False):
        self.terminal.configure(state='normal')
        if is_data:
            timestamp = datetime.datetime.now().strftime('%H:%M:%S.%f')[:-3]
            self.terminal.insert(tk.END, f"[{timestamp}] {message}\n")
        else:
            self.terminal.insert(tk.END, f"*** {message}\n")
        
        if self.autoscroll_var.get():
            self.terminal.see(tk.END)
        self.terminal.configure(state='disabled')

    def send_pid(self):
        if not self.serial_port or not self.serial_port.is_open:
            return
        
        try:
            p_val = self.p_entry.get()
            i_val = self.i_entry.get()
            d_val = self.d_entry.get()
            
            if not p_val or not i_val or not d_val:
                self.log_message("Error: All PID fields must be filled.")
                return

            p = float(p_val)
            i = float(i_val)
            d = float(d_val)
            
            # Format expected by main.cpp: #PID;p,i,d
            # Using formatting to ensure significant digits if needed, though default float str is usually fine
            cmd = f"#PID;{p},{i},{d}\n"
            
            self.serial_port.write(cmd.encode('utf-8'))
            self.log_message(f"Sent: {cmd.strip()}")
            
        except ValueError:
            self.log_message("Error: PID values must be valid numbers")
        except Exception as e:
            self.log_message(f"Error sending PID: {e}")

    def send_throttle(self, val):
        try:
            val_float = float(val)
            self.throttle_lbl.configure(text=f"{val_float:.1f}")
            if self.serial_port and self.serial_port.is_open:
                cmd = f"#TT;{val_float:.2f}\n"
                self.serial_port.write(cmd.encode('utf-8'))
        except Exception:
            pass

    def start_trajectory(self):
        if not self.serial_port or not self.serial_port.is_open:
            return
        
        try:
            self.recording_trajectory_type = self.traj_type_var.get()
            self.record_amplitude = float(self.amp_entry.get())
            self.record_frequency = float(self.freq_entry.get())

             # Start Recording State
            self.recorded_data = []
            self.record_start_time = time.time()
            self.start_traj_btn.configure(state="disabled")
            self.error_lbl.configure(text="Error: Recording...")
            
            # Open Log File
            try:
                filename = f"recordings/log_{datetime.datetime.now().strftime('%Y%m%d_%H%M%S')}_{self.recording_trajectory_type}.txt"
                self.log_file = open(filename, 'w')
                self.log_message(f"Logging to {filename}")
            except Exception as e:
                self.log_message(f"Failed to open log file: {e}")
            self.is_recording = True

            self.log_message(f"Started Trajectory: {self.recording_trajectory_type}")


            # Schedule Stop
            self.root.after(int(20 * 1000), self.finish_trajectory)
            
        except ValueError:
            self.log_message("Error: Invalid trajectory parameters.")

    def finish_trajectory(self):
        self.is_recording = False
        self.log_file.close()
        self.log_file = None
        self.start_traj_btn.configure(state="normal")
        
        if not self.recorded_data:
            self.error_lbl.configure(text="Error: No Data")
            self.log_message("Trajectory finished but received no data.")
            return

        # Calculate Integral Absolute Error (IAE)
        total_error = 0.0
        
        # Simple integration: sum(|error|) * dt
        # Assuming roughly constant sampling, or using timestamps
        
        if len(self.recorded_data) > 1:
            for i in range(1, len(self.recorded_data)):
                t0, ref0, meas0, model0 = self.recorded_data[i-1]
                t1, ref1, meas1, model1 = self.recorded_data[i]
                
                dt = t1 - t0
                # Trapezoidal approx for error? Or just rect at i?
                # err = ref - meas
                err = abs(ref1 - meas1) 
                total_error += err * dt
                
            self.error_lbl.configure(text=f"IAE: {total_error:.4f}")
            self.log_message(f"Trajectory Finished. Integral Absolute Error (IAE): {total_error:.4f}")
            self.update_plot()
        else:
            self.error_lbl.configure(text="Error: Insufficient Data")
            self.log_message("Trajectory finished. Not enough samples for error calc.")

    def update_plot(self):
        if self.canvas:
            self.canvas.get_tk_widget().destroy()
            self.canvas = None

        if not self.recorded_data:
            return

        # Prepare Data
        times = [d[0] - self.recorded_data[0][0] for d in self.recorded_data]
        targets = [d[1] for d in self.recorded_data]
        measured = [d[2] for d in self.recorded_data]
        modeled = [d[3] for d in self.recorded_data]

        # Create Plot
        fig = Figure(figsize=(5, 3), dpi=100)
        ax = fig.add_subplot(111)
        ax.plot(times, targets, label='Target', linestyle='--', color='orange')
        ax.plot(times, measured, label='Measured', color='blue')
        ax.plot(times, modeled, label='Modeled', color='green')
        
        ax.set_title(f"Trajectory: {self.recording_trajectory_type}")
        ax.set_xlabel('Time (s)')
        ax.set_ylabel('Value')
        ax.legend()
        ax.grid(True)
        fig.tight_layout()

        # Embed in Tkinter
        self.canvas = FigureCanvasTkAgg(fig, master=self.plot_frame)
        self.canvas.draw()
        self.canvas.get_tk_widget().pack(fill="both", expand=True)

if __name__ == "__main__":
    root = tk.Tk()
    app = DroneMonitorApp(root)
    root.mainloop()
