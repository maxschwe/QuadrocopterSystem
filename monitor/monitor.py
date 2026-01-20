import serial
import datetime

with serial.Serial('COM4', 115200, timeout=1) as ser:
    while True:
        line = ser.readline()
        if line:
            timestamp = datetime.datetime.now().strftime('%H:%M:%S.%f')[:-3]
            print(f'[{timestamp}] {line.decode().strip()}')
