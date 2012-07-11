int ledPin = 10;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  
  for (int x = 0; x < 3; x++) {
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  
  delay(100);
  
  for (int x = 0; x < 3; x++) {
    digitalWrite(ledPin, HIGH);
    delay(400);
    digitalWrite(ledPin, LOW);
    delay(100);
  }  

  delay(100);
  
  for (int x = 0; x < 3; x++) {
    digitalWrite(ledPin, HIGH);
    delay(150);
    digitalWrite(ledPin, LOW);
    delay(100);
  }
  
  delay(5000);
}

