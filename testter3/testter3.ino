void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  pinMode(13, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  Serial.begin(9600);
}

int  state = 1;
bool done = false;
int  firstwav[] = {0, 0, 0};
int  secwav[]   = {0, 0, 0};
long tim;
int  four;
int f, s ,t, fo;

void loop() {
  if (!digitalRead(13)){
    tim = millis();
  }
  if (millis() - tim < 10){
     done = false;
     Serial.println("in");
  }
  if (millis() - tim > 10 && done == false){
     if (state == 1){
          firstwav[0] = !digitalRead(12);
          firstwav[1] = !digitalRead(11);
          firstwav[2] = !digitalRead(10);

          digitalWrite(4, firstwav[0]);
          digitalWrite(3, firstwav[1]);
          digitalWrite(2, firstwav[2]); 
          state = 2;
          Serial.println(firstwav[0]);
          Serial.println(firstwav[1]);
          Serial.println(firstwav[2]);
          Serial.println("wav");
          digitalWrite(5, LOW);
      }
      else if (state == 2){
          secwav[0] = !digitalRead(12);
          secwav[1] = !digitalRead(11);
          secwav[2] = !digitalRead(10);

          digitalWrite(4, secwav[0]);
          digitalWrite(3, secwav[1]);
          digitalWrite(2, secwav[2]); 
          state = 3;
      }
      else if (state == 3){
          f = firstwav[2] + secwav[2];
          s = firstwav[1] + secwav[1];
          t = firstwav[0] + secwav[0];
          fo = 0;

          Serial.println(t);
          Serial.println(s);
          Serial.println(f);
          Serial.println(fo);
          Serial.println("---------------");
          for (int a = 0; a <= 2; a++){
            Serial.print(firstwav[a]);
            Serial.print(secwav[a]);
          }
          Serial.println();
          if (t == 2){
            fo = 1;
            t = 0;
          }
          if (s == 2){
            t = 1;
            s = 0;
          }
          if (f == 2){
            f = 0;
            s = 1;
          }
          Serial.println(fo);
          Serial.println(t);
          Serial.println(s);
          Serial.println(f);
          Serial.println("---------------");
          state = 1;
          digitalWrite(5, fo);
          digitalWrite(4, t);
          digitalWrite(3, s);
          digitalWrite(2, f); 

          for(int i = 0; i <= 2; i++){
             firstwav[i] = 0;
             secwav[i] = 0;
          }
      }
      done = true;
  }
}
