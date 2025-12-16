#pragma once

// Semua Pin Komponen Taruh Disini
constexpr int pinBuzzer = 33;
constexpr int pinIR = 34;
constexpr int pinServo = 32;
constexpr int pinLedG = 5;
constexpr int pinLedR = 4;
constexpr int pinButton = 35;

// OLED
constexpr int SCREEN_WIDTH = 128;
constexpr int SCREEN_HEIGHT = 64;
constexpr int OLED_RESET = -1;
constexpr int SCREEN_ADDRESS = 0x3C;

// Wifi dan MQTT
constexpr const char* ssid = "";
constexpr const char* password = "";
constexpr const char* mqtt_server = "";
constexpr const int mqtt_port = 1883;

// MQTT Topic
constexpr const char* topic_status = "device/status";
constexpr const char* topic_event_obat = "device/event/obat";
constexpr const char* topic_event_button = "device/event/button";