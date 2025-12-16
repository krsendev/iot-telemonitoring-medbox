// list library yang dipakai
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>
#include <RTClib.h>
#include <WiFi.h>
#include <PubSubClient.h>

// list pin komponen
#define pinBuzzer 33
#define pinIR 34
#define pinServo 32
#define pinLedG 5
#define pinLedR 4
#define pinButton 35

// Servo
Servo servo;

// RTC
RTC_DS3231 rtc;

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// konfigurasi wifi dan mqtt
const char* ssid = "P 5G";
const char* password = "16112018";
WiFiClient espClient;
PubSubClient client(espClient);

const char* mqtt_server = "192.168.16.23";
const int mqtt_port = 1883;
const char* topic_status = "device/status";
const char* topic_event_obat = "device/event/obat";
const char* topic_event_button = "device/event/button";

// fungsi untuk menghubungkan wifi
void setup_wifi(){
  Serial.print("Menghubungkan ke ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Wifi tersambung, IP Address: ");
  Serial.println(WiFi.localIP());
}

// fungsi komunikasi mqtt
void mqttCallback(char* topic, byte* payload, unsigned int length){
  Serial.print("(MQTT) Pesan dari topic: ");
  Serial.print(topic);
  Serial.print(" | payload: ");
  for(unsigned int i = 0; i < length; i++){
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

// jika jaringan reset dan mqtt reconnect
void reconnectMQTT(){
  while(!client.connected()){
    Serial.print("Menghubungkan ke MQTT...");
    String clientId = "ESP32";
    clientId += String(random(0xFFFF), HEX);

    if(client.connect(clientId.c_str())){
      Serial.println("Terhubung.");
      client.publish(topic_status, "Online");
    }else{
      Serial.print("Gagal, rc=" + String(client.state()));
      Serial.println("Coba lagi dalam 5s...");
      delay(5000);
    }
  }
}

// fungsi untuk menampilkan RTC
void RTC(){
  DateTime now = rtc.now();
  Serial.print(now.year());
  Serial.print("-");
  Serial.print(now.month());
  Serial.print("-");
  Serial.print(now.day());
  Serial.print(" ");
  Serial.print(now.hour()+":");
  Serial.print(":");
  Serial.print(now.minute());
  Serial.print(":");
  Serial.print(now.second());
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // setup Servo
  servo.attach(pinServo);

  // setup RTC
  if(!rtc.begin()){
    Serial.println("RTC tidak terdeteksi! :(");
    while(true);
  }
  // konfigurasi ketika nanti RTC kehilangan daya (mati listrik)
  if(rtc.lostPower()){
    Serial.print("RTC baru saja kehilangan daya, mengatur ulang waktu...");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // setup OLED 
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
    Serial.print("OLED gagal diinisialisasi :(");
    while(true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Hello World! ^.^");
  display.display();

  // pinmode komponen
  pinMode(pinBuzzer, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);
  pinMode(pinLedR, OUTPUT);
  pinMode(pinLedG, OUTPUT);
  pinMode(pinIR, INPUT);
}

void loop() {
  // membaca inputan sensor
  bool irState = digitalRead(pinIR);
  Serial.print("Sensor Infrared: " + String(irState));
}