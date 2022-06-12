import datetime

x = datetime.datetime.now()

# weekend attribute
day = x.strftime("%A")
# phase attribute
half = x.strftime("%p")
# time attribute
minute = x.strftime("%M")

# Function to set the weekend attribute of data:
def week():
    if day == "Saturday" or day == "Sunday" :
        week.weekend = "Yes"

    else :
        week.weekend = "No"

# Function to set the phase attribute of data:
def meridiem():
    if half == "AM":
        meridiem.phase = "Morning"
        
    elif half == "PM":
        meridiem.phase = "Evening"

# Function to set the time attribuete of data
def time():
    m = int(minute)
    if m in range(0,21):
        time.slot = "First"
        
    elif m in range(21,41):
        time.slot = "Second"
        
    elif m in range(41,59):
        time.slot = "Third"