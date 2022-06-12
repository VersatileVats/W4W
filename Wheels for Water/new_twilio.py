from twilio.rest import Client 
 
account_sid = 'ACf1339232a9cc6197b94117610957486f' 
auth_token = '48b958e590dfcf3fe4a92edbecf6ca4f'
client = Client(account_sid, auth_token) 
 
message = client.messages.create( 
                              from_='whatsapp:+14155238886',  
                              body='Hello! This is an editable text message. You are free to change it and write whatever you like.',      
                              to='whatsapp:+917011238307' 
                          ) 
 
print(message.sid)