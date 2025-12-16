// src/config.h
#pragma once

// Pin komponen
constexpr int PIN_BUZZER = 33;
constexpr int PIN_IR     = 34;
constexpr int PIN_SERVO  = 32;
constexpr int PIN_LED_G  = 5;
constexpr int PIN_LED_R  = 4;
constexpr int PIN_BUTTON = 35;

// OLED
constexpr int SCREEN_WIDTH  = 128;
constexpr int SCREEN_HEIGHT = 64;
constexpr int OLED_RESET    = -1;
constexpr int SCREEN_ADDRESS = 0x3C;

// WiFi & MQTT
constexpr const char* WIFI_SSID     = "P";
constexpr const char* WIFI_PASS     = "13062006";
constexpr const char* MQTT_SERVER   = "202.10.38.211";
constexpr int         MQTT_PORT     = 1883;

// MQTT topics
constexpr const char* TOPIC_STATUS       = "medicinebox/status";
constexpr const char* TOPIC_EVENT_OBAT   = "medicinebox/event/obat";
constexpr const char* TOPIC_EVENT_TOMBOL = "medicinebox/event/tombol";
constexpr const char* TOPIC_EVENT_WAKTU = "medicinebox/event/waktu";