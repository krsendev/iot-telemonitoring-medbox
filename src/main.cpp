// src/main.cpp
#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "globals.h"
#include "hardware.h"
#include "network.h"

bool lastObatAda = true;
bool lastButton = false;
unsigned long lastUpdateMs = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  initHardware();
  setLedStatus(true);
  buzzerBeep(100);

  setupWiFi();
  setupMQTT();
}

void loop() {
  mqttLoop();

  unsigned long nowMs = millis();
  if (nowMs - lastUpdateMs > 1000) {
    lastUpdateMs = nowMs;
    printRTCtoSerial();
    updateOLEDClock();
  }

  bool obatAda = readIR();
  if (lastObatAda && !obatAda) {
    Serial.println("EVENT: Obat diambil");

    DateTime now = rtc.now();
    String payload = String("{\"event\":\"obat_diambil\",\"waktu\":\"") +
                    String(now.year()) + "-" +
                    String(now.month()) + "-" +
                    String(now.day()) + " " +
                    String(now.hour()) + ":" +
                    String(now.minute()) + ":" +
                    String(now.second()) + "\"}";
    client.publish(TOPIC_EVENT_OBAT, payload.c_str());
    buzzerBeep(50);
  }
  lastObatAda = obatAda;

  bool button = readButton();
  if (button && !lastButton) {
    Serial.println("Tombol ditekan");
    client.publish(TOPIC_EVENT_TOMBOL, "tombol_ditekan");
    buzzerBeep(30);
  }
  lastButton = button;

  delay(20);
}
