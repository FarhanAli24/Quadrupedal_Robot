import math
from machine import Pin, PWM, ADC

def joyStick(xValue, yValue):
    xValue = xValue.read_u16()
    yValue = yValue.read_u16()
    if xValue <= 0:
        xValue = 0.1    
    rotation = (math.atan(yValue / xValue) * (180 / math.pi))
    rotation = rotation/45 * 140
    return rotation
