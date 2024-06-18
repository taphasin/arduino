#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <TimerOne.h>
#include <EEPROM.h>
#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);

int hr  = 0;
int min = 0;
int sec = 0;
int Shr  = 100;
int Smin = 100;
int Ssec = 100;
int Phr, Pmin, Psec;
bool loud = false;
bool key = true;

void count(){
  sec++;
  if (sec >= 60){
    min++;
    sec = 0;
    if (min >= 60){
      hr++;
      min = 0;
      if (hr >= 24){
        hr = 0;
      }
    }
  }
}

void setup()
{
  pinMode(2 ,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(11,OUTPUT);
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  hr  = EEPROM.read(1);
  min = EEPROM.read(2);
  sec = EEPROM.read(3);
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(count);
  Serial.begin(9600);
}

void loop()
{
  OLED.clearDisplay();
  OLED.setTextColor(WHITE); 
  OLED.setTextSize(2); 
  OLED.setCursor(15,9);
  OLED.println(hr);
  OLED.setCursor(37,9);
  OLED.println(":");
  OLED.setCursor(50,9);
  OLED.println(min);
  OLED.setCursor(72,9);
  OLED.println(":");
  OLED.setCursor(85,9);
  OLED.println(sec); 
  OLED.display();

  if (!digitalRead(2))
  {
    EEPROM.update(1, hr);
    EEPROM.update(2, min);
    EEPROM.update(3, sec);
    OLED.clearDisplay();
    OLED.setTextColor(WHITE); 
    OLED.setTextSize(2); 
    OLED.setCursor(15,9);
    OLED.println("SAVE");
    OLED.display();
  }
  
  if (Serial.available() > 0) {
    String str = Serial.readString();
    str.trim();
    for(int c = 1; c <= 6; c++){
      if (str[c] < '0' || str[c] > '9'){
        Serial.println("ERROR");
        key = false;
        c = 7;
      }
      else{
        key = true;
      }
    }

    Phr  = ((str[1] - 48) * 10) + (str[2] - 48);
    Pmin = ((str[3] - 48) * 10) + (str[4] - 48);
    Psec = ((str[5] - 48) * 10) + (str[6] - 48);

    if (key){
      if (Phr > 24 || Pmin > 60 || Psec > 60){
        Serial.println("ERROR");
        key = false;
      }
      else if (str[0] == 'A'){
        Shr  = Phr;
        Smin = Pmin;
        Ssec = Psec;
        Serial.println("Alarm set");
        Serial.print(Shr);
        Serial.print(" : ");
        Serial.print(Smin);
        Serial.print(" : ");
        Serial.println(Ssec);
      }
      else if (str[0] == 'T'){
        hr  = Phr;
        min = Pmin;
        sec = Psec;
        Serial.println("Time set");
        Serial.print(hr);
        Serial.print(" : ");
        Serial.print(min);
        Serial.print(" : ");
        Serial.println(sec);
      }
      else{
        Serial.println("ERROR");
      }
    }
  }

  if (hr == Shr && min == Smin && sec >= Ssec && sec <= (Ssec + 10)){
    if (loud == false){
      tone(11, 400);
      if (!digitalRead(10)){
        loud = true;
        noTone(11);
      }
    }
  }
  else if (hr != Shr || min != Smin || sec < Ssec || sec > (Ssec + 10)){
    loud = false;
    noTone(11);
  }

  if (analogRead(A1) >= 380){
      OLED.setRotation(2);
  }
  else{
      OLED.setRotation(0);
  }
}


