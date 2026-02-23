import time

from gui import Gui
import serial

if __name__ == "__main__":
    with serial.Serial('COM4', 921600, timeout=1) as ser:
        time.sleep(2)  # Wait for serial connection to initialize        
        app = Gui(ser)
        app.mainloop()
