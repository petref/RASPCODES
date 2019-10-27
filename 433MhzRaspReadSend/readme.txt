receive.py / send.py

https://www.instructables.com/id/RF-433-MHZ-Raspberry-Pi/


dependencies: 
- sudo get-apt install python3-pip
- sudo pip3 install rpi-rf

https://pypi.org/project/rpi-rf/

receive.py snifs 433mhz code with protocol, pulse length and code.

send.py sends code in calling of the file you need to add as arguments the pulselength and protocol as below:
python3 send.py -p [pulselength] -t [protocol] [code]   ex: