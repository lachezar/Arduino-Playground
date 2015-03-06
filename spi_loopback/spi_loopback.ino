#include <SPI.h>

// You need to wire pins 11 and 12 to enable SPI loopback - once you cut the connection the built-in LED will light up.

byte x, y;

void setup() {
  SPI.begin();
  pinMode(13, OUTPUT);
}

void loop() {
  y = SPI.transfer(x);
  if (x != y) {
    SPI.end();
    digitalWrite(13, HIGH);
    delay(1000);
    SPI.begin();
  }
  x++;
}

