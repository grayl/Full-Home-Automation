#Debadri Dutta's Code

import time
import serial
import smtplib
import email.utils
 
TO = 'recepient@gmail.com'
GMAIL_USER = 'putyouremailaddress@gmail.com'
GMAIL_PASS = '*********'
 
SUBJECT = 'Fire Detected'
TEXT = 'Fire Alert-Fire has been detected at your home. Get to know the intensity at: https://thingspeak.com/channels/260143. Call 911 ' #Put your link of the cloud
  
ser = serial.Serial('COM3', 9600) #PORT NO. OF YOUR ARDUINO, BAUD RATE
 
def send_email():
    print("Sending Email")
    smtpserver = smtplib.SMTP("smtp.gmail.com",587)
    smtpserver.ehlo()
    smtpserver.starttls()
    smtpserver.ehlo
    smtpserver.login(GMAIL_USER, GMAIL_PASS)
    header = 'To:' + TO + '\n' + 'From: ' + GMAIL_USER
    header = header + '\n' + 'Subject:' + SUBJECT + '\n'
    print(header)
    msg = header + '\n' + TEXT + ' \n\n'
    smtpserver.sendmail(GMAIL_USER, TO, msg)
    smtpserver.close()
    
while True:
    message = ser.readline()
    print(message)
    print(message[2]); #TO PRINT THE NUMERICAL VALUE OF "F", INCASE YOU USE SOMETHING ELSE JUST CHANGE THE VALUES HERE AND IN THE NEXT LINE
    if message[2] == 114: #THE INTEGER VALUE OF "F"
        send_email()
    time.sleep(1)
