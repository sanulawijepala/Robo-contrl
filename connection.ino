#include <WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "YourWiFiNetwork";
const char* password = "YourWiFiPassword";

WebSocketsServer webSocket(81); // Port 81

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    
    webSocket.begin();
}

void loop() {
    webSocket.loop();
}