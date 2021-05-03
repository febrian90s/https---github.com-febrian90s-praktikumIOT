#include <Arduino.h>
#include <wifi.h>

const char* WIFI_SSID = "realme 6";
const char* WIFI_PASS = "";
const char* HOSTNAME = "TestESP";

void setup() {

    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    WiFi.setHostname(HOSTNAME);
    
    Serial.print("connecting to wifi");
    while(WiFi.status() !=WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("");
    Serial.println("Wifi connected");
}

void loop() {

}