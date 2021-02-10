#!/usr/bin/env python

import pyfirmata
import time

board = pyfirmata.Arduino('/dev/ttyACM0')
# avoid the board to keep sending data to my serial port
it = pyfirmata.util.Iterator(board)
it.start()

# specify the analog channel to read data
# analog_input = board.get_pin('a:0:i')
board.analog[0].enable_reporting()

while True:
    # analog_value = analog_input.read()
    # print(analog_value)
    print(board.analog[0].read())
    time.sleep(1)