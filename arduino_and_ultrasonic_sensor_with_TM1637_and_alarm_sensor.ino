//-------------Libaries---------------------
#include <TM1637Display.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
//------------------------------------------


//-------------Variables TM1637----------------------------
#define CLK 2 // clock of TM1637 (4-digit-7-segmant-screen) {pirple}
#define DIO 9 // data input output of TM1637 (orange)
float ratio;
int amount;
float diff;
//---------------------------------------------------------


//-------------Ultrasonic Variables------------------------
int trigPin = 10; //pirple
int echoPin = 11; //black
int travelTime;
float distance;
//---------------------------------------------------------

//-------------Alarm device--------------------------------
int buzzer = 4; // white
int redLED = 5; // red
int greenLED = 13;// green
int yellowLED = 12; // yellow

//---------------------------------------------------------

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
//-------------Motor direction-----------------------------

int motorSpeed = 3; // broun
int motorDIR1 = 7; //white
int motorDIR2 = 8; //green

//---------------------------------------------------------
  
TM1637Display display(CLK, DIO); //object from TM1637Display Libary
LiquidCrystal_I2C lcd (0x27, 16,2); //0x27
RTC_DS3231 rtc;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(yellowLED,OUTPUT);
  pinMode(greenLED,OUTPUT);
  pinMode(redLED,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(motorDIR1,OUTPUT);
  pinMode(motorDIR2,OUTPUT);
  
    digitalWrite(greenLED,HIGH);
    digitalWrite(motorDIR1,HIGH);
    digitalWrite(motorDIR2,LOW);
    analogWrite(motorSpeed,0);// 0-255
    digitalWrite(redLED,HIGH);
  display.setBrightness(1);//0-7
  Serial.begin(115200); //Start serial monitor
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }

  if (rtc.lostPower()) 
  {
    Serial.println("RTC lost power, let's set the time!");
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
 
  lcd.init(); // to begin LCD screen
  lcd.backlight(); // set backlight
  
} // end setup function

