import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText
from email.mime.base import MIMEBase
from email import encoders

fromaddr = "dv.stationreport@gmail.com"
toaddr ="petroupb@gmail.com"

msg=MIMEMultipart();

msg['FROM'] = fromaddr
msg['TO'] = toaddr
msg['Subject'] ="Daily Report"

body="My daily report"

msg.attach(MIMEText(body, 'plain'))

filename="log.txt"
attachment = open("/home/pi/gasSensor/log.txt", "rb")

part=MIMEBase('application','octet-stream')
part.set_payload((attachment).read())
encoders.encode_base64(part)
part.add_header('Content-Disposition', "attachment; filename = %s" % filename)

msg.attach(part)

server = smtplib.SMTP('smtp.gmail.com', 587)
server.starttls()
server.login(fromaddr, "Cristi74")
text= msg.as_string()
server.sendmail(fromaddr, toaddr, text)
server.quit()
