#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET -1
Adafruit_SSD1306 OLED(OLED_RESET);

int xb = 40 ,yb = 10;
int cx = 1, cy = 1;
int x0 = 30, x1 = 40;
int gg = 1;

void setup()
{
  Serial.begin(115200); 
  OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(11,OUTPUT);
  pinMode(7,INPUT_PULLUP);
  pinMode(6,INPUT_PULLUP);
}

void ball(int xb, int yb)
{
   OLED.drawPixel(xb, yb, WHITE);
   OLED.display();
}

void paddle(int x0, int x1)
{
  OLED.drawLine(x0,30,x1,30,WHITE);
  OLED.display();
}

void loop()
{
  Serial.print(yb);
  OLED.clearDisplay();
  if (digitalRead(7) == 0){
    x0 = x0 + 7;
    x1 = x1 + 7;
  }
  if (digitalRead(6) == 0){
    x0 = x0 - 7;
    x1 = x1 - 7;
  } 
  if (gg == 1){
    paddle(x0, x1);
    ball(xb, yb);
    OLED.display();
    if (xb > 127){
      cx = -1;
      tone(11,440,300);
    }
    else if (xb < 2){
      cx = 1;
      tone(11,440,300);
    }
    if (yb > 33){
      gg = 0;
    }
    else if (yb < 2){
      cy = 1;
      tone(11,440,300);
    }
    if (xb > x0 && xb < x1 && yb == 27){
      cy = -1;
      tone(11,440,300);
    }
    xb = xb + cx;
    yb = yb + cy;
  }
  if(gg == 0){
    OLED.clearDisplay();
    OLED.setTextColor(WHITE); 
    OLED.setCursor(10,0);
    OLED.setTextSize(2); 
    OLED.println("gameover"); 
    OLED.display();
   }
}
