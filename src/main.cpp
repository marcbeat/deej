#include <Arduino.h>
#include <RotaryEncoder.h>
#include "Keyboard.h"

#define VolBumpPerStep 4
const int VolStep = 1024/(100/VolBumpPerStep);

#define INC1 2
#define DEC1 3
#define INC2 4
#define DEC2 5
#define INC3 6
#define DEC3 7
#define INC4 8
#define DEC4 9

#define PB1 10
#define PB2 16
#define PB3 14
#define PB4 15

RotaryEncoder encoder1(INC1, DEC1, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder encoder2(INC2, DEC2, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder encoder3(INC3, DEC3, RotaryEncoder::LatchMode::TWO03);
RotaryEncoder encoder4(INC4, DEC4, RotaryEncoder::LatchMode::TWO03);

int statePB1;
int statePB2;
int statePB3;
int statePB4;

int oldStatePB1 = 0;
int oldStatePB2 = 0;
int oldStatePB3 = 0;
int oldStatePB4 = 0;

void buttonActions();
void updateVolumeLevels();

void setup() {
  pinMode(PB1, INPUT_PULLUP);
  pinMode(PB2, INPUT_PULLUP);
  pinMode(PB3, INPUT_PULLUP);
  pinMode(PB4, INPUT_PULLUP);

  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  updateVolumeLevels();
  buttonActions();
  delay(1);
}

void updateVolumeLevels() {
  static int pos1 = 0;
  static int pos2 = 0;
  static int pos3 = 0;
  static int pos4 = 0;

  encoder1.tick();
  encoder2.tick();
  encoder3.tick();
  encoder4.tick();

  static int vol1 = 0;
  static int vol2 = 0;
  static int vol3 = 0;
  static int vol4 = 0;

  int newPos1 = encoder1.getPosition();
  int newPos2 = encoder2.getPosition();
  int newPos3 = encoder3.getPosition();
  int newPos4 = encoder4.getPosition();

  if (pos1 != newPos1) {
    pos1 = newPos1;
    if ((int)(encoder1.getDirection()) > 0) {
      // Volume 1 Up
      vol1 = min(1023, vol1 + (VolStep-1));
    }
    else {
      // Volume 1 Down
      vol1 = max(0, vol1 - (VolStep-1));
    }
  }

  if (pos2 != newPos2) {
    pos2 = newPos2;
    if ((int)(encoder2.getDirection()) > 0) {
      // Volume 2 Up
      vol2 = min(1023, vol2 + (VolStep-1));
    }
    else {
      // Volume 2 Down
      vol2 = max(0, vol2 - (VolStep-1));
    }
  }

  if (pos3 != newPos3) {
    pos3 = newPos3;
    if ((int)(encoder3.getDirection()) > 0) {
      // Volume 3 Up
      vol3 = min(1023, vol3 + (VolStep-1));
    }
    else {
      // Volume 3 Down
      vol3 = max(0, vol3 - (VolStep-1));
    }
  }

  if (pos4 != newPos4) {
    pos4 = newPos4;
    if ((int)(encoder4.getDirection()) > 0) {
      // Volume 4 Up
      vol4 = min(1023, vol4 + (VolStep-1));
    }
    else {
      // Volume 4 Down
      vol4 = max(0, vol4 - (VolStep-1));
    }
  }
  Serial.println(vol1 + String("|") + vol2 + String("|") + vol3 + String("|") + vol4);
}

void buttonActions() {

  oldStatePB1 = statePB1;
  oldStatePB2 = statePB2;
  oldStatePB3 = statePB3;
  oldStatePB4 = statePB4;

  statePB1 = digitalRead(PB1);
  statePB2 = digitalRead(PB2);
  statePB3 = digitalRead(PB3);
  statePB4 = digitalRead(PB4);

  if (statePB1 == 0 && oldStatePB1 == 1) {
    // Rising Edge
    Keyboard.press(KEY_F13);

  }
  else if (statePB1 == 1 && oldStatePB1 == 0) {
    // Faling Edge
    Keyboard.release(KEY_F13);
  }

  if (statePB2 == 0 && oldStatePB2 == 1) {
    // Rising Edge
    Keyboard.press(KEY_F14);

  }
  else if (statePB2 == 1 && oldStatePB2 == 0) {
    // Faling Edge
    Keyboard.release(KEY_F14);
  }

  if (statePB3 == 0 && oldStatePB3 == 1) {
    // Rising Edge
    Keyboard.press(KEY_F15);

  }
  else if (statePB3 == 1 && oldStatePB3 == 0) {
    // Faling Edge
    Keyboard.release(KEY_F15);
  }

  if (statePB4 == 0 && oldStatePB4 == 1) {
    // Rising Edge
    Keyboard.press(KEY_F16);

  }
  else if (statePB4 == 1 && oldStatePB4 == 0) {
    // Faling Edge
    Keyboard.release(KEY_F16);
  }
}