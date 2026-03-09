from collections import deque
from pathlib import Path
import threading
import time
import pandas as pd

from telemetry_data import TelemetryData3dof, TelemetryData6dof
from helpers import format_ms


class TelemetryHandler:
    def __init__(self, deque_size=1000):
        self._telemetry_data = deque(maxlen=deque_size)

        self._lock_recordings = threading.Lock()
        self._lock_deque = threading.Lock()

        self._recordings = []

    def start_recording(self, length_s: float, save_loc: Path | None = None, on_finish=None):
        def record():
            recording_telemetry = []
            with self._lock_recordings:
                self._recordings.append(recording_telemetry)

            time.sleep(length_s)

            with self._lock_recordings:
                self._recordings.remove(recording_telemetry)

            df = pd.DataFrame(recording_telemetry)
            if save_loc is not None:
                df.to_csv(save_loc, index=False)
            if on_finish is not None:
                on_finish(df)

        thread = threading.Thread(target=record)
        thread.start()

    def add(self, telemetry: TelemetryData3dof | TelemetryData6dof):
        with self._lock_deque:
            self._telemetry_data.append(telemetry)

        with self._lock_recordings:
            for recording in self._recordings:
                recording.append(telemetry)

        # print(f"Time: {format_ms(telemetry.time_ms)}\t X: {telemetry.x:.2f} m\t Y: {telemetry.y:.2f} m\t Z: {telemetry.z:.2f} m \t T1: {telemetry.throttle_1:.2f}\t T2: {telemetry.throttle_2:.2f}\t T3: {telemetry.throttle_3:.2f}\t T4: {telemetry.throttle_4:.2f}")

    def get_queue_data(self):
        with self._lock_deque:
            return pd.DataFrame(self._telemetry_data)
