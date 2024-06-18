#include <Arduino_FreeRTOS.h>
#include "queue.h"
#define RED 5
#define YEL 4
#define GRE 3
#define SW1 12
#define SW2 11
#define SW3 10
QueueHandle_t RedQueue;
QueueHandle_t YelQueue;
QueueHandle_t GreQueue;



void setup()
{
  Serial.begin(9600);
  RedQueue = xQueueCreate(5,sizeof(int32_t));
  YelQueue = xQueueCreate(5,sizeof(int32_t));
  GreQueue = xQueueCreate(5,sizeof(int32_t));

  xTaskCreate(RedSenderTask,"RSender Task",100,NULL,1,NULL);
  xTaskCreate(RedReceiverTask,"RReceiver Task", 100,NULL, 1, NULL);
  
  xTaskCreate(YelSenderTask,"YSender Task",100,NULL,1,NULL);
  xTaskCreate(YelReceiverTask,"YReceiver Task", 100,NULL, 1, NULL);

  xTaskCreate(GreSenderTask,"GSender Task",100,NULL,1,NULL);
  xTaskCreate(GreReceiverTask,"GReceiver Task", 100,NULL, 1, NULL);
}


void RedSenderTask(void *pvParameters)
{
  BaseType_t qStatus;
  int32_t RvalueToSend = 0;
  pinMode(SW1, INPUT_PULLUP); 
  while(1)
  {
    RvalueToSend = !digitalRead(SW1);
    if (RvalueToSend == 1){
      qStatus = xQueueSend(RedQueue,&RvalueToSend,0); 
      vTaskDelay(1);
      while(!digitalRead(SW1) == 1){
       vTaskDelay(1);
      }
    }
  }
}

void RedReceiverTask(void *pvParameters)
{
  int32_t RvalueReceived;
  BaseType_t RqStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  unsigned long Redmil;
  int con = 0;
  pinMode(RED, OUTPUT); 
  while(1)
  {
    RqStatus = xQueueReceive(RedQueue,&RvalueReceived,xTicksToWait);
    if (RqStatus == pdPASS){
      Serial.print("in");
      Redmil = millis();
      con = con + 3000;
    }
    if (millis() - Redmil <= con){
      digitalWrite(RED, 1);
      Serial.print("run");
    }
    else{
      digitalWrite(RED, 0);
      con = 0;
    }
  }
}

void YelSenderTask(void *pvParameters)
{
  BaseType_t qStatus;
  int32_t YvalueToSend = 0;
  pinMode(SW2, INPUT_PULLUP); 
  while(1)
  {
    YvalueToSend = !digitalRead(SW2);
    if (YvalueToSend == 1){
      qStatus = xQueueSend(YelQueue,&YvalueToSend,0); 
      while(!digitalRead(SW2) == 1){
        vTaskDelay(1);
      }
    }
  }
}


void YelReceiverTask(void *pvParameters)
{
  int32_t YvalueReceived;
  BaseType_t qStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  bool state = false;
  int light = 0;
  unsigned long Yelmil = 0;
  pinMode(YEL, OUTPUT); 
  while(1)
  {
    qStatus = xQueueReceive(YelQueue,&YvalueReceived,xTicksToWait);
    if (qStatus == pdPASS){
      state = !state;
    }
    if (state == true){
      if (millis() - Yelmil > 50){
        digitalWrite(YEL, light);
        light = !light;
        Yelmil = millis();
      }
    }
    else{
      digitalWrite(YEL, 0);
    }
  }
}

void GreSenderTask(void *pvParameters)
{
  BaseType_t qStatus;
  int32_t GvalueToSend = 0;
  pinMode(SW3, INPUT_PULLUP); 
  while(1)
  {
    GvalueToSend = !digitalRead(SW3);
    if (GvalueToSend == 1){
      qStatus = xQueueSend(GreQueue,&GvalueToSend,0); 
      while(!digitalRead(SW3) == 1){
        vTaskDelay(1);
      }
    }
  }
}

void GreReceiverTask(void *pvParameters)
{
  int32_t GvalueReceived;
  BaseType_t GqStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  unsigned long Gremil = 0;
  int light = 1;
  bool state = false;
  int count = 0;
  pinMode(GRE, OUTPUT); 
  while(1)
  {
    GqStatus = xQueueReceive(GreQueue,&GvalueReceived,xTicksToWait);
    if (GqStatus == pdPASS && state == false){
      Serial.print("in");
      Gremil = millis();
      state = true;
    }
    if (state == true){
      if (millis() - Gremil > 500){
        digitalWrite(GRE, light);
        light = !light;
        Gremil = millis();
        count++;
        Serial.println(count);
      }
    }
    else{
      digitalWrite(GRE, 0);
    }
    if (count >= 6){
      state = false;
      count = 0;
    }
  }
}



void loop(){}
