#include <Arduino.h>
#include <WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const char* WIFI_SSID = "realme 6";
const char* WIFI_PASS = "";
const char* HOSTNAME = "TestESP";
#define PIN_RELAY 32

OneWire oneWire(4);
DallasTemperature sensors(&oneWire);
WiFiClient net;
MQTTClient iot;

float getAmbientTemperature()
{
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.println("DONE");

  float tempC = sensors.getTempCByIndex(0);

  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
    return tempC;
  } 
  else
  {
    Serial.println("Error: Could not read temperature data");
    return -127;
  }
}

void setRelay(bool state)
{
  digitalWrite(PIN_RELAY, state);
  Serial.print("Relay state changed to: "); 
  Serial.print(state);
  Serial.println();
}

bool getRelay()
{
  bool state = digitalRead(PIN_RELAY);
  Serial.print("Relay state is: "); 
  Serial.print(state);
  Serial.println();
  return state;
}

void setup() {
  Serial.begin(115200);
  pinMode(PIN_RELAY,OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  WiFi.setHostname(HOSTNAME);
  
  
  Serial.print("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("Febrian Eibim,Arya Aditya,Joao Baptista");
  Serial.println("WiFi connected successfully.");

  sensors.begin();

  iot.begind(IOTBROKER, net);
  iot.onMesseage(messeageReceived);

  Serial.print("connectig to IoT Broker");
  while (iot.connect("ESP32","public","pubic"));
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("");
  Serial.println("IoT Broker connected succesfully.");

  iot.subscribe("undiknas/ti/kelompok0/relay");
  iot.subscribe("undiknas/ti/+/chatroom");

  

}

void loop() {
  // put your main code here, to run repeatedly:
  float suhu = getAmbientTemperature();
  delay(3000);
  Client loop();
} 