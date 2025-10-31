import time
import csv
import serial
from serial.serialutil import SerialException
import pandas as pd
import matplotlib.pyplot as plt

#!/usr/bin/env python3
"""
monitor_drone.py

Read COM/serial port lines that come in the format:
printf("%f,%f,%f\n", ypr[2]*180/M_PI, ypr[1]*180/M_PI, ypr[0]*180/M_PI);
i.e. "yaw,pitch,roll\n" in degrees.

Usage:
    python monitor_drone.py --port COM3 --baud 115200
"""


PORT = "COM17"
BAUD = 115200

def open_serial(port: str, baud: int, timeout: float = 1.0):
    while True:
        try:
            ser = serial.Serial(port=port, baudrate=baud, timeout=timeout)
            print(f"Opened {port} @ {baud} baud")
            return ser
        except SerialException as e:
            print(f"Failed to open {port}: {e}. Retrying in 2s...")
            time.sleep(2)


def parse_line(line: str):
    # Expect "yaw,pitch,roll" (three floats)
    parts = [p.strip() for p in line.split(",")]
    if len(parts) != 3:
        raise ValueError("Line does not have 3 comma-separated values")
    yaw, pitch, roll = map(float, parts)
    return yaw, pitch, roll


def main(filename: str = "measurements.csv"):
    ser = open_serial(PORT, BAUD, timeout=1.0)

    csv_file = open(filename, "w", newline="")
    csv_writer = csv.writer(csv_file)

    start_time = time.time()
    # write header if file was empty
    if csv_file.tell() == 0:
        csv_writer.writerow(
            ["timestamp_iso", "roll_deg", "pitch_deg", "yaw_deg"]
        )
        csv_file.flush()

    try:
        while True:
            try:
                raw = ser.readline()
            except SerialException as e:
                print(f"Serial error: {e}. Reopening port...")
                ser.close()
                ser = open_serial(PORT, BAUD, timeout=1.0)
                continue

            if not raw:
                # timeout, no data
                continue

            line = raw.decode("latin1", errors="replace").strip()

            if not line:
                continue

            try:
                yaw, pitch, roll = parse_line(line)
            except ValueError as ve:
                print(f"Ignored malformed line: {line!r} ({ve})")
                continue

            csv_writer.writerow(
                [
                    f"{time.time() - start_time:.3f}",
                    f"{yaw:.3f}",
                    f"{pitch:.3f}",
                    f"{roll:.3f}",
                ]
            )
            csv_file.flush()

    except KeyboardInterrupt:
        print("Exiting on user request")
    finally:
        try:
            ser.close()
        except Exception:
            pass
        if csv_file:
            csv_file.close()

    plot_csv_data(filename)


def plot_csv_data(filename: str):

    # Load the CSV file
    df = pd.read_csv(filename)


    # Plot yaw, pitch, and roll over time
    plt.figure(figsize=(10, 6))
    plt.plot(df["timestamp_iso"], df["yaw_deg"], label="Yaw (°)")
    plt.plot(df["timestamp_iso"], df["pitch_deg"], label="Pitch (°)")
    plt.plot(df["timestamp_iso"], df["roll_deg"], label="Roll (°)")

    # Add labels, title, legend, and grid
    plt.xlabel("Timestamp")
    plt.ylabel("Angle (degrees)")
    plt.title("Yaw, Pitch, and Roll over Time")
    plt.legend()
    plt.grid(True)
    plt.tight_layout()

    # Show the plot
    plt.show()


if __name__ == "__main__":
    main("measurements_roll/measurements_roll_12N_0.2Nm_2.csv")
    # plot_csv_data("measurements.csv")
