#include <WiFi.h>
#include <WebSocketsServer.h>

// Network credentials
const char* ssid = "YourWiFiNetwork";
const char* password = "YourWiFiPassword";

// Static IP configuration
IPAddress staticIP(192, 168, 1, 100);  // Choose an IP outside your router's DHCP range
IPAddress gateway(192, 168, 1, 1);     // Your router's IP
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);      // Optional: Google DNS
IPAddress secondaryDNS(8, 8, 4, 4);    // Optional: Backup DNS

WebSocketsServer webSocket(81);  // WebSocket server on port 81

void setup() {
  Serial.begin(115200);
  
  // Configure static IP
  if (!WiFi.config(staticIP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Connection established
  Serial.println("\nConnected successfully!");
  Serial.print("Network: ");
  Serial.println(ssid);
  Serial.print("Static IP: ");
  Serial.println(WiFi.localIP());
  Serial.print("WebSocket URL: ws://");
  Serial.print(WiFi.localIP());
  Serial.println(":81");

  // Start WebSocket server
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length) {
  switch (type) {
    case WStype_CONNECTED:
      Serial.printf("[%u] Connected!\n", num);
      break;
    case WStype_TEXT:
      // Handle incoming messages
      break;
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
  }
}
