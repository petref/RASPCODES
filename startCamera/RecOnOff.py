import os
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.chrome.options import Options
import time
import executeWheel

lastCounter = 0



#setting and option for browser session
chrome_options = Options()
chrome_options.accept_untrusted_certs = True
chrome_options.asume_untrusted_cert_issuer = True
chrome_options.add_argument('--headless')
chrome_options.add_argument('--no-sandbox')
chrome_options.add_argument("--window-size=1920x1000")
chrome_options.add_argument('--disable-features=VizDisplayCompositor')
chrome_options.add_argument('--disable-gpu')

chrome_options.binary_location = '/usr/lib/chromium-browser/chromium-browser'

#print(options.add_argument('--headless'))

#opening browser websession
driver = webdriver.Chrome(chrome_options = chrome_options, executable_path="/usr/lib/chromium-browser/chromedriver")
page = driver.get("http://admin:pxw-fs7@192.168.1.1")

#load rotaty setting from executeWheel module
executeWheel.init()

#loop for start/stop recording depending an the rotation of the platform
while True:
        counter = executeWheel.counter
        if(counter != lastCounter):
                #start recording
                rec_start=driver.find_element_by_id('DIV_REC_START')
                rec_start.click()
                lastCounter = counter
                print('Sunt in REC:')
                print(counter)
                print(" ")
                print(lastCounter)
                time.sleep(0.2)
        else:
                #stop recording
                rec_stop = driver.find_element_by_id('DIV_REC_STOP')
                rec_stop.click()
                print('sunt in stop')
                print(counter)
                print(" ")
                print(lastCounter)

#closing browser session
driver.close()


