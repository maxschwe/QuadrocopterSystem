import serial
import threading

from telemetry_data import TelemetryData

class Com(threading.Thread):
    def __init__(self, ser: serial.Serial, telemetry_handler):
        super().__init__()
        self.ser = ser
        self.telemetry_handler = telemetry_handler

    def send_cmd(self, cmd, values: float | list[float]):
        if isinstance(values, list):
            val_str = ",".join(map(str, values))
        else:
            val_str = str(values)
        full_cmd = f"#{cmd};{val_str}\n"
        self.ser.write(full_cmd.encode())

    def set_throttle(self, value: float):
        self.send_cmd("TT", value)

    def set_pid(self, p: float, i: float, d: float):
        self.send_cmd("PID", [p, i, d])

    def set_reference_roll(self, value: float):
        self.send_cmd("TR", value)

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
            telemetry_data = TelemetryData(
                time_ms,
                *data
            )
            self.telemetry_handler.add(telemetry_data)
