// Based on http://arduino.cc/en/Tutorial/MotorKnob

#include <Stepper.h>

#define STEPS 100

Stepper stepper(STEPS, 11, 9, 10, 8); // the pins on my controller were all wrong 

int previousPos = 0;

void setup() {
  stepper.setSpeed(100);
  Serial.begin(9600);
}

void loop() {
  int pos = analogRead(2);
  Serial.println(pos);
  stepper.step(pos - previousPos);
  previousPos = pos;
}

