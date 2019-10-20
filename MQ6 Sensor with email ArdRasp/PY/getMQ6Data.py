#!/user/bin/env python

from datetime import datetime
import serial
import time


last_sec = 0;
last_number =" ";


port = '/dev/ttyUSB0'

s1 = serial.Serial(port,9600)
input = s1.read()
print("Read input " + input.decode("utf-8") + "from Arduino");





while 1:

        input =s1.read()
        input_number=ord(input)

        now = datetime.now();
        current_time=now.strftime("%H:%M:%S");
        print(current_time)
        last_time="00:02:00"
        last_time1 ="00:02:01"
        if (current_time == last_time or current_time == last_time1):
                fileLog1 = open("/home/pi/gasSensor/log.txt", "w")
                fileLog1.write("TODAY")
                print("File erased")

        fileLog = open("/home/pi/gasSensor/log.txt","a");
        fileLog.write("%d" %now.year);
        fileLog.write(".%d" %now.month);
        fileLog.write(".%d " %now.day);
        fileLog.write(current_time);
        fileLog.write(" - " + str(input_number) + "\n");
        fileLog.close();
        last_sec = now.second;
        print ("Read Input Back: " + str(input_number))
        s1.flush();



