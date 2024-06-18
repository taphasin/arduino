#include  <Wire.h>
#define computer_number 0

char text[100] = "token#0#";
char message[100];
int message_pos = 0;
int SLAVE_ADDR = 1;


void setup()
{
  Serial.begin(9600);

  Wire.begin();
}

// CHECK token is emthy or not
//   if Empty -> check that we have mssage to fill in token or not -> if have, fill to token
// send token to slave
// CLEAR token prepare for recieve from slave
// recieve token from slave
//   if this token is sent to me -> print via serial monitor, CLEAR toke to empty
// change slave address
void loop()
{
   if(text[6] == '0')      // if token is emthy
  {
    if (strlen(message) != 0)   // if we have message to fill
    {
      //fill message to token
      strcpy(text, message);        
       Serial.println("fill message[i]:");
      
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


  
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(text);
  Wire.endTransmission();
  Serial.print("send:");
  Serial.println(text);
  Serial.print("To: ");
  Serial.println(SLAVE_ADDR);
  Wire.requestFrom(SLAVE_ADDR, 100);


  
  int j = strlen(text);               //clear Text[] to emthy  prepare for recieve new Token
  Serial.println("Clear text[i]:");   
  for (int  i = 0; i <= j; i++)
  {
    text[i] = '\0';
    //Serial.print("Clear text[i]:");
    //Serial.println(text[i]);
  }


  
 int i = 0;
  //Serial.println(Wire.available());
  while(Wire.available() != 0)
  {
    int c = Wire.read();
    //Serial.println(c);
    if (c != 255)
    {
      text[i] = (char)c;
      i = i + 1;
    }
    
  }
         
 Serial.print("recieve:");
 Serial.println(text);
 Serial.print("from: ");
 Serial.println(SLAVE_ADDR);
 



  if(text[8] == computer_number +  '0')      // if this token is sent to me
  {
     //print message via serial monitor
    Serial.print("********************************************:");
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
         
  SLAVE_ADDR = SLAVE_ADDR % 2 + 1;

  delay(500);
}

void serialEvent()
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
    
  }

  if (Serial.available() == 0)
    {
      Serial.print("**you type message:");
      Serial.println(message);
    }
  message_pos = 0;
}
