import numpy as np
import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.figure import Figure
import tkinter as tk

PLOT_CONFIGS = [
    # {
    #     "title": "Roll Data",
    #     "ylabel": "Angle (deg)",
    #     "plot_func": lambda df, ax: (
    #         ax.plot(df['time_ms'], np.rad2deg(df['roll']), label='Roll'),
    #         ax.plot(df['time_ms'], np.rad2deg(df['reference_roll']), label='Roll Target'),
    #         ax.plot(df['time_ms'], np.rad2deg(df['roll_predicted']), label='Roll Predicted'),
    #         ax.plot(df['time_ms'], np.rad2deg(df['value1']), label='Roll Rate Integrated'),
    #         ax.text(0.5, 0.95, f"MSE: {np.mean((np.rad2deg(df['roll']) - np.rad2deg(df['reference_roll']))**2):.2f}", 
    #                 transform=ax.transAxes, ha="center", va="top"),
    #         ax.legend(loc='upper right')
    #     )
    # },
    # {
    #     "title": "Pitch Data",
    #     "ylabel": "Angle (deg)",
    #     "plot_func": lambda df, ax: (
    #         ax.plot(df['time_ms'], np.rad2deg(df['pitch']), label='Pitch'),
    #         ax.plot(df['time_ms'], np.rad2deg(df['reference_pitch']), label='Pitch Target'),
    #         ax.plot(df['time_ms'], np.rad2deg(df['pitch_predicted']), label='Pitch Predicted'),
    #         ax.text(0.5, 0.95, f"MSE: {np.mean((np.rad2deg(df['pitch']) - np.rad2deg(df['reference_pitch']))**2):.2f}", 
    #                 transform=ax.transAxes, ha="center", va="top"),
    #         ax.legend(loc='upper right')
    #     )
    # },
    # {
    #     "title": "Yaw Data",
    #     "ylabel": "Angle (deg)",
    #     "plot_func": lambda df, ax: (
    #         ax.plot(df['time_ms'], np.rad2deg(df['yaw']), label='Yaw'),
    #         ax.plot(df['time_ms'], np.rad2deg(df['reference_yaw']), label='Yaw Target'),
    #         ax.plot(df['time_ms'], np.rad2deg(df['yaw_predicted']), label='Yaw Predicted'),
    #         ax.text(0.5, 0.95, f"MSE: {np.mean((np.rad2deg(df['yaw']) - np.rad2deg(df['reference_yaw']))**2):.2f}", 
    #                 transform=ax.transAxes, ha="center", va="top"),
    #         ax.legend(loc='upper right')
    #     )
    # },
    # {
    #     "title": "Roll Rate Data",
    #     "ylabel": "Anglerate (deg/s)",
    #     "plot_func": lambda df, ax: (
    #         ax.plot(df['time_ms'], np.rad2deg(df['value4']), label='Roll Rate'),
    #         ax.legend(loc='upper right')
    #     )
    # },
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
    },
    {
        "title": "Pos X",
        "ylabel": "X (m)",
        "plot_func": lambda df, ax: (
            ax.plot(df['time_ms'], df['x'], label='X'),
            ax.plot(df['time_ms'], df['reference_x'], label='X Target'),
            
            ax.legend(loc='upper right')
        )
    },
    {
        "title": "Pos Y",
        "ylabel": "Y (m)",
        "plot_func": lambda df, ax: (
            ax.plot(df['time_ms'], df['y'], label='Y'),
            ax.plot(df['time_ms'], df['reference_y'], label='Y Target'),
            
            ax.legend(loc='upper right')
        )
    },
    {
        "title": "Pos Z",
        "ylabel": "Z (m)",
        "plot_func": lambda df, ax: (
            ax.plot(df['time_ms'], df['z'], label='Z'),
            ax.plot(df['time_ms'], df['reference_z'], label='Z Target'),
            
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

def show_new_recording_plot(root, df):
    root.title("Recorded Trajectory Data")
        
    fig = Figure(figsize=(8, 8), dpi=100)
    axes = setup_subplots(fig)

    canvas = FigureCanvasTkAgg(fig, master=root)
    plot(df, axes, canvas)

    canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)
