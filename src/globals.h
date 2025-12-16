#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>
#include <RTClib.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"

extern Servo servo;
extern RTC_DS3231 rtc;
extern Adafruit_SSD1306 display;
extern WiFiClient espClient;
extern PubSubClient client;