#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

// Wifi Credentials
const char* ssid = "visitor"; // Wifi SSID
const char* password = "bmsce$1946"; //Wi-FI Password

WebSocketsClient webSocket; // websocket client class instance

StaticJsonDocument<100> doc; // Allocate a static JSON document

void setup() {
  // Connect to local WiFi
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print local IP address
  
  delay(2000); // wait for 2s

  //address, port, and URL path 
  webSocket.begin("10.60.2.245", 8000, "/ws/979797"); 
  // webSocket event handler
  webSocket.onEvent(webSocketEvent);
  // if connection failed retry every 5s
  webSocket.setReconnectInterval(5000);
}

void loop() {
  webSocket.loop(); // Keep the socket alive
  //
  webSocket.sendTXT("I LOVE YOU, PATS");
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  if (type == WStype_TEXT)
  {
    DeserializationError error = deserializeJson(doc, payload); // deserialize incoming Json String
    if (error) { // Print erro msg if incomig String is not JSON formated
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.c_str());
      return;
    }
    String clientId = doc["clientId"]; // String variable tha holds LED status
    String message = doc["message"]; // String variable tha holds LED status
    
    // Print the received data for debugging
    Serial.print(String(clientId)+" broadcasted ");
    Serial.print(message);
    Serial.println();
    // Send acknowledgement
    // webSocket.sendTXT("OK");
    
  }
}
