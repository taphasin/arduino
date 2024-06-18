int bitpat[] = {B11111001, B01001100, B01101000, B00111001, B00101010, B00001010, B11111000, B00001000, B00101000, B10001000, B10001010, B10001111};
const int segpin[] = {12, 11, 10, 9, 8, 7, 6, 5};
int num = 0;
int ran = 0;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  ran = random(1,10);
  for(int i = 0; i < 8; i++){
    pinMode(segpin[i], OUTPUT);
  }
  pinMode(3, INPUT);
  pinMode(2, INPUT);
}

void loop() {
  boolean bitset;
  for (int i = 0; i < 8; i++){
    bitset = bitRead(bitpat[num], i);
    digitalWrite(segpin[i], bitset); 
  }
  
  if (digitalRead(3) == HIGH){
    num++;
    while(digitalRead(3) == HIGH){
      delay(1);
    }
    if (num >= 9){
    num = 0; 
    }
    Serial.print(ran);
    Serial.println(num);
  }
  if (digitalRead(2) == HIGH){
    if (ran == num + 1){
      num = 9;
      ran = random(1,10);
      Serial.println("=");
    }
    else if (ran < num + 1){
      num = 10; 
      Serial.println("<");
    }
    else if (ran > num + 1){
      num = 11;
      Serial.println(">");
    }
    while(digitalRead(2) == HIGH){
      delay(1);
    }
  }
}

  
/*int number;
uint8_t bitPattern = 'B11101101';
const byte numPins = 8;
const int segmentPins[8] = {7, 12, 11, 5, 6, 8, 9, 10};

void setup() {
  Serial.begin(19200);
  for (int i = 0; i < numPins; i++){
    pinMode(segmentPins[i], OUTPUT);
  } 
}

void loop() {
  boolean isBitSet;
  Serial.println(isBitSet);
  delay(1000);
  for (int segment = 0; segment < 8; segment++){
    isBitSet = bitRead(bitPattern, segment);
    digitalWrite(segmentPins[segment], isBitSet);
  } 
}
*/
