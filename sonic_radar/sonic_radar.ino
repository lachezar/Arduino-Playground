#include <Servo.h>

const char triggerPin = 8;
const char echoPin = 9;

Servo servo;

void setup() {

  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  servo.attach(A0);
  Serial.begin(9600);
}

long echo() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH); // pull the Trig pin to high level for more than 10us impulse
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  long microseconds = pulseIn(echoPin, HIGH);   // waits for the pin to go HIGH, and returns the length of the pulse in microseconds
  return microseconds / (1000/34) / 2; // ((Duration of high level)/(Sonic : 29.4 cm/us))/2
}

void loop() {

  int angle = 600;
  int k = 5;
  
  while(1) {
    
    //servo.write(angle);
    servo.writeMicroseconds(angle);
    //delay(100);
    int dist = echo();
    //delay(100);
    
    Serial.print(k > 0 ? "+" : "-");
    Serial.print(angle-600);
    Serial.print(" ");
    Serial.print(dist);
    Serial.print(";");
    Serial.flush();
    
    if (angle < 600 || angle > 2400) {
      k = -k;
    }
    angle += k;
    
    delay(40);
  }
}
