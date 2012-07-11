/**
 * Simple program, that plays the super mario theme on piezo speaker and 
 * blinks LEDs and controls the LED brightness with a LDR and
 * has a potentiometer to slow down or speed up the music tempo.
 *
 * The music notes are borrowed from here: http://www.youtube.com/watch?v=VqeYvJpibLY
 *
 * Video clip demonstration of the code: 
 **/

#include <assert.h>

#include "pitches.h"

#include "super_mario_melody.h"
// defines int music[], int musicLength, char noteDurations[], int noteDuraionsLength

#define MUSIC_MULTIPLIER 31

int ledPin1 = 10;
int ledPin2 = 9;
int piezoPin = 5;
int potPin = 2;
int ldrPin = 0;

void setup() {
  assert(musicLength == noteDurationsLength);
  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(piezoPin, OUTPUT);
  
}

// this function works much better than the one described here:
// http://arduino.cc/en/Tutorial/Tone
void play(int note, int duration) {
  long hoisted = duration * 1000L;
  for (long i = 0; i < hoisted; i += note) {
    tone(piezoPin, note);
    delayMicroseconds(note);
  }
  noTone(piezoPin);
}

void loop() {

  for (int i = 0; i < musicLength; i++) {
    int k = map(analogRead(potPin), 0, 1023, MUSIC_MULTIPLIER-15, MUSIC_MULTIPLIER+15);
    int duration = k * noteDurations[i];
    
    int brightness = map(analogRead(ldrPin), 0, 1023, 100, 0);
    
    if (music[i] == 0) {
      analogWrite(ledPin2, brightness);
      delay(duration);
      analogWrite(ledPin2, 0);
    } else {
      analogWrite(ledPin1, brightness);
      play(music[i], duration);
      analogWrite(ledPin1, 0);
    }
    delay(duration >> 1);
  }
  
  delay(2000);
}

