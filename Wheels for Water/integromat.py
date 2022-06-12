import requests

# Integromat's scenario for storing the activity logs of the system
# Google sheet's name: Acivity Logs
def upload_activity(day,start,end,place,prediction):
    URL = "https://hook.integromat.com/kt27ecxk46ij7ngv3907sqa6u12jcltv?Day="+day+"&Start="+start+"&End="+end+"&Place="+place+"&Prediction="+prediction
    response = requests.request("POST",URL)
    print(response.text)
    
# Integromat's scenario for storing the place variable into table
# Google sheet's name: Prediction
def upload_prediction(place):
    URL = "https://hook.integromat.com/ltw9i9mi3eds8zh9ckz95o0am84k6jqr?Place="+place     
    response = requests.request("POST",URL)
    print(response.text)
    
# Integromat's sceanrio for fetching the schedule details
def get_schedule():
    URL = "https://hook.integromat.com/t69ssbbcxdnpf2br97oyup8s2h29iedc"
    response = requests.request("GET", URL)
    return response.text
        
# Integromat's for fetching the place variable into table
def get_prediction():
    URL = "https://hook.integromat.com/es9u64fct1m914xu59qkey1iio9e9j9n"
    response = requests.request("GET",URL)
    if(response.text == "Place"):
        print("No Record found")
    else:
        print(response.text)