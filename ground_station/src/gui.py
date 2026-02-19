import time
import threading
import tkinter as tk
from tkinter import ttk
import matplotlib

from com import Com
from telemetry_handler import TelemetryHandler
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import numpy as np


MAX_POINTS = 2000
INITIAL_THROTTLE = 3.0
INITIAL_PID = (1.2, 0.5, 2.0)


def plot(df, ax, canvas):
    ax.clear()
    if not df.empty:
        ax.plot(df['times'], df['roll'], label='Roll')
        ax.plot(df['times'], df['roll_rate'], label='Roll Rate')
        ax.set_ylim(-30, 30)
        ax.legend(loc='upper right')
        ax.set_xlabel("Time (ms)")
        ax.set_ylabel("Value")
        
    canvas.draw()


class Gui(tk.Tk):
    _lock = threading.Lock()

    def __init__(self, ser):
        super().__init__()
        self.ser = ser

        self._telemetry_handler = TelemetryHandler()
        self._trajectories = self.trajectories()

        self._com = Com(ser, self._telemetry_handler)

        # starts receiver thread
        self._com.start()

        self._com.set_throttle(INITIAL_THROTTLE)
        self._com.set_pid(*INITIAL_PID)

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

        # Trajectory Selection
        ttk.Label(control_frame, text="Trajectory:").pack(side=tk.LEFT, padx=10)
        self.traj_var = tk.StringVar()
        self.traj_combo = ttk.Combobox(control_frame, textvariable=self.traj_var, values=list(self._trajectories.keys()))
        self.traj_combo.current(0)
        self.traj_combo.pack(side=tk.LEFT, padx=5)

        # Recording Time
        ttk.Label(control_frame, text="Recording Time:").pack(side=tk.LEFT)
        self.recording_time_var = tk.DoubleVar(value=20.0)
        self.recording_time_scale = ttk.Scale(control_frame, from_=0, to=60, variable=self.recording_time_var)
        self.recording_time_scale.pack(side=tk.LEFT, fill=tk.X, expand=True, padx=5)
        self.recording_time_label = ttk.Label(control_frame, textvariable=self.recording_time_var)
        self.recording_time_label.pack(side=tk.LEFT, padx=5)   
        
        # Start Recording Button
        self.start_recording_btn = ttk.Button(control_frame, text="Start Recording", command=lambda: self.after(0, self.run_trajectory))
        self.start_recording_btn.pack(side=tk.LEFT, padx=5)

        # --- Plot Frame ---
        plot_frame = ttk.Frame(self)
        plot_frame.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
        
        self.fig = Figure(figsize=(8, 6), dpi=100)
        self.ax = self.fig.add_subplot(111)
        
        self.canvas = FigureCanvasTkAgg(self.fig, master=plot_frame)
        self.canvas.draw()
        self.canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)
        
        # Start update loop
        self.after(50, self.update_plot)

    def trajectories(self):
        def my_sin(t):
            return 5 * np.sin(0.01 * t)
        
        def my_step(t):
            return 5
        
        def my_ramp(t):
            return 0.01 * t

        return {
            "Sine": my_sin,
            "Step": my_step,
            "Ramp": my_ramp
        }

    def run_trajectory(self):
        traj_type = self.traj_var.get()
        traj_record_time = self.recording_time_var.get()

        traj_func = self._trajectories.get(traj_type)
        if traj_func is None:
            print(f"Unknown trajectory type: {traj_type}")
            return

        print(f"Starting {traj_type} trajectory...")
        start_time = time.time()
        self._telemetry_handler.start_recording(traj_record_time, on_finish=self.show_recorded_data)
        
        while (time.time() - start_time) < traj_record_time:
            elapsed_s = int((time.time() - start_time))
            target_value = traj_func(elapsed_s)

            target_value_rads = np.radians(target_value)

            self._com.set_reference_roll(target_value_rads)
            time.sleep(0.01)

    def show_recorded_data(self, df):
        top = tk.Toplevel(self)
        top.title("Recorded Trajectory Data")
        
        fig = Figure(figsize=(8, 6), dpi=100)
        ax = fig.add_subplot(111)

        canvas = FigureCanvasTkAgg(fig, master=top)
        plot(df, ax, canvas)

        canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

    def update_plot(self):
        df = self._telemetry_handler.get_queue_data()

        self.ax.clear()
        self.ax.set_title("Live Drone Data")
        plot(df, self.ax, self.canvas)

        self.after(100, self.update_plot)
