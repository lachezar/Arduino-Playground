int redPin = 10;
int yellowPin = 9;
int greenPin = 8;
int ledDelay = 10000;
int ledDelayYellow = 2000;


void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  
  digitalWrite(redPin, HIGH);
  delay(ledDelay);
  
  digitalWrite(yellowPin, HIGH);
  delay(ledDelayYellow);
  
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, LOW);
  digitalWrite(greenPin, HIGH);
  
  delay(ledDelay);
  
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, LOW);
  
  delay(ledDelayYellow);
  
  digitalWrite(yellowPin, LOW);
  digitalWrite(redPin, HIGH);
  
}

