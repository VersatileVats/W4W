# importing the general modules
import speech_recognition as sr
import simpleaudio as sa

from twilio.rest import Client
from boltiot import Bolt
import pandas as pd
import datetime
import serial
#import json

# Importing the local python files
import attribute as att
import prediction as pr
import integromat as integ
import credentials as cred

# initializing the bolt object
mydevice = Bolt(cred.API_key,cred.DEVICE_id)
# As motor is connected to the Normally Close port of relay, it has to be set to LOW
mydevice.digitalWrite(0, 'LOW')

#initializing the twilio's object
client = Client(cred.account_sid, cred.auth_token)

# calling the attribute's functions
att.week()
att.meridiem()
att.time()
 
timeToFill = "0"   
communication = "comm"

def categorize_temperature(tmp):
    if tmp < 15:
        return "cool"
    elif tmp > 15 and tmp<30:
        return "moderate"
    else :
        return "high"
    
def run_audio_file(name):
    filename = name
    wave_obj = sa.WaveObject.from_wave_file(filename)
    play_obj = wave_obj.play()
    play_obj.wait_done()

def twilio_alert(arg):
    
    #default string in case the user do not select anything from the touch module
    msg_string = "Dear user, need your attention here. The water tanks will be filled in "+timeToFill+" seconds\
                 \n\n📢📢 You can turn off the water motor by the following ways:\
                 \n👉 Direct API Request: \n  https://bit.ly/3ghdLbI \
                 \n👉 Cloud Dashboard: \n  https://bit.ly/3AWkBLI \
                 \n👉 Dedicated Web Application: \n  https://wheels4water.me \
                 \n\nYou can use any of the methods as per your convenience and in case you forgot to switch it off, it will be done on my own.\
                 \n\n Save Water & it will save us 🙏🙏 "
    
    if arg=="start":
        msg_string = "The autonomous project: Wheels for water, welcome you user. One cycle of the process has been initiated. I will keep you updated\
                     \n\nIf you are near the static site then hold on one of the four touch buttons, present over there, for 5 seconds. Following are the buttons with their meaning\
                    \n\n1️⃣ Button 1 : Direct API Request\
                    \n2️⃣ Button 2 : Cloud Dashboard\
                    \n3️⃣ Button 3 : Dedicated Web Application\
                    \n\nAt present, if you are not sure which way to choose then you can either choose the button 4 or even can skip this.\
                    \nYou will be provided with the respective choices at the time of intimation again."
    
    elif arg=="comm1":
        msg_string = "Dear user, need your attention here. The water tanks will be filled in "+timeToFill+" seconds\
                     \n\nIn the initial phase of the project you chose to switch off the motor through the direct API request. \n\nHere is the direct link: https://bit.ly/3ghdLbI\
                     \n\nDo click on this link to switch off the motor. You can also choose from other 2 options ie Cloud Dashboard & Web application to switch the motor off."
        
    elif arg=="comm2":
        msg_string = "Dear user, need your attention here. The water tanks will be filled in "+timeToFill+" seconds\
                     \n\nIn the initial phase of the project you chose to switch off the motor through the cloud's dashboard. \n\nHere is the dashboard's link: https://bit.ly/3AWkBLI\
                     \n\nJust click on the Turn Off button to switch off the motor. You can also have a detailed view of the time over which the motor was on. \
                     \n\nYou can also choose other 2 options ie Direct link & Web application to switch the motor off."
        
    elif arg=="comm3":
        msg_string = "Dear user, need your attention here. The water tanks will be filled in "+timeToFill+" seconds\
                     \n\nIn the initial phase of the project you chose to switch off the motor through the web application. \n\nHere is the app's link: https://wheels4water.me\
                     \n\nLog in and then switch off the motor. You can also choose other 2 options ie Cloud Dashboard & Direct link to switch the motor off."
    
    elif arg=="stopped" or arg=="stop":
        msg_string = "Congrats user, one cycle of the autonomous project: Wheels For Water has been completed. Glad that you used this project.\
                     \n\nWishing you good luck for the rest of the day. You truly are an insipiration ✌"
        
    #whatsapp message
    client.messages.create( 
     from_='whatsapp:'+cred.FROM_,  
     body=msg_string,
     to='whatsapp:'+cred.TO_ 
     ) 
    
    #text (normal) message
    #client.messages.create( 
     #from_= cred.text_FROM,  
     #body=msg_string,
     #to= cred.TO_ 
     #) 
    
