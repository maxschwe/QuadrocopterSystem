import time
from api_lasertracker import ltpy

from gui import Gui
import serial

if __name__ == "__main__":
    try:
        dev = ltpy.LaserTrackerInterface()
        ret = dev.connect("192.168.0.168")

        if ret != ltpy.ErrorType.Success:
            msg = dev.get_error_message(ret)
            print ('Connection Failed: {}'.format(msg))

        info = dev.get_device_information()
        version = dev.get_sdk_version_number()
        print (f'Model: {info.device_model}\\nSerial Number: {info.serial_number}\\nDevice Firmware Version: {info.device_firmware_version}\\nSDK Version: {version}')
        # dev.jog_to(5, -40)
        # dev.home(ltpy.SmrSize.OneHalfInch)

        ret = dev.enable_camera_search(enable = True)
        if ret != ltpy.ErrorType.Success:
            msg = dev.get_error_message(ret)
            print (f'Camera Search Failed: {msg}')
        else:
            print ('Camera Search enabled')

        with serial.Serial('COM4', 921600, timeout=1) as ser:
            time.sleep(2)  # Wait for serial connection to initialize        
            app = Gui(ser, dev)
            app.mainloop()
    finally:
        dev.disconnect()
