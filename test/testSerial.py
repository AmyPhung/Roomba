#!/usr/bin/env python

import serial, time

arduino = serial.Serial('/dev/ttyACM0', 115200, timeout=.1)
time.sleep(1) #give the connection a second to settle
# arduino.write("Hello from Python!")
arduino.write("SL+55A+100E")


while True:
    arduino.write("SL+50A+100E")
    arduino.write("SL+53A+100E")
    # print(1)

    # print(2)
    time.sleep(0.05)
    # print(3)
    print(time.time())
    # print(4)
    # data = arduino.readline()
    while arduino.in_waiting:
        print("innerloop")
        data = arduino.readline()
        # print(5)
        if data:
            print data #strip out the new lines for now

    # # print(2)
    # time.sleep(0.05)
    # # print(3)
    # print(time.time())
    # # print(4)
    # # data = arduino.readline()
    # while arduino.in_waiting:
    #     print("innerloop2")
    #     data = arduino.readline()
    #     # print(5)
    #     if data:
    #         print data #strip out the new lines for now


		# (better to do .read() in the long run for this reason
    # print(6)
    #
    # arduino.write("SL+52A+100E")
    # time.sleep(0.05)
    # print(time.time())
    # data = arduino.readline()
    # if data:
    #     print data.rstrip('\n') #strip out the new lines for now
	# 	# (better to do .read() in the long run for this reason
