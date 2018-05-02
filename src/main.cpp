#include <Arduino.h>
#include <Adafruit_MCP4725.h>
#include <MIDI.h>

static const unsigned gatePin = 13;

Adafruit_MCP4725 dac;
static const unsigned dacAddress = 0x62;

MIDI_CREATE_DEFAULT_INSTANCE();

void press(int pitch) {
  digitalWrite(gatePin, HIGH);
  int dacPitch = pitch/128.0 * 0xFFF; // rescale MIDI range to DAC range
  dac.setVoltage(dacPitch, false);
}

void release() {
  digitalWrite(gatePin, LOW);
}

void play(int pitch, int length) {
  press(pitch);
  delay(length);
  release();
}

void handleNoteOn(byte inChannel, byte inNote, byte inVelocity)
{
  press(inNote);
}

void handleNoteOff(byte inChannel, byte inNote, byte inVelocity)
{
  release();
}

void setup()
{
  // Gate
  pinMode(gatePin, OUTPUT);
  // CV dac
  dac.begin(dacAddress);
  dac.setVoltage(0, false);
  // MIDI
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop()
{
  MIDI.read();
}