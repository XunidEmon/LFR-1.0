from machine import Pin, ADC, PWM
import time

# Sensors
s1 = ADC(Pin(32))
s2 = ADC(Pin(33))
s3 = ADC(Pin(34))
s4 = ADC(Pin(35))
s5 = ADC(Pin(36))

# Motors
lm1 = Pin(25, Pin.OUT)
lm2 = Pin(26, Pin.OUT)
rm1 = Pin(27, Pin.OUT)
rm2 = Pin(14, Pin.OUT)

lpwm = PWM(Pin(12))
rpwm = PWM(Pin(13))

lpwm.freq(1000)
rpwm.freq(1000)

th = 2000   # ESP32 ADC scale (0–4095)

def set_speed(l, r):
    lpwm.duty(l)
    rpwm.duty(r)

def forward():
    lm1.value(1); lm2.value(0)
    rm1.value(1); rm2.value(0)
    set_speed(600, 600)

def left():
    lm1.value(0); lm2.value(1)
    rm1.value(1); rm2.value(0)
    set_speed(400, 600)

def right():
    lm1.value(1); lm2.value(0)
    rm1.value(0); rm2.value(1)
    set_speed(600, 400)

def hardLeft():
    lm1.value(0); lm2.value(1)
    rm1.value(1); rm2.value(0)
    set_speed(300, 600)

def hardRight():
    lm1.value(1); lm2.value(0)
    rm1.value(0); rm2.value(1)
    set_speed(600, 300)

def stop():
    lm1.value(0); lm2.value(0)
    rm1.value(0); rm2.value(0)
    set_speed(0, 0)

while True:
    v1 = s1.read()
    v2 = s2.read()
    v3 = s3.read()
    v4 = s4.read()
    v5 = s5.read()

    L1 = 1 if v1 < th else 0
    L2 = 1 if v2 < th else 0
    L3 = 1 if v3 < th else 0
    L4 = 1 if v4 < th else 0
    L5 = 1 if v5 < th else 0

    if L3:
        forward()
    elif L2:
        left()
    elif L4:
        right()
    elif L1:
        hardLeft()
    elif L5:
        hardRight()
    else:
        stop()

    time.sleep(0.01)
