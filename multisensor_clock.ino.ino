#include "pitches.h"
// notes in the melody:
int melody[] = {
  NOTE_D4, NOTE_G4, NOTE_B4, NOTE_G4, NOTE_D4, NOTE_B4, NOTE_G4, NOTE_B4,
  NOTE_G4, NOTE_D4, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_G4, NOTE_D4, NOTE_G4,
  NOTE_B4, NOTE_G4, NOTE_D4, NOTE_G4, NOTE_B4, NOTE_G4, NOTE_D4, NOTE_B4,
  NOTE_G4, NOTE_B4, NOTE_G4, NOTE_D4, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_G4,
  NOTE_D4, NOTE_D4, NOTE_G4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4,
  NOTE_D5, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_G4, NOTE_B4,
  NOTE_G4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_D5, NOTE_B4,
  NOTE_G4, NOTE_B4, NOTE_G4, NOTE_D4, NOTE_D4, NOTE_G4
};

// note durations: 1 = whole note, 2 = half note, 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 4, 8, 8, 4, 4, 4, 8,
  8, 4, 4, 4, 8, 8, 4, 4,
  2, 4, 4, 4, 8, 8, 4, 4,
  4, 8, 8, 4, 4, 4, 8, 8,
  4, 4, 3/2, 4, 4, 4, 4, 4,
  2, 4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 2, 4,
  4, 4, 4, 4, 4, 3/2
};

