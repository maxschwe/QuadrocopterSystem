import pandas as pd
from pathlib import Path
import tkinter as tk

from plots import show_new_recording_plot


if __name__ == "__main__":
    PATH = Path("../evaluation_recordings/pid_roll_1.4-1.18-0.33_throttle3_mse3.01.csv")
    
    df = pd.read_csv(PATH)

    root = tk.Tk()
    show_new_recording_plot(root, df)
    root.mainloop()
