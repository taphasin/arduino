#include <Wire.h>
#define SLAVE_ADDR 1
char text[] = "Token#0#";
static char message[100];
static unsigned int message_pos = 0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  while (Serial.available() > 0)
  {
    char inByte = Serial.read();
    
    if ( inByte != '\n')
    {
      message[message_pos] = inByte;
      message_pos++;
    }
    else
    {
      message[message_pos] = '\0';
      //Serial.println(message);
      message_pos = 0;
    }
  }
  if(message[0] != '\0')
  {
    
    text[6] = '1'; 
  }
  delay(500);
  
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(text);
  Wire.write(message);
  Wire.endTransmission();

  
  Serial.print(text);
  Serial.println(message);

  
  Wire.requestFrom(SLAVE_ADDR,9);
  if(Wire.available()!=0)
  {  
    
    for(int i=0;i<9;i++)
    {
      text[i] = Wire.read();
      message[0] = '\0';
      Serial.println(i);
    }
    Serial.println(text);
 
  }
}

//void receiveEvent(int byte)
//{
//  Serial.println("Recieve messag! :  ");
//  
//  for(int i=0;i<byte;i++)
//  {
//    text[i] = Wire.read();
//  }
//  
//  if(text[8] =='1' )      //non chat to me
//  {
//    Serial.println(text);
//  }
}
//
//void requestEvent()
//{
//
//}
