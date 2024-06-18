#define LED_W_G 6
#define LED_W_Y 5
#define LED_W_R 4
#define WEST_BUTTON_PIN 2

#define LED_S_G 10
#define LED_S_Y 9
#define LED_S_R 8
#define SOUTH_BUTTON_PIN 3

#define LED_C_R 11
#define LED_C_G 12
#define CROSS_BUTTON_PIN 12

#define goN 0
#define waN 1
#define goE 2
#define waE 3
#define goC 4

#define a1H 5
#define a2L 6
#define a3H 7
#define a4L 8
#define a5H 9
#define a6L 10

struct State {
  unsigned long ST_Out;    // 6-bit pattern to street output 
  unsigned long Time;      // delay in ms units
  unsigned long Next[8];};// next state for inputs 0,1,2,3

typedef const struct State SType;

SType FSM[11]={
  {B10100001,2000,{goN, waN, goN, waN, waN, waN, waN, waN}}, //goN B10100001
  {B10100010,500 ,{goE, goE, goE, goE, goC, goC, goC ,goE}}, //waN B10100001
  {B10001100,2000,{goE, goE, waE, waE, waE, waE, waE, waE}}, //goE B10001100
  {B10010100,500 ,{goN, goN, goN, goN, goC, goC, goC, goC}}, //waE B10010100
  
  {B01100100,2000,{goC, a1H, a1H, a1H, goC, a1H, a1H, a1H}}, //goC
  {B00100100,300 ,{a2L, a2L, a2L, a2L, a2L, a2L, a2L, a2L}}, //a1H 00100100
  {B01100100,300 ,{a3H, a3H, a3H, a3H, a3H, a3H, a3H, a3H}}, //a2L 10100100
  {B00100100,300 ,{a4L, a4L, a4L, a4L, a4L, a4L, a4L, a4L}}, //a3H
  {B01100100,300 ,{a5H, a5H, a5H, a5H, a5H, a5H, a5H, a5H}}, //a4H
  {B00100100,300 ,{a6L, a6L, a6L, a6L, a6L, a6L, a6L, a6L}}, //a5L
  {B01100100,300 ,{goN, goE, goN, goN, goN, goE, goN, goN}}  //a6H
};

unsigned long S = 0; // index to the current state 

void setup()
{
  pinMode(LED_W_R, OUTPUT);
  pinMode(LED_W_Y, OUTPUT);
  pinMode(LED_W_G, OUTPUT); 
  pinMode(WEST_BUTTON_PIN, INPUT); 
  
  pinMode(LED_S_R, OUTPUT);
  pinMode(LED_S_Y, OUTPUT);
  pinMode(LED_S_G, OUTPUT); 
  pinMode(SOUTH_BUTTON_PIN, INPUT); 
  
  pinMode(LED_C_R, OUTPUT);
  pinMode(LED_C_G, OUTPUT);
  pinMode(CROSS_BUTTON_PIN, INPUT);
}
int input, input1, input2, input3;

void loop() 
{
  digitalWrite(LED_S_G, FSM[S].ST_Out & B00000001);
  digitalWrite(LED_S_Y, FSM[S].ST_Out & B00000010);
  digitalWrite(LED_S_R, FSM[S].ST_Out & B00000100);
  digitalWrite(LED_W_G, FSM[S].ST_Out & B00001000);
  digitalWrite(LED_W_Y, FSM[S].ST_Out & B00010000);
  digitalWrite(LED_W_R, FSM[S].ST_Out & B00100000);

  //cross
  digitalWrite(LED_C_G, FSM[S].ST_Out & B10000000);
  digitalWrite(LED_C_R, FSM[S].ST_Out & B01000000);
  
  delay(FSM[S].Time);
  
  input2 = digitalRead(SOUTH_BUTTON_PIN);
  input1 = digitalRead(WEST_BUTTON_PIN);
  input3 = digitalRead(13);
  
  input = (input3*4)+(input2*2)+(input1);
  
  S = FSM[S].Next[input]; 
}
