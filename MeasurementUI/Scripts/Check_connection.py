#!/usr/bin/env python
import struct
import serial
import time

ser = serial.Serial()
# Configuration of serial port
ser.port = "/dev/tty.usbserial"
ser.baudrate = 9600
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_TWO
ser.timeout = 2
ser.xonxoff = False
ser.rtscts = False
ser.dsrdtr = True

try:
	ser.open()
except(e):
	print("Cannot open serial port: {}".format(str(e)))
	exit()
print(ser.isOpen())

print("Serial start")

# command = "*IDN?"

command = ":SYST:REM;"
ser.write(command.encode("utf-8"))
ser.write("\n".encode("utf-8"))
# ret = ser.read_until().decode("utf-8")

# command = "MEASure:RESistance?"
command = ":MEAS:VOLT:DC?"

ser.write(command.encode("utf-8"))
ser.write("\n".encode("utf-8"))
ret = ser.read_until().decode("utf-8")

print("return value: ", ret)

ser.close()