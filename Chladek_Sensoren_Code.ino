from machine import Pin, ADC, UART
import time

uart1 = UART(1, baudrate=9600, tx=33, rx=32)

fotowiderstand_pin = 35
potentiometer_pin = 25
led_pin = 2

pin_fotow = ADC(Pin(fotowiderstand_pin))
pin_potent1 = ADC(Pin(potentiometer_pin))
pin_potent1.width(ADC.WIDTH_12BIT)
pin_led = Pin(led_pin, Pin.OUT)

while True:
    fotow = pin_fotow.read()
    potent1 = pin_potent1.read()

    uart1.write("Fotowiderstand: {}\tPotentiometer: {}\n".format(fotow, potent1))

    time.sleep_ms(100)
                                                                                                                                                                                                                                                                                                                                    