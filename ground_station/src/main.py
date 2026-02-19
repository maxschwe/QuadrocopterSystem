from gui import Gui
import serial

if __name__ == "__main__":
    with serial.Serial('COM4', 921600, timeout=1) as ser:        
        app = Gui(ser)
        app.mainloop()
