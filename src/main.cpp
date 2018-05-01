#include <Arduino.h>

static const unsigned gatePin = 13;

void press(int pitch) {
  digitalWrite(gatePin, HIGH);
}

void release() {
  digitalWrite(gatePin, LOW);
}

void play(int pitch, int length) {
  press(pitch);
  delay(length);
  release();
}

void setup()
{
  pinMode(gatePin, OUTPUT);
}

void loop()
{
}