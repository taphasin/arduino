#include <Wire.h>
#define SLAVE_ADDR 1
char text[100];
char sent_text[] = "TOKEN#0#";

void setup()
{
  Wire.begin(SLAVE_ADDR);
  Serial.begin(9600);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop()
{
   delay(500);
}

void receiveEvent(int bytes)
{
  for(int i=0;i<bytes;i++)
  {
    text[i] = Wire.read();
  }
  Serial.println(String("Byte = ")+bytes);
  Serial.println(String("I recieve:")+text);
}

void requestEvent()
{
  
  Wire.write(sent_text);
  
  Serial.print("I sent: ");
  Serial.println(sent_text);
  
}
