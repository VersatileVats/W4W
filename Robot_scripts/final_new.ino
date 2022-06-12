#include <NewPing.h>
#include <LiquidCrystal_I2C.h>

//General Variables
float ttf = 0;
float wpcm = 480;
float flowRate = 0.0;
float left_volume = 0.0;

int robot_max_time = 32;
    
volatile int count = 0;

String place = "";
String prediction = "";

unsigned long start_seconds = 0;

//Pin Related Variables
#define Trig1 10
#define Echo1 11
#define Echo2 5
#define Trig2 6
#define valve 4
#define flowPin 2
#define DC_Motor A0
#define sensorInterrupt 0

//Variables for the touchpad
int touchPad[4] = {3,7,8,9};

NewPing sonar[2] = {  
  NewPing(Trig1,Echo1,200), 
  NewPing(Trig2,Echo2,200)
};


// Function for handling the interrupt on GPIO 2
void calculate_waterFlow()
{
  attachInterrupt(sensorInterrupt,flow, RISING);
  delay(1000);
  detachInterrupt(sensorInterrupt);
}

// ISR or Interrupt Handler for water flow sensor
void flow()
{ count++; }


void setup()
{
  Serial.begin(9600);
  lcd_display();

  //Declaring the necessary mode of operation for the pins
  pinMode(valve, OUTPUT);
  pinMode(DC_Motor,INPUT);
  pinMode(flowPin, INPUT);
  digitalWrite(flowPin,HIGH);

  //pinModes for the touchpad
  for(byte i=0; i <=3; i++)
  { pinMode(touchPad[i],INPUT); }

  //Step1: Solenoid valve will be switched on
  digitalWrite(valve,HIGH);

  //Step2: Turn off the water pump when the water level in the water tower is >90%
  while(true)
  {
    int water_level = sonar[0].ping_cm();
    
    if(water_level <= 5) {
      digitalWrite(valve,LOW); 
      break;
    }

    delay(200);
    yield();
  }

  //Step3: Calculate the volume of the secondary tank to be filled
  delay(100);
  int water_level = sonar[1].ping_cm();
  left_volume = (water_level - 6) * wpcm;

  lcd_display();

  //Step4: Send the message to python ,via serial comm, for turning on the motor
  Serial.println("start");
  delay(1500);
  start_seconds = millis()/1000;

  //loop to check the input entered by the user via the touchpad 
  while(((millis()/1000) - start_seconds) < 1)
  {
    String comm="comm";
    for(byte i=0; i <=3; i++)
    {
      if(digitalRead(touchPad[i]) == 1)
      {
        comm = comm+(i+1);
        Serial.println(comm);
        break;
      }
    }
    Serial.println(comm);
    delay(1000);
  }

  calculate_waterFlow();

  //flowRate in ml/sec
  flowRate = ((1000.0/999.0)*count)*0.23;

  //Step6: Calculating the ttf (in seconds) as now I have left_volume and flowRate
  ttf = left_volume / flowRate;
  Serial.println(ttf);

  //now the ttf will be displayed to the lcd
  lcd_display();
  
  if(ttf < robot_max_time)
  { Serial.println("noRobot");  }

  else if (ttf > robot_max_time)
  { 
    Serial.println("robot");  

    //Gathering the variable from the serial comm.
    while(true)
    {
      if(Serial.available() > 0)
      { 
        place = Serial.readStringUntil('\n'); 
        break;
      }  
    }
  
  }
  
  //This now will display the place in the lcd
  lcd_display();

  //Step7: Constantly check if time to fill has been reached or not
  while(true)
  {
    int elapsed_seconds = (millis()/1000) - start_seconds;

    if((ttf - elapsed_seconds) <= 5)
    {
      // check if the motor is still on
      if(digitalRead(DC_Motor) ==  1)
      {
        //Used serial comm. to stop the motor
        prediction = "False";
        Serial.println(prediction);
        Serial.println("stop");
        break;
      }

      // if motor is already off
      else if(digitalRead(DC_Motor) == 0)
      { 
        Serial.println("stopped");
        prediction = "True"; 
        Serial.println(prediction);
        break;
      }
    }
    delay(200);
  }
  
  lcd_display();
  
}

void loop()
{ 
}

void lcd_display()
{
  LiquidCrystal_I2C lcd(0x27, 16, 2);

  byte drop[8] = {
    0b00000,0b00100,0b01110,0b11111,
    0b11111,0b11111,0b01110,0b00000
  };

  byte alert[8] = {
    0b00100,0b01110,0b01110,0b01110,
    0b01110,0b11111,0b00000,0b00100
  };

  byte tick[8] = {
    0b00000,0b00000,0b00001,0b00011,
    0b10110,0b11100,0b01000,0b00000
  };

  byte cross[8] = {
    0b00000,0b10001,0b11011,0b01110,
    0b01110,0b11011,0b10001,0b00000
  };

  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();

  lcd.createChar(0,drop);
  lcd.createChar(1,alert);
  lcd.createChar(2,tick);
  lcd.createChar(3,cross); 

  lcd.home();
  
  if(flowRate == 0.0) {
    lcd.print(" 0.00ml/s ");
  }
  else {
    lcd.print(" ");
    lcd.print(flowRate);
    lcd.print("ml/s ");
  }

  if(left_volume == 0) {
    lcd.print(left_volume);
    lcd.print("L");
  }
  else {
    lcd.print(left_volume/1000);
    lcd.print("L");
  }
  
  lcd.setCursor(0,1);
  lcd.write(1);
  
  if (ttf == 0) {
    lcd.print("TTF");
  }
  else{ 
    lcd.print(ttf);  
  }
  
  if(place=="")
  { 
    lcd.setCursor(8,1);
    lcd.print("Place"); 
  }

  else if(place == "Hall") {
    lcd.setCursor(8,1);
    lcd.print(place);
  }

  else if(place=="Balcony" || place=="Bedroom")
  {
    lcd.setCursor(7,1);
    lcd.print(place);
  }
  
  if(prediction=="False")
  {
    lcd.setCursor(15,1);
    lcd.write(3);  
  }
  
  else if(prediction=="True")
  {
    lcd.setCursor(15,1);
    lcd.write(2); 
  }
}
