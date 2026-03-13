import pandas as pd
from pathlib import Path
import tkinter as tk

from plots import show_new_recording_plot


if __name__ == "__main__":
    PATH = Path(r"../recordings/Test1/trajectory_30s Benchmark_Roll_1773395325.csv")
    
    df = pd.read_csv(PATH)

    root = tk.Tk()
    show_new_recording_plot(root, df)
    root.mainloop()
