###########################################################################################################################################################

Dependencies:
* pip install selenium 
* sudo apt-get update && sudo apt-get upgrade && sudo apt-get dist -upgrade
* chromedriver from the zip file you find with this repository


FLOW DESCRIPTION:
---------------------------------------------------
* browserCommand.desktop:
	This file will be run, when the GUI is sole purpose is to open a terminal window and 
	in this terminal to run the job.sh file. *This file contains abs. path to job.sh!!!
*job.sh
	This bash file will run in the terminal it is open a python script, more precise the 
	checkWifi.py script.

*checkWifi.py
	The script checks in a loop if the pi has connected to a network. 
	The event when the pi connects to a network triggers the event to compare the network SSID
	with the known SSID's of the 7 camera's and if the SSID checks OK, then the RecOnOff.py script 
	is run.

*RecOnOff.py:
	The script opens a session of chromium-browser using the chromedriver, then initiates also the executeWheel.py
	and starts a loop if the encoder values modify then the script clicks DIV_START_REC and if the encoder values is stuck at a 
	value then the script presses DIV_STOP_REC.
	
	

* executeWheel.py : 
	Runs the GPIO.PIN 17/18 and runs the counter for the encoder.
	This script it is all about the encoder and returns the encoder values, from here you can always set max value an which the counter 
	can be reset and the wheel can be stopped.


 Reboot ===>browserCommand.desktop ========>job.sh=======>checkWifi.py ------------> RecOnOff.py
											|
											|
											|
									(gets the encoder values in loop)
											|
											|
										   executeWheel.py

HOW TO*:
-------------------------------------------------

*create folder wheel in /home/pi/

now the path will be: /home/pi/wheel/[files]


As the chromedriver can have version conflicts for the chromium v74 you can use the cromedriver from repo:
*copy the file to path
*unzip /home/pi/wheel/chromedriver
move the file to the bin folder for accesibility:
*sudo mv /home/pi/wheel/chromedriver /usr/bin/chromedriver
handle permissions:
*sudo chown root:root /usr/bin/chromedriver
*sudo chmod +x /usr/bin/chromedriver


Create bash file:
*nano /home/pi/wheel/job.sh
 write in file just this 1 line -  python /home/pi/wheel/checkWifi.py -

Create run job at start of GUI:
*cd /etc/xdg/autostart

Create .desktop - file: 
*touch browserCommand.desktopfile

Copy the text below in the file:
============================
[Desktop Entry]
Name=myScript
Path=/home/pi/wheel/
Exec=lxterminal -e  '/home/pi/wheel/job.sh'
Type=Application
StartupNotify=true
================================

Save file.

Reboot and watch the magic happen:  :)
*sudo reboot











