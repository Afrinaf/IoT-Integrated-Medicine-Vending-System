#include <MFRC522.h>
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>

#define SS_PIN 5
#define RST_PIN 0
const char* ssid = "Galaxy A53 5G1A11";
const char* password = "elitepro";

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
  WiFi.begin(ssid, password); // Replace with your WiFi SSID and password
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String tagNumber = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      tagNumber += String(mfrc522.uid.uidByte[i], HEX);
    }
    mfrc522.PICC_HaltA();
    
    Serial.println("od"+ tagNumber ); 
    String jsonData = "{\"tag_number\":\"" + tagNumber + "\"}";
    Serial.println("Sending JSON data: " + jsonData);
    sendJsonData(tagNumber);
    delay(2000);
  }
}

void sendJsonData(String tagNumber ) {
  HTTPClient http;
  String url = "/update_tag/" + tagNumber;
  http.begin("http://192.168.100.231:5000" + url); // Replace with your Flask app IP
  int httpResponseCode = http.GET();
  if (httpResponseCode == 200) {
    Serial.println("Request successful");
} 
  else {
    Serial.println("Error: " + String(httpResponseCode));
}
http.end();
}
