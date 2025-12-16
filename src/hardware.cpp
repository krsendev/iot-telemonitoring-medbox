// src/hardware.cpp
#include "hardware.h"
#include "globals.h"
#include "config.h"

void initRTC() {
    if (!rtc.begin()) {
    Serial.println("RTC tidak terdeteksi! :(");
    while (true);
    }
    if (rtc.lostPower()) {
        Serial.println("RTC kehilangan daya, set ulang waktu...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void initOLED() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println("OLED gagal diinisialisasi :(");
        while (true);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Smart MedBox Init...");
    display.display();
}

void initServoMotor() {
    servo.attach(PIN_SERVO);
    servo.write(90); // misal posisi netral / stop
}

void initPins() {
    pinMode(PIN_BUZZER, OUTPUT);
    pinMode(PIN_LED_R, OUTPUT);
    pinMode(PIN_LED_G, OUTPUT);
    pinMode(PIN_IR, INPUT);
    pinMode(PIN_BUTTON, INPUT_PULLUP);
}

void initHardware() {
    initServoMotor();
    initRTC();
    initOLED();
    initPins();
}

void buzzerBeep(int durasiMs) {
    digitalWrite(PIN_BUZZER, HIGH);
    delay(durasiMs);
    digitalWrite(PIN_BUZZER, LOW);
}

void setLedStatus(bool ok) {
    if (ok) {
        digitalWrite(PIN_LED_G, HIGH);
        digitalWrite(PIN_LED_R, LOW);
    } else {
        digitalWrite(PIN_LED_G, LOW);
        digitalWrite(PIN_LED_R, HIGH);
    }
}

bool readIR() {
    int raw = digitalRead(PIN_IR);
    return (raw == LOW); // asumsi: LOW = objek ada
}

bool readButton() {
  return (digitalRead(PIN_BUTTON) == LOW); // INPUT_PULLUP -> ditekan = LOW
}

void printRTCtoSerial() {
    DateTime now = rtc.now();
    String waktu = String(now.year()) + "-" +
                String(now.month()) + "-" +
                String(now.day()) + " " +
                String(now.hour()) + ":" +
                String(now.minute()) + ":" +
                String(now.second());
    Serial.print("RTC: ");
    Serial.println(waktu);
}

void updateOLEDClock() {
    DateTime now = rtc.now();
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Smart Medicine Box");

    display.setCursor(0, 16);
    display.print(now.year());
    display.print("-");
    display.print(now.month());
    display.print("-");
    display.print(now.day());

    display.setCursor(0, 26);
    display.print(now.hour());
    display.print(":");
    display.print(now.minute());
    display.print(":");
    display.print(now.second());

    display.display();
}