def voice_command():
    r = sr.Recognizer()
    mic = sr.Microphone()
    
    try:
        with mic as source:
            # listening to the user
            audio = r.listen(source)
        
            user_phrase = r.recognize_google(audio)
            print("\nUser's phrase:",user_phrase)
        
            #evaluating the user's phrase
            phrase = user_phrase.split()
            for i in phrase:
                if i=="off":
                    return "success"
                    break
        
    except Exception as e:
        return e

# opening the serial communication port
comm = serial.Serial('COM3',9600)

# looping through the values which will be collected via serial port
i=0
while i<6:  
    x = comm.readline().decode().strip()
    
    if x=="start":
        mydevice.digitalWrite(0, 'HIGH')
        run_audio_file("audio/start.wav")
        # store the start time of motor
        start = datetime.datetime.now().strftime("%X")
        twilio_alert(x)
        print("\nMotor on..") 
        
    elif x=="comm1" or x=="comm2" or x=="comm3" or x=="comm":
        communication = x
        print(communication)
    
    elif x=="robot" or x=="noRobot":
        
        # checking whether schedule is there is not
        schedule = integ.get_schedule()
        if schedule == "1" or schedule == "2":
            x = "noRobot"
            
        if x=="robot":
            # get the temperature reading from the LM35 sensor
            #temp = mydevice.analogRead('A0')
            #reading = json.loads(temp)
            #temp_reading = int(reading["value"])/10.24
            
            data = {'weekend':att.week.weekend,'phase':att.meridiem.phase,'time':att.time.slot,'temp':categorize_temperature(10)}
            inst = pd.Series(data)
        
            print("\nData attributes through which ML algorithm has predicted: \n" + str(data))

            place = pr.predict(inst,pr.tree)
            #sending the place (predicted value) to arduino
            comm.write(place.encode())

            print("\nAccording to ID3 Algorithm's prediction, the person should be in: " + place)
            print("\nUploading the data to Google sheets: ")
            integ.upload_prediction(place)
            
            #sending the twilio's alert message to the user
            twilio_alert(communication)
            
            run_audio_file("audio/robot.wav")
            
        if x=="noRobot":
            run_audio_file("audio/noRobot.wav")
            #sending the twilio's msg alert
            twilio_alert(communication)
        
    elif x=="stop" or x=="stopped":
        if x=="stopped":   
            end = datetime.datetime.now().strftime("%X")
            run_audio_file("audio/stopped.wav")
            twilio_alert(x)
            print("\nMotor was switched off by the user")
        
        if x=="stop":
            end = datetime.datetime.now().strftime("%X")
            run_audio_file("audio/last.wav")
            if voice_command() == "success":
                mydevice.digitalWrite(0, 'LOW')
                twilio_alert(x)
                run_audio_file("audio/stopped.wav")
                print("\nMotor was switched off by the user")
                break
            mydevice.digitalWrite(0, 'LOW')
            twilio_alert(x)
            run_audio_file("audio/stop.wav")
            print("\nMotor has been forcefully shut down")
        
    elif x=="True" or x=="False":
        print("\nUploaded the prediction. The prediction was",x)
        integ.upload_activity(att.day, start, end, place, x)
    
    else :
        # condition to fetch the time to fill
        print("\nTime to fill:",x)
        timeToFill = x
        
    i=i+1

comm.close()