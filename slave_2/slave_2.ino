#include <Wire.h>
#define SLAVE_ADDR 8

#define index_Token_status 6
#define index_Token_target 8

#define My_computer_number 1

char Token[100] = "Token#0#"; 
char input_message_from_serial[100];    //use for store string from input serial monito
char Token_target;

void reset(char *s)
{
  // clear data in string
  int len = strlen(s);
  for (int j = 0; j < len; j++)
  {
    s[j] = '\0';
  }
  
  strcpy(s, "Token#0#");   //assign "Token#0#" prepare for sent
  Serial.print("Token AFTER reset: ");        //debug
  Serial.println(Token);                     //debug
}



void setup() 
{
  Serial.begin(9600);
  Serial.println("NANO Start!!");

  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() 
{
  Serial.println("*********START LOOP*************");    
  delay(1000);
  if (Token[index_Token_status] == '0')                 // If Token Empty
  {
    Serial.println("Token Emthy");
     
    //check that user want to chat??
    if (strlen(input_message_from_serial) == 0)       //user dont want to chat
    {
       Serial.println("user dont want to chat.");    // do notthing
    }
    if (strlen(input_message_from_serial) != 0)       //master want to sent text to slave
    {                                                 // start to assign text to Token...
      
     Serial.println("user  want to chat.");    
     Token[index_Token_status] = '1';                 // set Token's status NOT EMPTY
     Token[index_Token_target] = Token_target;        // set Token's target 
  
     strcat(Token, "#");                              //add '#' after target
     strcat(Token, input_message_from_serial);        //add message to Token
    }
  }
  else if(Token[index_Token_status] == '1')                  // If Token NOT EMPTY
  {
    Serial.println("OKEN NOT EMPTY");               // do notthing
  }
    

  Serial.print("Token which is being sent: ");      //debug
  Serial.println(Token);                            //debug



  Serial.println("Please Enter your computer number that want to talk with");
  Serial.println("----------------------------END void loop-----------------------------");
}





void receiveEvent()
{
 

  reset(Token);
  
  // store text from master to "Token"
  int i = 0;
  while (Wire.available() != 0)
  {
    Token[i] = (char)Wire.read();
    i = i + 1;
  }
  Serial.print("Recieve Token!!: ");              //debug
  Serial.println(Token);                          //debug


  //check Token that already get is storing message or not
  if(Token[index_Token_status] == '1')           //token is storing message
  {
    if (Token[index_Token_target] == My_computer_number)    //someone send message to this computer
    {
      Serial.print("Recieve Message!! : ");
      Serial.println(Token);                     //show part MESSAGE via Srrial monotor 
      reset(Token);                                            //reset Token to Token#0#
    }
    if (Token[index_Token_target] != My_computer_number)    //someone send message but not to this computer
    {
                                                            //do not thing
    }
  }
  if(Token[index_Token_status] == '0')            //Token is Empty
  {
                                                 //do not thing
  }
  
  
}

void requestEvent()
{
  Serial.println("RequestEvent!!!"); 

  
  Serial.print("Token length BEFORE write: ");        //debug
  Serial.println(strlen(Token));                       //debug
  
  Wire.write(Token);


  Serial.print("Token [");                            //debug
  Serial.print(Token);                                //debug
  Serial.println("] has been sent!!");                //debug
}






void serialEvent()      
{
  // clear data in  target_Token for prepare for fill target from user
  Token_target = '\0';
  
  // store target from input serial monotor to "target_Token"
  while (Serial.available() != 0)
  {
    Token_target = (char)Serial.read();
  }

  //ask user for fill type message
  Serial.println("Enter your message!!");
  while(Serial.available() == 0)
  {
    Serial.print(".");
    delay(200);
  }


  // clear data in  input_message_from_serial for prepare for fill new text from user
  int len = strlen(input_message_from_serial);
  for (int j = 0; j < len; j++)
  {
    input_message_from_serial[j] = '\0';
  }
 

  // store text from input serial monotor to "input_message_from_serial"
  int i = 0;
  while (Serial.available() != 0)
  {
    input_message_from_serial[i] = (char)Serial.read();
    i = i + 1;
  }
  Serial.print("Input : "); Serial.println(input_message_from_serial);
  
}
