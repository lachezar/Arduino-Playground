#define PUMP_PIN 3
#define LED_PIN 5

void setup () {
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  delay(2500);
  digitalWrite(PUMP_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);
  delay(4000);
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  delay(2500);  
}
