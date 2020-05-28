import wiringpi as wpi
import time
wpi.wiringPiSetup()
wpi.pinMode(15, 1)
wpi.pinMode(16, 1)
while True:
    wpi.digitalWrite(15, 1)
    wpi.digitalWrite(16, 1)
    time.sleep(1)
    wpi.digitalWrite(15, 0)
    wpi.digitalWrite(16, 0)
    time.sleep(1)
