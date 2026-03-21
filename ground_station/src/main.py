import time
from api_lasertracker import ltpy

from gui import Gui
import serial

IN_6DOF_MODE = True
PID_ROT_ACTIVE = True
PID_POS_ACTIVE = True

def activate_lasertracker():
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

    return dev

if __name__ == "__main__":
    try:
        if IN_6DOF_MODE:
            dev = activate_lasertracker()
        else:
            dev = None

        with serial.Serial('COM4', 921600, timeout=1) as ser:
            time.sleep(2)  # Wait for serial connection to initialize        
            app = Gui(ser, dev, IN_6DOF_MODE, PID_ROT_ACTIVE, PID_POS_ACTIVE)
            app.mainloop()
    finally:
        if dev:
            dev.disconnect()
