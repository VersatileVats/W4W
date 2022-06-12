#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "wifi-ssid";
const int httpsPort = 443;
const char* password = "wifi-pwd";

//Connection variables for the Integromat Scenario
const char* host = "hook.integromat.com";
const char* fingerprint = "83a72e6c37833814cba8bbb90376dabef88ac179";


//Connection variables for the Cloud Request API
const char* host1 = "cloud.boltiot.com";
const char* fingerprint1 = "f219db233aded965dd5cfa95f727576b269341ad";

String place="", line="";

//Variables for the 4051 IC
const int selectPins[2] = {D5, D0};
const int analogInput = A0;

int IR1 = 0;
int IR2 = 0;

//Variables for the TCS300 color sensor
const int s0 = D6;
const int s1 = D7;
const int s2 = 10;//SD3
const int s3 = 9;//SD2   
const int out = D8; 

int red = 0;
int green = 0; 
int blue = 0;

int touch_value = 0;
int robot_max_time = 32;
unsigned long go_back_time = 0;
unsigned long wait_time = 0, start_time = 0;
unsigned long sense_line = 0, follow_line = 0;
unsigned long begin_time = 0, turn_back_time = 0;

void setup() {
  
  //pinModes for the Analog Multiplexer (4051 IC)
  for (int i=0; i < 2; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], HIGH);
  }

  //As an indication measure use the Builtin Led
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,LOW);
  
  //pinModes for the Color sensor
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT); 

  //2% frequency scailing for TCS300
  digitalWrite(s0, LOW);  
  digitalWrite(s1, HIGH);

  //pinModes for Motor Pins (D0-D4)
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);

  //default value function for DC Motors
  back_2_normal();

  //connecting esp8266 to the wifi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  { delay(500); }

  Serial.println(millis()/1000);
  //Step 1: Loop to fetch the predicted value
  while(true)
  {
    get_place_from_integromat();
    if(place!="NA")
    { 
      digitalWrite(s0,HIGH); 
      delay(250); 
      digitalWrite(s0,LOW);
      break; 
    }
    delay(1500);
  }

  //Step 2: Loop to find the line which has to be followed
  while(true)
  {
    line_color();
    if(place == line)
    {
        sense_line = millis();
        while((millis() - sense_line) <= 200)
        { robot_motion(); }
        back_2_normal();
        start_time = millis();
        while((millis()-start_time) < 350)
        { move_right(); }
        back_2_normal();
        break;
    }

    //head to the next colored line
    follow_line = millis();
    while((millis() - follow_line) <= 1050)
    { robot_motion(); }
    back_2_normal();
  }


  begin_time = millis()/1000;

  //assigning robot_max_time according to the destination
  if(place == "Bedroom") {
    robot_max_time = 44;
  } else if (place == "Balcony") {
    robot_max_time = 33;
  }

  //Step 3: Making the robot reach the destination
  while(((millis()/1000) - begin_time) <= robot_max_time)
  { robot_motion(); yield(); }

  back_2_normal();

  //Step 4: Run the song via buzzer and in btw waiting for users input
  Serial.println("Starting the party song");
  buzzer();

  get_touch_input();
  if(touch_value > 600)
  {
     execute_cloud_request();
  }

  //Step 5: Making the robot come back to the starting point  
  turn_back_time = millis();
  while((millis() - turn_back_time) < 750)
  { move_left(); }

  back_2_normal();

  go_back_time = millis()/1000;
  while(((millis()/1000) - go_back_time) <= robot_max_time)
  { robot_motion(); yield(); }
}

void loop() {
}

void get_place_from_integromat()
{
  WiFiClientSecure httpsClient;
  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(15000);
  delay(1000);

  int r=0;
  while((!httpsClient.connect(host, httpsPort)))
  { delay(100); }

  String url = "/es9u64fct1m914xu59qkey1iio9e9j9n";

  httpsClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +               
               "Connection: close\r\n\r\n");

  while (httpsClient.connected()) 
  {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") 
    { break;  }
  }

  String line;
  while(httpsClient.available())
  {        
    line = httpsClient.readStringUntil('\n');
    
    if(line.startsWith("Hall"))
    { place = "Hall"; }

    else if(line.startsWith("Bedroom"))
    { place = "Bedroom";  }

    else if(line.startsWith("Balcony"))
    { place = "Balcony";  }

    else if(line.startsWith("Place") || line.startsWith("Accepted"))
    { place = "NA";   }
  }

}

