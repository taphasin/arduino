bool bts1 = false;
bool bts2 = false;
bool bts3 = false;
bool sta = false;
bool sta3 = false;
long ldb1 = 0;
long ldb2 = 0;
long ldb3 = 0;


void setup() {
  pinMode(12, INPUT);
  pinMode(11, INPUT);
  pinMode(10, INPUT_PULLUP);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int b1 = digitalRead(12);
  int b2 = digitalRead(11);
  int b3 = digitalRead(10);
  
  if (b1 == HIGH)
  {
    ldb1 = millis();
    if (bts1 == false && sta == false)
    {
      digitalWrite(4, HIGH);
      bts1 = true;
       Serial.println("L");
    }
    else if (bts1 == true && sta == false)
    {
      bts1 = false;
      digitalWrite(4, LOW);
      Serial.println("H");
    }
    sta = true;
  }
  else
  {
    sta = false;
  }
/////////////////////////////////////////////////// 
  if (b2 == LOW && bts1 == false && bts3 == false)
  {
    ldb2 = millis();
    digitalWrite(3, HIGH);
    bts2 = true;
  }
///////////////////////////////////////////////////
/*if (b3 == LOW && bts1 == false)
  {
    ldb3 = millis();
    if (bts3 == false)
    {
      digitalWrite(2, HIGH);
      bts3 = true;
      while (digitalRead(10) == LOW)
      {
        delay(1);
      } 
    }
    else if (bts3 == true)
    {
      bts3 = false;
      digitalWrite(2, LOW);
      while (digitalRead(10) == LOW)
      {
        delay(1);
      } 
    }
  }
  */
  if (b3 == LOW && bts1 == false)
  {
    ldb3 = millis();
    if (bts3 == false && sta3 == false)
    {
      digitalWrite(2, HIGH);
      bts3 = true;
      Serial.println("H");
    }
    else if (bts3 == true && sta3 == false)
    {
      bts3 = false;
      digitalWrite(2, LOW);
      Serial.println("L");
    }
    sta3 = true;
  }
  else
  {
    sta3 = false;
  }
////////////////////////////////////////////////////
  if((millis() - ldb1) > 3000)
  {
    digitalWrite(4, LOW);
    bts1 = false;
  }
/////////////////////////////////////////////////
  if((millis() - ldb2) > 500 && (millis() - ldb2) < 999)
  {
    digitalWrite(3, LOW);
  }
  if((millis() - ldb2) > 1000 && bts2 != false && (millis() - ldb2) < 1999)
  {
    digitalWrite(3, HIGH);
    bts2 = false;
  }
  if((millis() - ldb2) > 2000)
  {
    digitalWrite(3, LOW);
  }
  //Serial.println((millis() - ldb2));
  
///////////////////////////////////////////////////////
  if((millis() - ldb3) > 3000)
  {
    digitalWrite(2, LOW);
    bts3 = false;
  }
}
