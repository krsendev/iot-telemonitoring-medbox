#pragma once
#include <Arduino.h>

void initHardware();
void initPins();
void updateOLEDClock();
void initRTC();
void buzzerBeep(int durasiMs);
void setLedStatus(bool ok);
void printRTCtoSerial();
void initServo();
bool readIR();
bool readButton();