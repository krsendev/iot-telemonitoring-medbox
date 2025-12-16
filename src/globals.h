// src/globals.h
#pragma once
#include <Arduino.h>
#include <ESP32Servo.h>
#include <RTClib.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "config.h"

extern Servo servo;
extern RTC_DS3231 rtc;
extern Adafruit_SSD1306 display;
extern WiFiClient espClient;
extern PubSubClient client;
