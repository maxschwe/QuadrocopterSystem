import math
from pathlib import Path
import time
import threading
import tkinter as tk
from tkinter import ttk

import numpy as np

from com import Com
from telemetry_handler import TelemetryHandler
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
from plots import show_new_recording_plot, setup_subplots, plot


MAX_POINTS = 2000
INITIAL_THROTTLE = 0.0
INITIAL_PID = (1.4, 1.18, 0.33)


class Gui(tk.Tk):
    def __init__(self, ser, dev):
        super().__init__()
        self.ser = ser
        self.dev = dev

        self._telemetry_handler = TelemetryHandler()
        self._trajectories = self.trajectories()
        self._multi_trajectories = self.multi_trajectories()

        self._com = Com(ser, self._telemetry_handler)

        # starts receiver thread
        self._com.start()

        self._com.set_pid(*INITIAL_PID)
        self.dev.start_temporal_dynamic_measurement(20, self._com.update_position)
        self._com.set_throttle(INITIAL_THROTTLE)

        self.setup_ui()

    def setup_ui(self):
        self.title("Drone Monitor")

        # --- Control Frame ---
        control_frame = ttk.Frame(self)
        control_frame.pack(side=tk.TOP, fill=tk.X, padx=5, pady=5)
        
        # Throttle
        def update_throttle(_):
            value = self.throttle_var.get()
            self._com.set_throttle(value)

        ttk.Label(control_frame, text="Throttle:").pack(side=tk.LEFT)
        self.throttle_var = tk.DoubleVar(value=INITIAL_THROTTLE)
        self.throttle_scale = ttk.Scale(control_frame, from_=0, to=10, variable=self.throttle_var, command=update_throttle)
        self.throttle_scale.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=5)
        self.throttle_label = ttk.Label(control_frame, textvariable=self.throttle_var)
        self.throttle_label.pack(side=tk.LEFT, padx=5)

        # Axis Selection
        def update_traj_options(_):
            axis = self.axis_var.get()
            if axis == "All Axis":
                self.traj_combo['values'] = list(self._multi_trajectories.keys())
                self.traj_combo.current(0)
            else:
                self.traj_combo['values'] = list(self._trajectories.keys())
                self.traj_combo.current(0)

        ttk.Label(control_frame, text="Axis:").pack(side=tk.LEFT, padx=10)
        self.axis_var = tk.StringVar(value="Roll")
        self.axis_combo = ttk.Combobox(control_frame, textvariable=self.axis_var, values=["Roll", "Pitch", "Yaw", "All Axis"])
        self.axis_combo.current(0)
        self.axis_combo.pack(side=tk.LEFT, padx=5)
        self.axis_combo.bind("<<ComboboxSelected>>", update_traj_options)     

        # Trajectory Selection
        ttk.Label(control_frame, text="Trajectory:").pack(side=tk.LEFT, padx=10)
        self.traj_var = tk.StringVar()
        self.traj_combo = ttk.Combobox(control_frame, textvariable=self.traj_var, values=list(self._trajectories.keys()))
        self.traj_combo.current(0)
        self.traj_combo.pack(side=tk.LEFT, padx=5)

        # Recording Time
        ttk.Label(control_frame, text="Recording Time:").pack(side=tk.LEFT)
        self.recording_time_var = tk.DoubleVar(value=30.0)
        self.recording_time_scale = ttk.Scale(control_frame, from_=0, to=60, variable=self.recording_time_var)
        self.recording_time_scale.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=5)
        self.recording_time_label = ttk.Label(control_frame, textvariable=self.recording_time_var)
        self.recording_time_label.pack(side=tk.LEFT, padx=5)   
        
        # Start Recording Button
        self.start_recording_btn = ttk.Button(control_frame, text="Start Recording", command=self.start_trajectory)
        self.start_recording_btn.pack(side=tk.LEFT, padx=5)

        # --- PID Control Frame ---
        pid_frame = ttk.Frame(self)
        pid_frame.pack(side=tk.TOP, fill=tk.X, padx=5, pady=5)

        def update_pid():
            try:
                p = float(self.p_var.get())
                i = float(self.i_var.get())
                d = float(self.d_var.get())
                self._com.set_pid(p, i, d)
                print(f"PID updated to: P={p}, I={i}, D={d}")
            except ValueError:
                print("Invalid PID values")

        ttk.Label(pid_frame, text="P:").pack(side=tk.LEFT, padx=5)
        self.p_var = tk.StringVar(value=str(INITIAL_PID[0]))
        ttk.Entry(pid_frame, textvariable=self.p_var, width=5).pack(side=tk.LEFT)

        ttk.Label(pid_frame, text="I:").pack(side=tk.LEFT, padx=5)
        self.i_var = tk.StringVar(value=str(INITIAL_PID[1]))
        ttk.Entry(pid_frame, textvariable=self.i_var, width=5).pack(side=tk.LEFT)

        ttk.Label(pid_frame, text="D:").pack(side=tk.LEFT, padx=5)
        self.d_var = tk.StringVar(value=str(INITIAL_PID[2]))
        ttk.Entry(pid_frame, textvariable=self.d_var, width=5).pack(side=tk.LEFT)

        ttk.Button(pid_frame, text="Update PID", command=update_pid).pack(side=tk.LEFT, padx=10)

        # --- Plot Frame ---
        plot_frame = ttk.Frame(self)
        plot_frame.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
        
        self.fig = Figure(figsize=(8, 8), dpi=100)
        self.axes = setup_subplots(self.fig)
        
        self.canvas = FigureCanvasTkAgg(self.fig, master=plot_frame)
        self.canvas.draw()
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)
        
        # Start update loop
        self.after(50, self.update_plot)

    def trajectories(self):
        def my_sin(t):
            return 3 * np.sin(1 * t)
        
        def my_step(t):
            return 3
        
        def my_ramp(t):
            return 0.25 * t
        
        def benchmark_30s(t):
            if t < 5:
                return 0.0
            elif t < 10:
                return 5.0
            elif t < 15:
                return 5.0 - 2 * (t - 10)
            elif t < 25:
                return 5.0 * math.sin(0.2 * (t - 15)**2)
            elif t <= 30:
                return 2.5 * math.cos(math.pi/5 * (t - 25)) + 2.5
            else:
                return 0.0

        return {
            "Sine": my_sin,
            "Step": my_step,
            "Ramp": my_ramp,
            "30s Benchmark": benchmark_30s
        }

    def multi_trajectories(self):
        def sample_multi(t):
            # Roll, Pitch, Yaw
            return (5 * np.sin(t), 5 * np.cos(t), 10 * np.sin(t))

        return {
            "Sample Multi": sample_multi
        }
    
    def start_trajectory(self):
        threading.Thread(target=self.run_trajectory).start()

    def run_trajectory(self):
        traj_type = self.traj_var.get()
        traj_axis = self.axis_var.get()
        traj_record_time = self.recording_time_var.get()

        if traj_axis == "All Axis":
            traj_func = self._multi_trajectories.get(traj_type)
        else:
            traj_func = self._trajectories.get(traj_type)

        if traj_func is None:
            print(f"Unknown trajectory type: {traj_type}")
            return

        print(f"Starting {traj_type} trajectory on {traj_axis}...")
        start_time = time.time()
        save_loc = Path("../recordings") / Path(f"trajectory_{traj_type}_{traj_axis}_{int(start_time)}.csv")
        self._telemetry_handler.start_recording(traj_record_time, save_loc=save_loc, on_finish=self.show_recorded_data)
        
        while (time.time() - start_time) < traj_record_time:
            elapsed_s = time.time() - start_time
            target_value = traj_func(elapsed_s)

            if traj_axis == "All Axis":
                # Ensure target_value is a tuple/list of 3
                if isinstance(target_value, (list, tuple)) and len(target_value) == 3:
                    target_rads = np.radians(target_value)
                    self._com.set_reference_angles(target_rads[0], target_rads[1], target_rads[2])
                else:
                   print(f"Invalid multi-trajectory return: {target_value}")
            else:
                target_value_rads = np.radians(target_value)

                if traj_axis == "Roll":
                    self._com.set_reference_angles(target_value_rads, 0.0, 0.0)
                elif traj_axis == "Pitch":
                    self._com.set_reference_angles(0.0, target_value_rads, 0.0)
                elif traj_axis == "Yaw":
                    self._com.set_reference_angles(0.0, 0.0, target_value_rads * 2)

            # print(f"Setting {traj_type} trajectory: {target_value:.2f} degrees")
            time.sleep(0.0001)

        self._com.set_reference_angles(0.0, 0.0, 0.0)

    def show_recorded_data(self, df):
        top = tk.Toplevel(self)
        show_new_recording_plot(top, df)
        

    def update_plot(self):
        df = self._telemetry_handler.get_queue_data()
        
        plot(df, self.axes, self.canvas)
        self.after(50, self.update_plot)
