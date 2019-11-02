import os
import subprocess
from subprocess import check_output

startProgram = 0


while startProgram == 0:
        try:
                scanoutput = check_output(["sudo","iwgetid"])

                for line in scanoutput.split():
                        if line.startswith("ESSID"):
                                ssid=line.split('"')[1]

                AuthWifi = ["DIRECT-gaF0:PXW-FS7_0055572","DIRECT-sbF0:PXW-FS7_0055647"]


                PresentNetwork = ssid

                if PresentNetwork in AuthWifi:
                        startProgram = 1
                        check_output(["python","/home/pi/wheel/RecOnOff.py"])

                print("OK")

        except subprocess.CalledProcessError:
                continue