// notes in the melody:
int dragnetMelody[] = {
  NOTE_C3, NOTE_D3, NOTE_DS3, 0, NOTE_C3,
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int dragnetDurations[] = {
  3, 16, 8, 8, 8
};


int lightPin = 0;  //define a pin for Photo resistor

#include <LiquidCrystal.h>// include the library code:
// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;//LCD Pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

uint8_t degree[8] = {0x0E,0x0A,0x0E,0x00,0x00,0x00,0x00,0x00};  //a custom HEX character

//* Unnecessary for robot remove if needed
int ThermistorPin = 1; //Temp pin
int V1;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


#include "DHT.h"
// set the DHT Pin
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define trigPin 9 //Ultrasonic pin Tx
#define echoPin 8 //Ultrasonic pin Rx
/*
#include <IRremote.h>
int RECV_PIN = 10; //Rx infrared pin
IRrecv irrecv(RECV_PIN);
decode_results results;
*/

int backLight = 13;

int RGBLED = 10;


int buzzer = 6;

int start = 0;
int finish = 0;

int second=0, minute=37, hour=16; //start the time at...
int munit = 0;
int hunit = 0;
int valm=0;
int valh=0;

unsigned char hourCharA = 0x00;
unsigned char hourCharB = 0x00;
unsigned char hourCharC = 0x00;
unsigned char hourCharD = 0x00;
unsigned char hourCharE = 0x00;

unsigned char minCharA = 0x00;
unsigned char minCharB = 0x00;
unsigned char minCharC = 0x00;
unsigned char minCharD = 0x00;
unsigned char minCharE = 0x00;
unsigned char minCharF = 0x00;

unsigned char secCharA = 0x00;
unsigned char secCharB = 0x00;
unsigned char secCharC = 0x00;
unsigned char secCharD = 0x00;
unsigned char secCharE = 0x00;
unsigned char secCharF = 0x00;


uint8_t charHour[8] = {0x00, hourCharA, hourCharB, hourCharC, hourCharD, hourCharE, 0x00, 0x00};  //a custom HEX character
uint8_t charMin[8] = {0x00, minCharA, minCharB, minCharC, minCharD, minCharE, minCharF, 0x00};  //a custom HEX character
uint8_t charSec[8] = {0x00, secCharA, secCharB, secCharC, secCharD, secCharE, secCharF, 0x00};  //a custom HEX character

void setup()
{
    Serial.begin(9600);  //Begin serial communcation
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(backLight, OUTPUT);
    pinMode(RGBLED, OUTPUT);
    digitalWrite(backLight, HIGH);
  //  irrecv.enableIRIn(); // Start the receiver
    lcd.begin(16, 2);
    dht.begin();
    tone(buzzer, NOTE_C4, 500);

  lcd.createChar(1, charHour);
  lcd.createChar(2, charMin);
  lcd.createChar(3, charSec);
  lcd.write(byte(1));
  lcd.write(byte(2));
  lcd.write(byte(3));
  lcd.createChar(4, degree);
  lcd.home();
    
  delay(500);
  noTone(13);
}

void loop()
{
    
 /* lcd.setCursor(8, 0);
  if (irrecv.decode(&results)) {
    lcd.print("        ");
    lcd.setCursor(8, 0);
    lcd.print(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }

  */
    

        if (analogRead(lightPin) <= 150){
          digitalWrite(RGBLED, LOW);
          //tone(buzzer, NOTE_C3);
          start = 0;
          finish = finish + 1;
          //digitalWrite(backLight, LOW);
         }
        else if (analogRead(lightPin) >= 350){
          digitalWrite(backLight, HIGH);
          digitalWrite(RGBLED, HIGH);
          noTone(buzzer);
          finish = 0;
          start = start + 1;
         }

        if (start == 1 && hour >= 0 && hour < 12){
          startup();
         }
        else if(start > 10){
          start = 2;
         }
        if (finish == 1){
          shutOff();
         }
        else if(finish > 10){
          finish = 2;
         }
  
static unsigned long lastTick = 0; // set up a local variable to hold the last time we moved forward one second
// (static variables are initialized once and keep their values between function calls)
// move forward one second every 1000 milliseconds

if (millis() - lastTick >= 1000) {
  lastTick = millis();
  second++;
  upDate();

}

// move forward one minute every 60 seconds
  if (second >= 60) {
  minute++;
  second = 0; // reset seconds to zero
}

// move forward one hour every 60 minutes
if (minute >=60) {
  hour++;
  minute = 0; // reset minutes to zero
}

if (hour >=24) {
  hour=0;
  minute = 0; // reset minutes to zero
}

  munit = minute%10; //sets the variable munit and hunit for the unit digits
  hunit = hour%10;


  
 
  uint8_t charHour[8] = {0x00, hourCharA, hourCharB, hourCharC, hourCharD, hourCharE, 0x00, 0x00};  //a custom HEX character (Hour)
  uint8_t charMin[8] = {0x00, minCharA, minCharB, minCharC, minCharD, minCharE, minCharF, 0x00};  //a custom HEX character (Minute)
  uint8_t charSec[8] = {0x00, secCharA, secCharB, secCharC, secCharD, secCharE, secCharF, 0x00};  //a custom HEX character (Second)

  lcd.createChar(1, charHour); //Creates LCD clock characters that change over time 
  lcd.createChar(2, charMin);
  lcd.createChar(3, charSec);
  lcd.home(); //(reset(ish))
  lcd.setCursor(5,0);
  lcd.write(byte(1)); //print hour
  lcd.write(byte(2)); //print minute
  lcd.write(byte(3)); //print second
 
  
   // add one minute when pressed
  if(second == 60) {
   minute++;
   second=0;
   delay(250);
  }
  
   // add one hour when pressed
  if(minute == 60) {
   hour++;
   second=0;
   delay(250);
  }
  else  {   //********************************************************************IF YOU KNOW HOW TO SIMPLIFY THE NEXT 17 IF STATEMENTS, LET ME KNOW PLEZ********************************************************//
  if(second % 2){secCharA = 0x0E;} else{secCharA = 0x00;}       //************************YOU CAN COMMENT ON GITHUB FOR THE ABOVE STATEMENT**********************************************************************//
  if(second == 2||second==3||second==6||second==7||second==10||second==11||second==14||second==15||second==18||second==19||second==22||second==23||second==26||second==27||second==30||second==31||second==34||second==35||second==38||second==39||second==42||second==43||second==46||second==47||second==50||second==51||second==54||second==55||second==58||second==59){secCharB = 0x0E;} else{secCharB = 0x00;}
  if(second >= 4 && second < 8 || second >= 12 && second < 16 || second >= 20 && second < 24 || second >= 28 && second < 32 || second >= 36 && second < 40 || second >= 44 && second < 48 || second >= 52 && second < 56 || second >= 60 && second < 64){secCharC = 0x0E;} else{secCharC = 0x00;}
  if(second >= 8 && second < 16 || second >= 24 && second < 32 || second >= 40 && second < 48 || second >= 56 && second < 64){secCharD = 0x0E;} else{secCharD = 0x00;} 
  if(second >= 16 && second < 32 || second >= 48 && second < 64){secCharE = 0x0E;} else{secCharE = 0x00;}
  if(second >= 32 ){secCharF = 0x0E;} else{secCharF = 0x00;}

  //minutes units
  if(minute % 2) {minCharA = 0x0E;} else {minCharA = 0x00;}
  if(minute == 2||minute==3||minute==6||minute==7||minute==10||minute==11||minute==14||minute==15||minute==18||minute==19||minute==22||minute==23||minute==26||minute==27||minute==30||minute==31||minute==34||minute==35||minute==38||minute==39||minute==42||minute==43||minute==46||minute==47||minute==50||minute==51||minute==54||minute==55||minute==58||minute==59){minCharB = 0x0E;} else{minCharB = 0x00;}
  if(minute >= 4 && minute < 8 || minute >= 12 && minute < 16 || minute >= 20 && minute < 24 || minute >= 28 && minute < 32 || minute >= 36 && minute < 40 || minute >= 44 && minute < 48 || minute >= 52 && minute < 56 || minute >= 60 && minute < 64){minCharC = 0x0E;} else{minCharC = 0x00;}
  if(minute >= 8 && minute < 16 || minute >= 24 && minute < 32 || minute >= 40 && minute < 48 || minute >= 56 && minute < 64){minCharD = 0x0E;} else{minCharD = 0x00;} 
  if((minute >= 16 && minute < 32) || (minute >= 30 && minute < 40) || (minute >= 50 && minute < 60))  {minCharE = 0x0E;} else {minCharE = 0x00;}
  if(minute >= 32)  {minCharF = 0x0E;} else {minCharF = 0x00;}

  //hour units
  if(hour % 2) {hourCharA = 0x0E;} else {hourCharA = 0x00;}
  if(hour == 2||hour==3||hour==6||hour==7||hour==10||hour==11||hour==14||hour==15||hour==18||hour==19||hour==22||hour==23||hour==26||hour==27||hour==30||hour==31){hourCharB = 0x0E;} else{hourCharB = 0x00;}
  if(hour >= 4 && hour < 8 || hour >= 12 && hour < 16 || hour >= 20 && hour < 24 || hour >= 28 && hour < 32){hourCharC = 0x0E;} else{hourCharC = 0x00;}
  if(hour >= 8 && hour < 16 || hour >= 24 && hour < 32){hourCharD = 0x0E;} else{hourCharD = 0x00;} 
  if(hour >= 16 && hour < 32)  {hourCharE = 0x0E;} else {hourCharE = 0x00;}

  }
  if( hour == 16 && minute == 30 && second == 0){ //Alarm time in hours, minutes, and seconds
    wakeUp();
    second = second + 17;
  }

 }

 void upDate(){ //updates sensor values every second (see seconds protocol above to change)
   lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(analogRead(lightPin));//TBH I have no idea if this is candelas, Lumens, or nothing at all.
  
  V1 = analogRead(ThermistorPin);//I know that DHT11 has its own thermometer however I tried using it and TBH the one I had was crappy, off by 2-4 degrees, I know I could have corrected by manipulating the value but I am lazy.
  R2 = R1 * (1023.0 / (float)V1 - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 + 32.0; 
  
  lcd.setCursor(4,1);
  //int f = dht.readTemperature();
  lcd.print("Temp:");
  lcd.print(T);
  lcd.write(byte(4)); 
  lcd.print("F");

  int h = dht.readHumidity();
  lcd.setCursor(11, 0);
  lcd.print("H:");
  lcd.print(h);
  lcd.print("%");

 long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  lcd.setCursor(0, 0);
  if (distance >= 200 || distance <= 0){
    lcd.print("OOR  "); //stands for Out Of Range
}
  else {
    lcd.print(distance);
    lcd.print("cm");;
  }
 }

 void startup(){
  lcd.begin(16, 2);
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH);
  // put your setup code here, to run once:
  lcd.clear();
  lcd.print("Good morning ");
  wakeUp();// revellie ~16.5 seconds
  lcd.setCursor(0,1);
  lcd.print("ADMIN");
  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("There are 10");
  lcd.setCursor(0,1);
  lcd.println("types of people,");
  delay(2500);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("those who know");
  lcd.setCursor(0,1);
  lcd.print("binary and those who");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0,0);

  lcd.print("WhoDont");
  delay(750);
   lcd.print("Dont");
  delay(750);
  lcd.print("Dont");
  lcd.setCursor(0,1);
  delay(750);
  lcd.print("Dont");
  delay(750);
  lcd.print("Dont");
  delay(750);
  lcd.print("Dont");
  delay(750);
  lcd.print("Dont");
  delay(1500);
  lcd.clear(); //14.5 seconds
  second = second + 31;

 }

 void shutOff(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GOODBYE");
// iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 5; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int dragnetDuration = 1700 / dragnetDurations[thisNote];
    tone(6, dragnetMelody[thisNote], dragnetDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = dragnetDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(6);
    digitalWrite(backLight, LOW);
  }
 }

void wakeUp(){
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 62; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 800 / noteDurations[thisNote];
    tone(6, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(6);
  }
  
}





