#include <Wire.h>
#define SLAVE_ADDR_1 1

char text[100];

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
    for(int i=8;i<100;i++)
    {
      text[i]='\0';
    }
    text[6]='0';
  }
  Serial.print("send : ");
  Serial.println(text);
  Wire.write(text);
}
