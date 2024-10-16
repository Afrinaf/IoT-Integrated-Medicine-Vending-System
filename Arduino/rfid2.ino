 #include <MFRC522.h>
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#define SS_PIN 5
#define RST_PIN 0
const char* ssid = "";
const char* password = "";

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(230400);
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
    String jsonData = "{\"tag_number\":\"" + tagNumber + "\"}";
    Serial.println("Sending JSON data: " + jsonData);
    sendJsonData(jsonData);
    delay(2000);
  }
}

void sendJsonData(String jsonData) {
  HTTPClient http;
  http.begin("http://192.168.4.226:5000/update_tag"); // Replace with your Flask app IP
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(jsonData);
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String response = http.getString();
    Serial.println(response);
  } else {
    Serial.print("Error sending request. HTTP Response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
