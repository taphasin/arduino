#include <Wire.h>


#define SLAVE_ADDR 1
#define computer_number 1

char text[100];
char message[100];
int message_pos = 0;

void setup()
{
  Serial.begin(9600);
  
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop()
{
  // get message[] from user through Serial.monitor input
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
    if (Serial.available() == 0)
    {
      Serial.print("**you type message:");
      Serial.println(message);
    }
  }
  message_pos = 0;

  delay(500);
}


//  GET token and CHECK  Emthy/sent to me/sent to other
//    if Empty -> check that we have mssage to fill in token or not-> if have, fill to token
//    if this token is sent to me -> PRINT via Serial monitor -> CLEAR token to empty
//    if this token is sent to other -> DO NOTHING
void receiveEvent(int byte)                
{
  Serial.println("Recieve messag!!");
  
  int j = strlen(text);             //clear Text[] to emthy  prepare for recieve new Token
  Serial.println("Clear text[i]:");
  for (int  i = 0; i <= j; i++)
  {
    //Serial.print("Clear text[i]:");
    text[i] = '\0';
    //Serial.println(text[i]);
  }

  
  for(int i=0; i<byte; i++)         //Get token
  {
    text[i] = Wire.read();
  }
  Serial.print("recieve:");
  Serial.println(text);


  if(text[6] == '0')      // if token is emthy
  {
    if (strlen(message) != 0)   // if we have message to fill
    {
      //fill message to token
      text[6] = '1';     
      text[7] = '#';
      text[8] =  message[8];        
      text[9] = '#';
      strcpy(text, message);  

      
      //clear message[] to emthy  prepare for recieve new message
       int j = strlen(message);    
       Serial.println("Clear message[i]:");         
       for (int  i = 0; i <= j; i++)
       {
          //Serial.print("Clear message[i]:");
          message[i] = '\0';
          //Serial.println(message[i]);
       }
    }
  }

  
  else if(text[8] == computer_number + '0' )      // if this token is sent to me
  {
     //print message via serial monitor
    //print message via serial monitor
    Serial.print("**********************************************:");
    for(int i = 10; i < sizeof(text); i++)
    {
    Serial.print(text[i]);
    }
    Serial.println();
    // CLEAR token to emthy
    text[6] = '0';
    for(int i=8;i<100;i++)
    {
      text[i]='\0';
    }
  }

}


void requestEvent()
{
  //send token to master
  Serial.print("send : ");
  Serial.println(text);
  Wire.write(text);
}
