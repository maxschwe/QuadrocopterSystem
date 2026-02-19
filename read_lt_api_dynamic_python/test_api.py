from api_lasertracker import ltpy
import time

def my_meas_callback(meas_result: ltpy.MeasurementResult):
    print(meas_result.error_code)
    point = {"x": meas_result.measured_point.x, "y": meas_result.measured_point.y, "z": meas_result.measured_point.z}
    print(point)


dev = ltpy.LaserTrackerInterface()
ret = dev.connect("192.168.0.168")

if ret != ltpy.ErrorType.Success:
    msg = dev.get_error_message(ret)
    print ('Connection Failed: {}'.format(msg))

info = dev.get_device_information()
version = dev.get_sdk_version_number()
print (f'Model: {info.device_model}\\nSerial Number: {info.serial_number}\\nDevice Firmware Version: {info.device_firmware_version}\\nSDK Version: {version}')

# dev.jog_to(5, -40)
dev.home(ltpy.SmrSize.OneHalfInch)

dev.start_temporal_dynamic_measurement(20, my_meas_callback)
time.sleep(30)
dev.stop_measurement()


dev.disconnect()
