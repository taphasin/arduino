#include <Arduino_FreeRTOS.h>
#include "queue.h"
#define RED 6
#define SW1 9
QueueHandle_t ledQueue;
void setup()
{
  Serial.begin(9600);
  ledQueue = xQueueCreate(5,sizeof(int32_t));
  xTaskCreate(vSenderTask,"Sender Task",100,NULL,1,NULL);
  xTaskCreate(vReceiverTask,"Receiver Task", 100,NULL, 1, NULL);
}

void vSenderTask(void *pvParameters)
{
  BaseType_t qStatus;
  int32_t valueToSend = 0;
  pinMode(SW1, INPUT_PULLUP); 
  while(1)
  {
    valueToSend = digitalRead(SW1);
    qStatus = xQueueSend(ledQueue,&valueToSend,0); 
    vTaskDelay(10);
  }
}

void vReceiverTask(void *pvParameters)
{
  int32_t valueReceived;
  BaseType_t qStatus;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
  pinMode(RED, OUTPUT); 
  while(1)
  {
    xQueueReceive(ledQueue,&valueReceived,xTicksToWait);
    Serial.print("Received value : ");
    Serial.println(valueReceived);
    digitalWrite(RED, valueReceived);
    vTaskDelay(1);
    }
  }
void loop(){}
