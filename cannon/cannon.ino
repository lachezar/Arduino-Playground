#include <Servo.h>

#define SERVO_PIN 9
#define PUMP_PIN 3
#define LED_PIN 5

Servo servo;
char serialState;
int rotationAngle;
char isBlasting;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  servo.write(89);
  serialState = 0;
  rotationAngle = 0;
  isBlasting = 0;
  
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // data format: <rotation angle>,<is-it-blasting?>\n
  if (Serial.available() > 0) {
    char c = Serial.read();
    
    if (c == '\n') {
      int servoAngle = map(rotationAngle, 0, 1023, 182, 0); // my servo is lame, so the range is up to 182 :/
      servo.write(servoAngle);
      serialState = 0;
      rotationAngle = 0;
    } else if (c == ',') {
      serialState = 1;
    } else if (serialState == 0) {
      rotationAngle = rotationAngle * 10 + c - '0';
    } else if (serialState == 1) {
      isBlasting = c - '0';
    }
    
    digitalWrite(PUMP_PIN, isBlasting ? HIGH : LOW);
    digitalWrite(LED_PIN, isBlasting ? HIGH : LOW);
    
  }
}
