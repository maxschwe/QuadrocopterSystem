from collections import deque
import math
from pathlib import Path
import threading
import time
import pandas as pd

from telemetry_data import TelemetryData
from helpers import format_ms


class TelemetryHandler:
    def __init__(self, deque_size=1000):
        self._telemetry_data = deque(maxlen=deque_size)

        self._lock = threading.Lock()

        self._recordings = []

    def start_recording(self, length_s: float, save_loc: Path | None = None, on_finish=None):
        def record():
            recording_telemetry = []
            with self._lock:
                self._recordings.append(recording_telemetry)

            time.sleep(length_s)

            with self._lock:
                self._recordings.remove(recording_telemetry)

            df = pd.DataFrame(recording_telemetry)
            if save_loc is not None:
                df.to_csv(save_loc, index=False)
            if on_finish is not None:
                on_finish(df)

        thread = threading.Thread(target=record)
        thread.start()

    def add(self, telemetry: TelemetryData):
        self._telemetry_data.append(telemetry)

        with self._lock:
            for recording in self._recordings:
                recording.append(telemetry)

        print(f"Time: {format_ms(telemetry.time_ms)}\t Roll: {math.degrees(telemetry.roll):.8f}\t Roll Rate: {math.degrees(telemetry.roll_rate):.8f}")

    def get_queue_data(self):
        return pd.DataFrame(self._telemetry_data)