void execute_cloud_request()
{
  WiFiClientSecure httpsClient;
  httpsClient.setFingerprint(fingerprint1);
  httpsClient.setTimeout(15000);
  delay(1000);

  int r=0;
  while((!httpsClient.connect(host1, httpsPort)))
  { delay(100); }

  String url = "/remote/e719e4f0-cc5d-427b-a0aa-6b9d1ceb0f28/digitalWrite?pin=0&state=LOW&deviceName=BOLT8024008";

  httpsClient.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host1 + "\r\n" +               
               "Connection: close\r\n\r\n");

  while (httpsClient.connected()) 
  {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") 
    { break;  }
  }

  String line;
  while(httpsClient.available())
  { line = httpsClient.readStringUntil('\n'); }
}

void line_color()      
{    
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW); 
 
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  
  digitalWrite(s3, HIGH); 
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  
  digitalWrite(s2, HIGH); 
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH); 

  //Red Line -> Bedroom
  if (red < blue && red < green)
  { line = "Bedroom"; Serial.println("RED COLOR"); } 

  //Blue Line -> Balcony
  else if (blue < red && blue < green)    
  { line = "Balcony"; Serial.println("BLUE COLOR"); }

  //Green Line -> Hall
  else if (green < red && green < blue) 
  { line = "Hall"; Serial.println("GREEN COLOR"); }
}

//Line Following Robot Code
void robot_motion()
{
  //Get the value of IR sensors:
   get_IR_values();

  //forward motion
  if(IR1 < 200 && IR2 < 200)
  { move_fwd();}

  //left motion
  else if(IR1 < 200 && !IR2 < 200)
  { move_left();}

  //right motion
  else if(!IR1 < 200 && IR2 < 200)
  { move_right();}

  //stop motion
  else if(!IR1 < 200 && !IR2 < 200)
  { back_2_normal();}
}

void get_IR_values()
{
  // Loop through the 02 input pins ie A0 and A1
  for (byte pin=0; pin <= 1; pin++)
  {
      for (int i=0; i < 2; i++) 
      { digitalWrite(selectPins[i], pin & (1 << i)?HIGH:LOW); }
      
      if(pin==0)
      { IR1 = analogRead(analogInput);  }
      
      else if(pin==1)
      { IR2 = analogRead(analogInput);  }
  }
}

void get_touch_input()
{
  // Loop through the A2 pin only
  byte pin = 2;
  
  for (int i=0; i < 2; i++) 
  { digitalWrite(selectPins[i], pin & (1 << i)?HIGH:LOW); }
 
  touch_value = analogRead(analogInput);
}

//functions directing the robot
void move_fwd()
{
  back_2_normal();
  analogWrite(D1,150);
  analogWrite(D2,150);
}

void move_left()
{
  back_2_normal();
  digitalWrite(D3,HIGH);
  analogWrite(D1,200);
  analogWrite(D2,200);
}

void move_right()
{
  back_2_normal();
  digitalWrite(D4,HIGH);
  analogWrite(D1,200);
  analogWrite(D2,200);
}

void back_2_normal()
{
  analogWrite(D1,0);
  analogWrite(D2,0);
  digitalWrite(D3,LOW);
  digitalWrite(D4,LOW);
}

void testing(int x)
{
  digitalWrite(s0,HIGH); 
  delay(x); 
  digitalWrite(s0,LOW);
}

