import pandas as pd
from pathlib import Path
import tkinter as tk

from plots import show_new_recording_plot


if __name__ == "__main__":
    PATH = Path("../evaluation_recordings/pid_pitch_1.42-1.21-0.35_throttle_3_mse2.96.csv")
    
    df = pd.read_csv(PATH)

    root = tk.Tk()
    show_new_recording_plot(root, df)
    root.mainloop()
