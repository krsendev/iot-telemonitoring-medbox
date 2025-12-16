#include "hardware.h"
#include "globals.h"
#include "config.h"

void initRTC(){
    if(!rtc.begin()){
        Serial.println("RTC tidak terdeteksi! :(");
        while(true);
    }
    if(rtc.lostPower()){
        Serial.print("RTC kehilangan daya, mengatur ulang waktu...");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void initOLED(){
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
}

void initServo(){
    servo.attach(pinServo);
}

void initPins() {
    pinMode(pinBuzzer, OUTPUT);
    pinMode(pinButton, INPUT_PULLUP);
    pinMode(pinLedR, OUTPUT);
    pinMode(pinLedG, OUTPUT);
    pinMode(pinIR, INPUT);
}

void initHardware(){
    initServo();
    initRTC();
    initOLED();
    initPins();
}

void buzzerBeep(int durasiMs){
    digitalWrite(pinBuzzer, 1);
    delay(durasiMs);
    digitalWrite(pinBuzzer, 0);
}

void setLedStatus(bool ok){
    if(ok){
        digitalWrite(pinLedG, 1);
        digitalWrite(pinLedR, 0);
    }else{
        digitalWrite(pinLedG, 0);
        digitalWrite(pinLedR, 1);
    }
}

bool readIR(){
    int scan = digitalRead(pinIR);
    return(scan == 1);
}

bool readButton(){
    return(digitalRead(pinButton) == 0);
}

void printRTCtoSerial(){
    DateTime now = rtc.now();
    Serial.print("RTC: ");
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

void updateOLEDClock(){
    DateTime now = rtc.now();
    
}