import utime
from machine import Pin, PWM


class SERVO:
    #pwm = PWM(Pin(0))
    #pwm.freq(50)
    def servoInit(self, pin):
        pwm = PWM(Pin(pin))
        pwm.freq(50)
        duty = ((140 / 270) * 6553) + 1638
        pwm.duty_u16(int(duty))

    def servo(self, angle, pin):
        pwm = PWM(Pin(pin))
        pwm.freq(50)
        duty = ((angle / 270) * 6553) + 1638
        pwm.duty_u16(int(duty))





#pos = SERVO()
#pos.servoInit(0)
#pos.servo(270, 0)

