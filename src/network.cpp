// src/network.cpp
#include "network.h"
#include "globals.h"
#include "config.h"

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    Serial.print("MQTT [");
    Serial.print(topic);
    Serial.print("] ");
    for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    }
    Serial.println();
}

void setupWiFi() {
    Serial.print("Menghubungkan ke ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println();
    Serial.print("WiFi OK, IP: ");
    Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
    while (!client.connected()) {
        Serial.print("Menghubungkan ke MQTT...");
        String clientId = "ESP32-MedBox-";
        clientId += String(random(0xFFFF), HEX);

        if (client.connect(clientId.c_str())) {
            Serial.println("OK");
            client.publish(TOPIC_STATUS, "online");
            // client.subscribe("medicinebox/cmd/#");
        } else {
            Serial.print("gagal, rc=");
            Serial.print(client.state());
            Serial.println(" coba lagi 5 detik");
            delay(5000);
        }
    }
}

void setupMQTT() {
    client.setServer(MQTT_SERVER, MQTT_PORT);
    client.setCallback(mqttCallback);
}

void mqttLoop() {
    if (!client.connected()) {
        reconnectMQTT();
    }
    client.loop();
}