void buzzer()
{
  #define NOTE_B0  31
  #define NOTE_C1  33
  #define NOTE_CS1 35
  #define NOTE_D1  37
  #define NOTE_DS1 39
  #define NOTE_E1  41
  #define NOTE_F1  44
  #define NOTE_FS1 46
  #define NOTE_G1  49
  #define NOTE_GS1 52
  #define NOTE_A1  55
  #define NOTE_AS1 58
  #define NOTE_B1  62
  #define NOTE_C2  65
  #define NOTE_CS2 69
  #define NOTE_D2  73
  #define NOTE_DS2 78
  #define NOTE_E2  82
  #define NOTE_F2  87
  #define NOTE_FS2 93
  #define NOTE_G2  98
  #define NOTE_GS2 104
  #define NOTE_A2  110
  #define NOTE_AS2 117
  #define NOTE_B2  123
  #define NOTE_C3  131
  #define NOTE_CS3 139
  #define NOTE_D3  147
  #define NOTE_DS3 156
  #define NOTE_E3  165
  #define NOTE_F3  175
  #define NOTE_FS3 185
  #define NOTE_G3  196
  #define NOTE_GS3 208
  #define NOTE_A3  220
  #define NOTE_AS3 233
  #define NOTE_B3  247
  #define NOTE_C4  262
  #define NOTE_CS4 277
  #define NOTE_D4  294
  #define NOTE_DS4 311
  #define NOTE_E4  330
  #define NOTE_F4  349
  #define NOTE_FS4 370
  #define NOTE_G4  392
  #define NOTE_GS4 415
  #define NOTE_A4  440
  #define NOTE_AS4 466
  #define NOTE_B4  494
  #define NOTE_C5  523
  #define NOTE_CS5 554
  #define NOTE_D5  587
  #define NOTE_DS5 622
  #define NOTE_E5  659
  #define NOTE_F5  698
  #define NOTE_FS5 740
  #define NOTE_G5  784
  #define NOTE_GS5 831
  #define NOTE_A5  880
  #define NOTE_AS5 932
  #define NOTE_B5  988
  #define NOTE_C6  1047
  #define NOTE_CS6 1109
  #define NOTE_D6  1175
  #define NOTE_DS6 1245
  #define NOTE_E6  1319
  #define NOTE_F6  1397
  #define NOTE_FS6 1480
  #define NOTE_G6  1568
  #define NOTE_GS6 1661
  #define NOTE_A6  1760
  #define NOTE_AS6 1865
  #define NOTE_B6  1976
  #define NOTE_C7  2093
  #define NOTE_CS7 2217
  #define NOTE_D7  2349
  #define NOTE_DS7 2489
  #define NOTE_E7  2637
  #define NOTE_F7  2794
  #define NOTE_FS7 2960
  #define NOTE_G7  3136
  #define NOTE_GS7 3322
  #define NOTE_A7  3520
  #define NOTE_AS7 3729
  #define NOTE_B7  3951
  #define NOTE_C8  4186
  #define NOTE_CS8 4435
  #define NOTE_D8  4699
  #define NOTE_DS8 4978

  int melody[] = {
    NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
    NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
    NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
    NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
    NOTE_AS4, NOTE_AS4, NOTE_AS4, NOTE_AS4,
    NOTE_D5, NOTE_D5, NOTE_D5, NOTE_D5,
    NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5, 
    NOTE_F5, NOTE_F5, NOTE_F5, NOTE_F5, 
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5,
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
    NOTE_G5, NOTE_G5, NOTE_G5, NOTE_G5, 
    NOTE_C5, NOTE_AS4, NOTE_A4, NOTE_F4,
    NOTE_G4, 0, NOTE_G4, NOTE_D5,
    NOTE_C5, 0, NOTE_AS4, 0,
    NOTE_A4, 0, NOTE_A4, NOTE_A4,
    NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
    NOTE_G4,0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
    NOTE_G4,0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
    NOTE_G4, 0, NOTE_G4, NOTE_D5,
    NOTE_C5, 0, NOTE_AS4, 0,
    NOTE_A4, 0, NOTE_A4, NOTE_A4,
    NOTE_C5, 0, NOTE_AS4, NOTE_A4, 
    NOTE_G4,0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5,
    NOTE_G4,0, NOTE_G4, NOTE_AS5,
    NOTE_A5, NOTE_AS5, NOTE_A5, NOTE_AS5
  };

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  4,4,4,4,
  };
  
  for (int thisNote = 40; thisNote < 112; thisNote++) {
   
    int noteDuration = 750 / noteDurations[thisNote];
    tone(s0, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    
    noTone(s0);
  }
}
