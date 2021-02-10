#!/usr/bin/env python

from scipy.interpolate import InterpolatedUnivariateSpline
from time import sleep
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import serial

ser = serial.Serial('/dev/ttyACM0', 9600) # Establish the connection on a specific port
ser.flushInput()

adc2temp = pd.read_csv('../data/temp_calib.csv')
x_meas = np.flip(np.array(adc2temp['ADC']))
y_meas = np.flip(np.array(adc2temp['temperatuer (°C)']))
x_plot = np.linspace(x_meas.min(), x_meas.max(), 101)

ius = InterpolatedUnivariateSpline(x_meas, y_meas)
y_ius = ius(x_plot)

plt.plot(x_meas, y_meas, 'bo', label='measured')
plt.plot(x_plot, y_ius, 'y', label='spline', alpha=.9)
plt.legend()
plt.ylabel('temperatuer (°C)')
plt.xlabel('ADC')

plt.savefig('adc_to_temperature.png')

while True:
    ser_bytes = ser.readline()
    decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode('utf-8')
    adc0 = float(decoded_bytes.split(',')[0])
    adc1 = float(decoded_bytes.split(',')[1])
    temp0 = ius(adc0)
    temp1 = ius(adc1)
    print('ADC0:{} \ttemp0: {:.2f}°C\tADC1:{} \ttemp1: {:.2f}°C'.format(adc0, temp0, adc1, temp1))
    sleep(1)