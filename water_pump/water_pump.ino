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
#define WATERING_DURATION (65 / SLEEP_DURATION) // seconds
#define WATERING_PERIOD (( (3*60) / SLEEP_DURATION) - WATERING_DURATION) // (60 * 60 * 24 * 3) // seconds

void setup () {
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  
  digitalWrite(LED_PIN, LOW);
  digitalWrite(PUMP_PIN, LOW);
  
  for (int period_counter = 0; period_counter < WATERING_PERIOD; period_counter++) {
    // Sleep for 8 s with ADC module and BOD module off
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
  
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(PUMP_PIN, HIGH);
  
  for (int duration_counter = 0; duration_counter < WATERING_DURATION; duration_counter++) {
    // Sleep for 8 s with ADC module and BOD module off
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}
