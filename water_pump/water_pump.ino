/**
 * Great article about power efficiency with Arduino - http://donalmorrissey.blogspot.se/2010/04/sleeping-arduino-part-5-wake-up-via.html
 * The low power arduino library which is used for this project - http://www.rocketscream.com/blog/2011/07/04/lightweight-low-power-arduino-library/
 * Instead of external LED, the built-in LED on pin 13 will be used!
 * Transistor changed to S9013 which has higher Ic and runs the water pump with higher rpm.
 */

// MODIFY THESE VALUES:
// change the periods between watering events and the duration of the watering event
#define WATERING_DURATION_IN_SECONDS 20
#define WATERING_PERIOD_IN_DAYS 1
/////////////////////////////////////////////////////////////////////////////////////

#include "LowPower.h"

#define PUMP_PIN 3
#define LED_PIN 13

// measuring the actual time spent in sleep mode shows that it takes more than 8 sec.
#define SLEEP_DURATION 9.35

const unsigned long WATERING_DURATION_CYCLES = (unsigned long)WATERING_DURATION_IN_SECONDS / SLEEP_DURATION;
const unsigned long WATERING_PERIOD_CYCLES = ((unsigned long)WATERING_PERIOD_IN_DAYS*24*60*60) / SLEEP_DURATION;
boolean is_first_run = true;

void setup () {
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
}

inline void sleep(unsigned long cycles) {
  while (cycles > 0) {
    // Sleep for 8 s with ADC module and BOD module off
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    cycles--;
  }
}

inline void turn_on() {
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(PUMP_PIN, HIGH);
}

inline void turn_off() {
  digitalWrite(LED_PIN, LOW);
  digitalWrite(PUMP_PIN, LOW);
}

void test_run() {
  sleep(1);
  turn_on();
  sleep(1);
  turn_off();
}

void loop() {
  
  if (is_first_run) {
    test_run();
    is_first_run = false;
  }

  sleep(WATERING_PERIOD_CYCLES);

  // split watering in two, so that there is system cool down period inbetween
  // first half of the watering
  turn_on();
  sleep((WATERING_DURATION_CYCLES + 1) / 2);
  turn_off();

  // 30 seconds system cool down
  sleep(3);

  // second half of the watering
  turn_on();
  sleep(WATERING_DURATION_CYCLES / 2);
  turn_off();
}
