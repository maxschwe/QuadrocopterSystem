from dataclasses import dataclass

@dataclass(slots=True)
class TelemetryData:
    time_ms: int

    roll: float
    pitch: float
    yaw: float

    x: float
    y: float
    z: float

    reference_roll: float
    reference_pitch: float
    reference_yaw: float
    reference_throttle: float

    throttle_1: float
    throttle_2: float
    throttle_3: float
    throttle_4: float

    roll_predicted: float
    pitch_predicted: float
    yaw_predicted: float
    roll_rate_predicted: float
    pitch_rate_predicted: float
    yaw_rate_predicted: float

    value1: float
    value2: float
    value3: float
    value4: float
    value5: float
    value6: float
