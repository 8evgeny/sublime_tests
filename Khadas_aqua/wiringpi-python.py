import wiringpi as GPIO

INPUT = 0
OUTPUT = 1
OUTPUT_PIN = 17
INPUT_PIN = 16
OUTPUT_HIGH = 1
OUTPUT_LOW = 0
pinstatus_list = ['LOW','HIGH']
 
GPIO.wiringPiSetup()
GPIO.pinMode(OUTPUT_PIN, OUTPUT)
GPIO.pinMode(INPUT_PIN, INPUT)
 
print("----WiringPi Python Library Test-----")
 
print("set output pin is LOW level")

GPIO.digitalWrite(OUTPUT_PIN, OUTPUT_LOW)
result = GPIO.digitalRead(INPUT_PIN)
print('{}{}'.format('The read Pin value is', pinstatus_list[result]))

GPIO.delay(2000)

print("set output pin is High level")

GPIO.digitalWrite(OUTPUT_PIN, OUTPUT_HIGH)
result = GPIO.digitalRead(INPUT_PIN)
print('{}{}'.format('The read Pin value is', pinstatus_list[result]))

GPIO.delay(2000)
print("End")
