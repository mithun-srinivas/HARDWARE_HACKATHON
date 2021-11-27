#define LED_BUILTIN 2
boolean BT_cnx = false;
#include <Wire.h>
#include <Adafruit_MLX90614.h>
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//websockets
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>



// Wifi Credentials
const char* ssid = "Mithun"; // Wifi SSID
const char* password = "mithu#12345"; //Wi-FI Password

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
  
  delay(2000); // wait for

  //address, port, and URL path 
  webSocket.begin("192.168.255.159", 8000, "/ws/10949"); 
  // webSocket event handler
  webSocket.onEvent(webSocketEvent);
  // if connection failed retry every 5s
  webSocket.setReconnectInterval(5000);


  
  // initialize digital pin 2 as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Adafruit MLX90614 test");
 
  mlx.begin();
  Serial.println(); // blank line in serial ...
  pinMode(41, INPUT); // Setup for leads off detection LO +
  pinMode(40, INPUT); // Setup for leads off detection LO -
  // initialize the serial BT communication:
}
 
void loop() {
  webSocket.loop(); // Keep the socket alive
  //
  float tempc;
  float tempf;
  float ecg;
  DynamicJsonDocument doc(1024);
  String payload;
  
  if((digitalRead(40) == 1)||(digitalRead(41) == 1)){
    Serial.println('!');
  }
  else{
    // send the value of analog input 0 to serial:
    //Serial.println(analogRead(A0));
    ecg=analogRead(A0);
    tempc=mlx.readObjectTempC();
    tempf=mlx.readObjectTempF();
    doc["ecg"] = analogRead(A0);
    doc["temp"]   = mlx.readObjectTempC();
    doc["spo2"] = mlx.readObjectTempF();
    serializeJson(doc, payload);
    webSocket.sendTXT(payload);
    
    //Serial.print("Ambient = ");
//    Serial.print(mlx.readAmbientTempC());
//    Serial.print("*C\tObject = ");
//    Serial.print(mlx.readObjectTempC()); Serial.println("*C");
//    Serial.print("Ambient = ");
//    Serial.print(mlx.readAmbientTempF());
//    Serial.print("*F\tObject = ");
//    Serial.print(mlx.readObjectTempF()); Serial.println("*F");
//     
   // Serial.println();
   // delay(20);
}
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
