#include <Wire.h>

#define MASTER_ADDR 0
#define SLAVE_ADDR_1 1

char text[100];
static char message[3];
static unsigned int message_pos = 0;
void setup()
{
  char text[100];
  Wire.begin(SLAVE_ADDR_1);
  Serial.begin(9600);
     
   Wire.onReceive(receiveEvent);
   Wire.onRequest(requestEvent);
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
}


void receiveEvent(int byte)
{
  Serial.println("Recieve messag! :  ");
  
  for(int i=0;i<byte;i++)
  {
    text[i] = Wire.read();
  }
  
  if(text[8] =='1' )      //non chat to me
  {
  Serial.println(text);
  }
}


void requestEvent()
{
  Serial.println(text[8]);
  if(text[8]== '1' )
  {
    if(sizeof(message) != 0)
    {
      for(int y = 9; 11 >= y; y++)
      {
        text[y] = Serial.read();
        message[y - 9] = '\0';
      }
    }
    else
    {
      text[6] = '0';
      for(int i=8;i<100;i++)
      {
        text[i]='\0';
      }
    }
  }
  Serial.print("send : ");
  Serial.println(text);
  Wire.write(text);
}
