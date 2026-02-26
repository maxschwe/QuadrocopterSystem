import math
from pathlib import Path
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
INITIAL_PID = (1.4, 1.18, 0.33)

PLOT_CONFIGS = [
    {
        "title": "Roll Data",
        "ylabel": "Angle (deg)",
        "plot_func": lambda df, ax: (
            ax.plot(df['time_ms'], np.rad2deg(df['roll']), label='Roll'),
            ax.plot(df['time_ms'], np.rad2deg(df['reference_roll']), label='Roll Target'),
            ax.plot(df['time_ms'], np.rad2deg(df['value1']), label='Roll Rate integrated'),
            ax.text(0.5, 0.95, f"MSE: {np.mean((np.rad2deg(df['roll']) - np.rad2deg(df['reference_roll']))**2):.2f}", 
                    transform=ax.transAxes, ha="center", va="top"),
            # ax.set_ylim(-30, 30),
            ax.legend(loc='upper right')
        )
    },
    {
        "title": "Roll Rate Data",
        "ylabel": "Anglerate (deg/s)",
        "plot_func": lambda df, ax: (
            ax.plot(df['time_ms'], np.rad2deg(df['value4']), label='Roll Rate'),
            ax.legend(loc='upper right')
        )
    },
    {
        "title": "Throttles",
        "ylabel": "Throttle",
        "plot_func": lambda df, ax: (
            ax.plot(df['time_ms'], df['throttle_1'], label='Throttle 1'),
            ax.plot(df['time_ms'], df['throttle_2'], label='Throttle 2'),
            ax.plot(df['time_ms'], df['throttle_3'], label='Throttle 3'),
            ax.plot(df['time_ms'], df['throttle_4'], label='Throttle 4'),
            ax.legend(loc='upper right')
        )
    }
]

def setup_subplots(fig):
    axes = []
    num_plots = len(PLOT_CONFIGS)
    for i in range(num_plots):
        # Add subplot: e.g. 211, 212
        ax = fig.add_subplot(num_plots, 1, i + 1)
        axes.append(ax)
    return axes

def plot(df, axes, canvas):
    for i, ax in enumerate(axes):
        ax.clear()
        config = PLOT_CONFIGS[i]
        
        if not df.empty:
            config["plot_func"](df, ax)
            
        ax.set_title(config["title"])
        ax.set_ylabel(config["ylabel"])
        if i == len(axes) - 1:
            ax.set_xlabel("Time (ms)")
        
    canvas.draw()


class Gui(tk.Tk):
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
    
    def start_trajectory(self):
        threading.Thread(target=self.run_trajectory).start()

    def run_trajectory(self):
        traj_type = self.traj_var.get()
        traj_record_time = self.recording_time_var.get()

        traj_func = self._trajectories.get(traj_type)
        if traj_func is None:
            print(f"Unknown trajectory type: {traj_type}")
            return

        print(f"Starting {traj_type} trajectory...")
        start_time = time.time()
        save_loc = Path("../recordings") / Path(f"trajectory_{traj_type}_{int(start_time)}.csv")
        self._telemetry_handler.start_recording(traj_record_time, save_loc=save_loc, on_finish=self.show_recorded_data)
        
        while (time.time() - start_time) < traj_record_time:
            elapsed_s = time.time() - start_time
            target_value = traj_func(elapsed_s)

            target_value_rads = np.radians(target_value)

            self._com.set_reference_roll(target_value_rads)
            print(f"Setting {traj_type} trajectory: {target_value:.2f} degrees")
            time.sleep(0.01)

        self._com.set_reference_roll(0.0)

    def show_recorded_data(self, df):
        top = tk.Toplevel(self)
        top.title("Recorded Trajectory Data")
        
        fig = Figure(figsize=(8, 8), dpi=100)
        axes = setup_subplots(fig)

        canvas = FigureCanvasTkAgg(fig, master=top)
        plot(df, axes, canvas)

        canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)

    def update_plot(self):
        df = self._telemetry_handler.get_queue_data()
        
        plot(df, self.axes, self.canvas)
        self.after(50, self.update_plot)
