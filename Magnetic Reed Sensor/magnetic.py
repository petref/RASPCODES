from time import sleep
import RPi.GPIO as io
io.setmode(io.BCM)
io.setwarnings(False)

mgsenz_pin=14

counter = 0

io.setup(mgsenz_pin, io.IN)

while True:
    if(io.input(mgsenz_pin)==False):
        print("Magnet Detected")
    else:
        print("No magnet detected")