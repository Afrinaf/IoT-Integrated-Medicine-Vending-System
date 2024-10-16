#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "";
const char* password = "";
const char* server_address = "http://127.0.0.1:5000";
const char* endpoint_path = "/data";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  HTTPClient http;
  http.begin("http://192.168.69.231:5000/data");
  int httpCode = http.GET();
   Serial.println(httpCode);
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println("Received data: " + payload);
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    int value = doc["value"];
    Serial.println("Parsed value: " + String(value));

    
    // do something with the value here
  } else {
    Serial.println("Failed to retrieve data");
  }

  http.end();
}

void loop() {
  // do something here
}
