import time

from api_lasertracker import ltpy
import serial
import threading

from helpers import Axis
from telemetry_data import TelemetryData3dof, TelemetryData6dof

class Com(threading.Thread):
    def __init__(self, ser: serial.Serial, telemetry_handler, in_6dof_mode: bool):
        super().__init__()
        self.ser = ser
        self.telemetry_handler = telemetry_handler
        self._in_6dof_mode = in_6dof_mode

        self._start_time = time.time()

        self._lock = threading.Lock()

    def send_cmd(self, cmd, values: float | list[float]):
        if isinstance(values, list):
            val_str = ",".join(map(str, values))
        else:
            val_str = str(values)
        full_cmd = f"#{cmd};{val_str}\n"

        with self._lock:
            self.ser.write(full_cmd.encode())

    def set_thrust(self, value: float):
        self.send_cmd("RT", value)

    def set_reference(self, value1: float, value2: float, value3: float):
        self.send_cmd("R", [value1, value2, value3])

    def set_pid(self, axis: Axis, p: float, i: float, d: float):
        axis_code = {Axis.ROLL: "R", Axis.PITCH: "P", Axis.YAW: "Y", Axis.X: "x", Axis.Y: "y", Axis.Z: "z"}[axis]

        self.send_cmd(f"{axis_code}PID", [p, i, d])

    def update_position(self, meas_result: ltpy.MeasurementResult):
        try:
            if meas_result.error_code != ltpy.ErrorType.Success:
                print("Measurement error: {}".format(meas_result.error_code))
                return

            x = meas_result.measured_point.x
            y = meas_result.measured_point.y
            z = meas_result.measured_point.z

            # print(f"{format_ms((time.time() - self._start_time) * 1000)}: Updating position: x={x}, y={y}, z={z}")

            self.send_cmd("P", [x / 1000, y / 1000, z / 1000])  # Convert mm to m
        except Exception as e:
            print(f"Error in update_position: {e}")

    def run(self):
        while True:
            line = self.ser.readline()
            try:
                line = line.decode('utf-8').strip()
            except Exception:
                print("Failed to decode line from serial")
                continue
            
            if not line.startswith("#"):
                print(line)
                continue

            line = line[1:]
            data = line.split("\t")
            if len(data) < 5:
                print(f"Unexpected data format: {line}")
                continue

            time_ms = int(data[0])

            data = map(float, data[1:])
            if self._in_6dof_mode:
                telemetry_data = TelemetryData6dof(
                    time_ms,
                    *data
                )
            else:
                telemetry_data = TelemetryData3dof(
                    time_ms,
                    *data
                )
            self.telemetry_handler.add(telemetry_data)
