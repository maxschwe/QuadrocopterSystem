import pandas as pd
from pathlib import Path
import tkinter as tk

from plots import show_new_recording_plot


if __name__ == "__main__":
    PATH = Path(r"../evaluation_recordings/lqr_yz.csv")
    
    df = pd.read_csv(PATH)

    root = tk.Tk()
    show_new_recording_plot(root, df, in_6dof_mode=True)
    root.mainloop()
