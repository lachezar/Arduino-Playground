/**
 * Great article about power efficiency with Arduino - http://donalmorrissey.blogspot.se/2010/04/sleeping-arduino-part-5-wake-up-via.html
 * The low power arduino library which is used for this project - http://www.rocketscream.com/blog/2011/07/04/lightweight-low-power-arduino-library/
 * Instead of external LED, the built-in LED on pin 13 will be used!
 * Transistor changed to S9013 which has higher Ic and runs the water pump with higher rpm.
 */

#include "LowPower.h"

#define PUMP_PIN 3
#define LED_PIN 13

// measuring the actual time spent in sleep mode shows that it takes more than 8 sec.
#define SLEEP_DURATION 9.35
#define WATERING_DURATION 93 / SLEEP_DURATION // seconds
#define WATERING_PERIOD 28 / SLEEP_DURATION // (60 * 60 * 24 * 3) // seconds

unsigned long duration_counter;
unsigned long period_counter;

void setup () {
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  duration_counter = 0;
  period_counter = 0;
}

void loop() {
  
  if (period_counter < WATERING_PERIOD) {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(PUMP_PIN, LOW);
    // Sleep for 8 s with ADC module and BOD module off
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    period_counter++;
  } else if (duration_counter < WATERING_DURATION) {
    digitalWrite(LED_PIN, HIGH);
    digitalWrite(PUMP_PIN, HIGH);
    // Sleep for 8 s with ADC module and BOD module off
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    duration_counter++;
  } else {
    period_counter = 0;
    duration_counter = 0;
  }
  
  /*delay(2500);
  digitalWrite(PUMP_PIN, HIGH);
  digitalWrite(LED_PIN, HIGH);
  delay(4000);
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  delay(2500);  */
}
