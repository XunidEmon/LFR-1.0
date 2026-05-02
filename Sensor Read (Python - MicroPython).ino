from machine import Pin, ADC
import time

# Sensors (ADC)
s1 = ADC(Pin(32))
s2 = ADC(Pin(33))
s3 = ADC(Pin(34))
s4 = ADC(Pin(35))
s5 = ADC(Pin(36))

while True:
    v1 = s1.read()
    v2 = s2.read()
    v3 = s3.read()
    v4 = s4.read()
    v5 = s5.read()

    avg = (v1 + v2 + v3 + v4 + v5) // 5

    print(v1, v2, v3, v4, v5, "| Avg:", avg)
    time.sleep(0.5)
