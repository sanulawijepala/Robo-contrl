#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>

// Network credentials
const char* ssid = "nien";
const char* password = "nien";

byte R_leg_F = 4 ;//right leg forward motor pin
byte R_leg_B = 16 ;//right leg backward motor pin

byte L_leg_F = 17 ;// left leg forward motor pin
byte L_leg_B = 5 ;// left leg backward motor pin

int step_time = 100;//the time a motor is active in a step

AsyncWebServer server(80);

void forw(int steps);
void back(int steps);
void left(int steps;
void right(int steps);
void killyourself();


void setup(){

  // Serial port for debugging purposes
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false);
  });

// Route the responses respectively

  server.on("/F", HTTP_GET, [](AsyncWebServerRequest *request){
    forw();    
    request->send(SPIFFS, "/index.html", String(), false);
  });
  
  server.on("/B", HTTP_GET, [](AsyncWebServerRequest *request){
    back();    
    request->send(SPIFFS, "/index.html", String(), false);
  });

  server.on("/L", HTTP_GET, [](AsyncWebServerRequest *request){
    left();    
    request->send(SPIFFS, "/index.html", String(), false);
  });

  server.on("/R", HTTP_GET, [](AsyncWebServerRequest *request){
    right();    
    request->send(SPIFFS, "/index.html", String(), false);
  });

  server.on("/S", HTTP_GET, [](AsyncWebServerRequest *request){
    killyourself();    
    request->send(SPIFFS, "/index.html", String(), false);
  });

  // Start server
  server.begin();
}

void loop() {
  
}

void forw(int steps) {
  digitalWrite(R_leg_F, HIGH);
  digitalWrite(R_leg_B, LOW);
  digitalWrite(L_leg_F, HIGH);
  digitalWrite(L_leg_B, LOW);

  Delay = steps * step_time;
  
  delay(Delay);

  killyourself();

}

void back(int steps) {
  digitalWrite(R_leg_F, LOW);
  digitalWrite(R_leg_B, HIGH);
  digitalWrite(L_leg_F, LOW);
  digitalWrite(L_leg_B, HIGH);

  Delay = steps * step_time;
  
  delay(Delay);

  killyourself();

}

void left(int steps) {
  digitalWrite(R_leg_F, HIGH);
  digitalWrite(R_leg_B, LOW);
  digitalWrite(L_leg_F, LOW);
  digitalWrite(L_leg_B, HIGH);

  Delay = steps * step_time;
  
  delay(Delay);

  killyourself();

}

void right(int steps) {
  digitalWrite(R_leg_F, LOW);
  digitalWrite(R_leg_B, HIGH);
  digitalWrite(L_leg_F, HIGH);
  digitalWrite(L_leg_B, LOW);

  Delay = steps * step_time;
  
  delay(Delay);

  killyourself();

}

void killyourself() {
  digitalWrite(R_leg_F, LOW);
  digitalWrite(R_leg_B, LOW);
  digitalWrite(L_leg_F, LOW);
  digitalWrite(L_leg_B, LOW);

}
