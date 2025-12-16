// src/hardware.h
#pragma once
#include <Arduino.h>

void initHardware();
void updateOLEDClock();
bool readIR();
bool readButton();
void buzzerBeep(int durasiMs);
void setLedStatus(bool ok);
void printRTCtoSerial();
