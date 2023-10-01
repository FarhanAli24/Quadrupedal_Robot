from servo import *
import utime
import math
#import controller
from machine import Pin, PWM, ADC




def joyStick(xValue, yValue):
    xValue = xValue.read_u16()
    yValue = yValue.read_u16()
    if xValue <= 0:
        xValue = 0.1
    rotation = (math.atan(yValue / xValue))#* (180 / math.pi)
    #rotation = rotation/45 * 140 #70
    return rotation


elbow = 0
leg = 1

xAxis = ADC(Pin(27))
yAxis = ADC(Pin(26))


joint = SERVO()
analog = SERVO()

joint.servoInit(elbow)
utime.sleep(1)
joint.servoInit(leg)
utime.sleep(1)


while True:
    #rotation = joyStick(xAxis, yAxis)
    '''   
    if rotation >= 1:
        rotation = 0.9
    print(rotation)
    rotation = math.acos(rotation) * (180 / math.pi)
    rotation2 = 180 - (2*rotation)
    rotation = rotation/38 * 140
    rotation2 = rotation2/104 * 80
    '''
     
    xValue = xAxis.read_u16()
    yValue = yAxis.read_u16()
    if yValue <= 200:
        yValue = 33240
        
    
    radian = (math.atan(xValue / yValue))

    
    elbowRotation = yValue/math.cos(radian)
    elbowRotation = elbowRotation * (180/math.pi)
    degrees = radian * (180/math.pi)
    elbowRotation = (elbowRotation/2624593) * 75
    if elbowRotation <= 50:
        elbowRotation = 80
    
    degrees = degrees/45 * 140
    #utime.sleep_ms(300)
    #print(degrees)
    
    if degrees >= 180:
        degrees = 140
    if degrees <= 20:
        degrees = 30
        
    joint.servo(degrees, leg)
    joint.servo(elbowRotation, elbow)




while Flase:
    joint.servo(100, leg)
    utime.sleep_ms(500)
    joint.servoInit(leg)
    utime.sleep_ms(500)

    joint.servo(100, elbow)
    utime.sleep_ms(500)
    joint.servoInit(elbow)
    utime.sleep_ms(500)

