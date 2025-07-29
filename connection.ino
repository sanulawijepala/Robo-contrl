#include <WiFi.h>
#include <WebSocketsServer.h>

// Network credentials
const char* ssid = "Network";
const char* password = "Password";

// Static IP configuration (if needed)
IPAddress staticIP(192, 168, 1, 100);  // Change to your desired IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);      // Optional
IPAddress secondaryDNS(8, 8, 4, 4);    // Optional

WebSocketsServer webSocket(81);  // WebSocket server on port 81

// Motor pins
byte R_leg_F = 4;   // Right leg forward motor pin

byte R_leg_B = 16;  // Right leg backward motor pin
byte L_leg_F = 17;  // Left leg forward motor pin
byte L_leg_B = 5;   // Left leg backward motor pin

void setup() {
  Serial.begin(115200);
  
  // Initialize motor pins
  pinMode(R_leg_F, OUTPUT);
  pinMode(R_leg_B, OUTPUT);
  pinMode(L_leg_F, OUTPUT);
  pinMode(L_leg_B, OUTPUT);

  // Configure static IP (optional)
  if (!WiFi.config(staticIP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("Failed to configure static IP, using DHCP");
  }

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected successfully!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

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
      handleCommand((char*)payload);
      break;
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
  }
}

void handleCommand(String command) {
  Serial.println("Received: " + command);
  
  if (command == "forward") {
    moveForward();
  } else if (command == "backward") {
    moveBackward();
  } else if (command == "left") {
    turnLeft();
  } else if (command == "right") {
    turnRight();
  } else if (command == "stop") {
    stopMotors();
  }
}

void moveForward() {
  digitalWrite(R_leg_F, HIGH);
  digitalWrite(R_leg_B, LOW);
  digitalWrite(L_leg_F, HIGH);
  digitalWrite(L_leg_B, LOW);
}

void moveBackward() {
  digitalWrite(R_leg_F, LOW);
  digitalWrite(R_leg_B, HIGH);
  digitalWrite(L_leg_F, LOW);
  digitalWrite(L_leg_B, HIGH);
}

void turnLeft() {
  digitalWrite(R_leg_F, HIGH);
  digitalWrite(R_leg_B, LOW);
  digitalWrite(L_leg_F, LOW);
  digitalWrite(L_leg_B, HIGH);
}

void turnRight() {
  digitalWrite(R_leg_F, LOW);
  digitalWrite(R_leg_B, HIGH);
  digitalWrite(L_leg_F, HIGH);
  digitalWrite(L_leg_B, LOW);
}

void stopMotors() {
  digitalWrite(R_leg_F, LOW);
  digitalWrite(R_leg_B, LOW);
  digitalWrite(L_leg_F, LOW);
  digitalWrite(L_leg_B, LOW);
}

/*read from websocket
  use direction and speed data accordingly
  
  */
