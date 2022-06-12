from twilio.rest import Client 

account_sid = 'AC605df19db112080a31aa5a9066ea9c6d' 
auth_token = '120a9c77cdfa7e14486296be2c8874f4' 
client = Client(account_sid, auth_token) 

message = client.messages.create( 
     from_='whatsapp:+14155238886',  
     body='The autonomous project: \n\nWHEELS FOR WATER, is doing its job 👍 Do sit back and relax. https://google.com',      
     to='whatsapp:+917011238307' 
) 

from twilio.rest import Client 
 
account_sid = 'AC605df19db112080a31aa5a9066ea9c6d' 
auth_token = '120a9c77cdfa7e14486296be2c8874f4' 
client = Client(account_sid, auth_token) 
 
message = client.messages.create(   
    from_='+12064881502',                          
    body='The autonomous project: \n\nWHEELS FOR WATER, is doing its job 👍 Do sit back and relax. https://google.com',  
    to='+917011238307' 
 ) 