void loop() {
  // put your main code here, to run repeatedly:
  DateTime now = rtc.now();
  
  

  //---------------------display time and date on serial--------
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour());
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

  //------------------------------------------------------------

  //---------------------trigger send signal---------------------
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);                       // delay in microseconds
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  //------------------------------------------------------------
  
  //---------------------calculate distance---------------------
  travelTime = pulseIn(echoPin,HIGH);         // calculate the travel time 
  distance = 0.034 * travelTime/2;            // we divide by 2 because the travel time is:                                            //the time that the signal is go and back
  Serial.println(distance);
  if (distance >= 9)
  {
    distance = 9;
  }
  if (distance < 4.62)
  {
    distance = 4.62;
  }
  
  
  //------------------------------------------------------------

  //---------------------display on TM1637----------------------
  diff = 9 - distance;
  Serial.println(diff);
  ratio = diff/4.38;  //calculate the amount of midecine
  Serial.print("the ratio is : ");
  Serial.println(ratio);
  if (ratio >= 0.98)
  {
    amount = 1000;
  }
  else if ((ratio >= 0.96) && (ratio < 9.8))
  {
    amount = 980;
  }
  else if ((ratio >= 0.94) && (ratio < 0.96))
  {
    amount = 960;
  }
  else if ((ratio >= 0.92) && (ratio < 0.94))
  {
    amount = 940;
  }
  else if ((ratio >= 0.90) && (ratio < 0.92))
  {
    amount = 920;
  }
  else if ((ratio >= 0.88) && (ratio < 0.90))
  {
    amount = 900;
  }
  else if ((ratio >= 0.86) && (ratio < 0.88))
  {
    amount = 880;
  }
  else if ((ratio >= 0.84) && (ratio < 0.86))
  {
    amount = 860;
  }
  else if ((ratio >= 0.82) && (ratio < 0.84))
  {
    amount = 840;
  }
  else if ((ratio >= 0.80) && (ratio < 0.82))
  {
    amount = 820;
  }
  else if ((ratio >= 0.78) && (ratio < 0.80))
  {
    amount = 800;
  }
  else if ((ratio >= 0.76) && (ratio < 0.78))
  {
    amount = 780;
  }
  else if ((ratio >= 0.74) && (ratio < 0.76))
  {
    amount = 760;
  }
  else if ((ratio >= 0.72) && (ratio < 0.74))
  {
    amount = 740;
  }
  else if ((ratio >= 0.70) && (ratio < 0.72))
  {
    amount = 720;
  }
  else if ((ratio >= 0.68) && (ratio < 0.70))
  {
    amount = 700;
  }
  else if ((ratio >= 0.66) && (ratio < 0.68))
  {
    amount = 680;
  }
  else if ((ratio >= 0.64) && (ratio < 0.66))
  {
    amount = 660;
  }
  else if ((ratio >= 0.62) && (ratio < 0.64))
  {
    amount = 640;
  }
  else if ((ratio >= 0.60) && (ratio < 0.62))
  {
    amount = 620;
  }
  else if ((ratio >= 0.58) && (ratio < 0.60))
  {
    amount = 600;
  }
  else if ((ratio >= 0.56) && (ratio < 0.58))
  {
    amount = 580;
  }
  else if ((ratio >= 0.54) && (ratio < 0.56))
  {
    amount = 560;
  }
  else if ((ratio >= 0.52) && (ratio < 0.54))
  {
    amount = 540;
  }
  else if ((ratio >= 0.50) && (ratio < 0.52))
  {
    amount = 520;
  }
  else if ((ratio >= 0.48) && (ratio < 0.50))
  {
    amount = 500;
  }
  else if ((ratio >= 0.46) && (ratio < 0.48))
  {
    amount = 480;
  }
  else if ((ratio >= 0.44) && (ratio < 0.46))
  {
    amount = 460;
  }
  else if ((ratio >= 0.42) && (ratio < 0.44))
  {
    amount = 440;
  }
  else if ((ratio >= 0.40) && (ratio < 0.42))
  {
    amount = 420;
  }
  else if ((ratio >= 0.38) && (ratio < 0.40))
  {
    amount = 400;
  }
  else if ((ratio >= 0.36) && (ratio < 0.38))
  {
    amount = 380;
  }
  else if ((ratio >= 0.34) && (ratio < 0.36))
  {
    amount = 360;
  }
  else if ((ratio >= 0.32) && (ratio < 0.34))
  {
    amount = 340;
  }
  else if ((ratio >= 0.30) && (ratio < 0.32))
  {
    amount = 320;
  }
  else if ((ratio >= 0.28) && (ratio < 0.30))
  {
    amount = 300;
  }
  else if ((ratio >= 0.26) && (ratio < 0.28))
  {
    amount = 280;
  }
  else if ((ratio >= 0.24) && (ratio < 0.26))
  {
    amount = 260;
  }
  else if ((ratio >= 0.22) && (ratio < 0.24))
  {
    amount = 240;
  }
  else if ((ratio >= 0.20) && (ratio < 0.22))
  {
    amount = 220;
  }
  else if ((ratio >= 0.18) && (ratio < 0.20))
  {
    amount = 200;
  }
  else if ((ratio >= 0.16) && (ratio < 0.18))
  {
    amount = 180;
  }
  else if ((ratio >= 0.14) && (ratio < 0.16))
  {
    amount = 160;
  }
  else if ((ratio >= 0.12) && (ratio < 0.14))
  {
    amount = 140;
  }
  else if ((ratio >= 0.10) && (ratio < 0.12))
  {
    amount = 120;
  }
  else if ((ratio >= 0.08) && (ratio < 0.10))
  {
    amount = 100;
  }
  else if ((ratio >= 0.06) && (ratio < 0.08))
  {
    amount = 80;
  }
  else if ((ratio >= 0.04) && (ratio < 0.06))
  {
    amount = 60;
  }
  else if ((ratio >= 0.02) && (ratio < 0.04))
  {
    amount = 40;
  }
  else if ((ratio >= 0.00) && (ratio < 0.02))
  {
    amount = 20;
  }
  else
  {
    amount = 0;
  }
  Serial.print("the amount of midicine is : ");
  Serial.println(amount);
  display.showNumberDec(amount, false);
  delay(2500);

  //------------------------------------------------------------

  //---------------------LCD I2C display------------------------
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Time: ");
  lcd.print(now.hour(),DEC);
  lcd.print(".");
  lcd.print(now.minute(),DEC);
  lcd.print(".");
  lcd.print(now.second(),DEC);
  lcd.setCursor(0,1);
  lcd.print("Date: ");
  lcd.print(now.day(),DEC);
  lcd.print("/");
  lcd.print(now.month(),DEC);
  lcd.print("/");
  lcd.print(now.year(),DEC);
  
  //------------------------------------------------------------
  
  //---------------------Alarm device---------------------------

 if(amount >=501)
 {
  digitalWrite(buzzer,LOW);
  digitalWrite(redLED,LOW);
  digitalWrite(yellowLED,LOW);
  digitalWrite(greenLED,HIGH);
  Serial.println("green LED has turned on you are in save area");
  Serial.println("************************");
 }
 
 else if((amount >= 200)&&(amount <= 500))
 {
  digitalWrite(buzzer,LOW);
  digitalWrite(redLED,LOW);
  digitalWrite(yellowLED,HIGH);
  digitalWrite(greenLED,LOW);
  Serial.println("yellow LED has turned on, Be careful, you are in a warn area");
  Serial.println("************************");
 }
 else
 {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Danger! you have");
  lcd.setCursor(0,1);
  lcd.print("last ");
  lcd.print(amount);
  lcd.print(" ml");
  digitalWrite(yellowLED,LOW);
  digitalWrite(greenLED,LOW);
  digitalWrite(redLED,HIGH);
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  digitalWrite(redLED,LOW);
  delay(500);
  digitalWrite(redLED,HIGH);
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  digitalWrite(redLED,LOW);
  delay(500);
  digitalWrite(redLED,HIGH);
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  digitalWrite(redLED,LOW);
  delay(500);
  Serial.print("Danger!,Danger!,Danger!,you have last ");
  Serial.print(amount);
  Serial.print(" of midecine");
  Serial.println("************************");
  
  
  
 }

 //--------------------------------------------------------------
 
 //-------------------water pump---------------------------------
  if (now.minute() == 3)
  {
    while (1)
    {
      
    
    analogWrite(motorSpeed,65);//0-255
    DateTime now = rtc.now();
  

  //---------------------display time and date on serial--------

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

  //------------------------------------------------------------

  //---------------------trigger send signal---------------------
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);                       // delay in microseconds
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  //------------------------------------------------------------
  
  //---------------------calculate distance---------------------
  travelTime = pulseIn(echoPin,HIGH);         // calculate the travel time 
  distance = 0.034 * travelTime/2;            // we divide by 2 because the travel time is:                                            //the time that the signal is go and back
  Serial.println(distance);
  
  //------------------------------------------------------------

  //---------------------display on TM1637----------------------
  
  diff = 9 - distance;
  Serial.println(diff);
  ratio = diff/5.19;  //calculate the amount of midecine
  Serial.print("the ratio is : ");
  Serial.println(ratio);
  amount = ratio * 1000 ;
  Serial.print("the amount of midicine is : ");
  Serial.println(amount);
  display.showNumberDec(amount, false);
  delay(3000);

  //------------------------------------------------------------

  //---------------------LCD I2C display------------------------

  lcd.setCursor(0,0);
  lcd.print("Time: ");
  lcd.print(now.hour(),DEC);
  lcd.print(".");
  lcd.print(now.minute(),DEC);
  lcd.print(".");
  lcd.print(now.second(),DEC);
  lcd.setCursor(0,1);
  lcd.print("Date: ");
  lcd.print(now.day(),DEC);
  lcd.print("/");
  lcd.print(now.month(),DEC);
  lcd.print("/");
  lcd.print(now.year(),DEC);
  
  
  //------------------------------------------------------------
  
  //---------------------Alarm device---------------------------

 if(amount >=501)
 {
  digitalWrite(buzzer,LOW);
  digitalWrite(redLED,LOW);
  digitalWrite(yellowLED,LOW);
  digitalWrite(greenLED,HIGH);
  Serial.println("green LED has turned on you are in save area");
  Serial.println("************************");
 }
 
 else if((amount >= 200)&&(amount <= 500))
 {
  digitalWrite(buzzer,LOW);
  digitalWrite(redLED,LOW);
  digitalWrite(yellowLED,HIGH);
  digitalWrite(greenLED,LOW);
  Serial.println("yellow LED has turned on, Be careful, you are in a warn area");
  Serial.println("************************");
 }
 else
 {
  digitalWrite(yellowLED,LOW);
  digitalWrite(greenLED,LOW);
  digitalWrite(redLED,HIGH);
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  digitalWrite(redLED,LOW);
  delay(500);
  digitalWrite(redLED,HIGH);
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  digitalWrite(redLED,LOW);
  delay(500);
  digitalWrite(redLED,HIGH);
  digitalWrite(buzzer,HIGH);
  delay(500);
  digitalWrite(buzzer,LOW);
  digitalWrite(redLED,LOW);
  delay(500);
  Serial.print("Danger!,Danger!,Danger!,you have last ");
  Serial.print(amount);
  Serial.print(" of midecine");
  Serial.println("************************");
  lcd.setCursor(0,0);
  lcd.print("Danger! you have");
  lcd.setCursor(0,1);
  lcd.print(amount);
  lcd.clear();
  
 }

 //--------------------------------------------------------------
    
  }
  }
}//end loop function
