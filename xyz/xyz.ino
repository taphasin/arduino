void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int xaccel = analogRead(A0); 
  int yaccel = analogRead(A1); 
  int zaccel = analogRead(A2); 
  unsigned long timevar = millis();
  Serial.print(timevar);
  Serial.print(" ");
  Serial.print(xaccel); 
  Serial.print(" ");
  Serial.print(yaccel);
  Serial.print(" ");
  Serial.println(zaccel);
}
