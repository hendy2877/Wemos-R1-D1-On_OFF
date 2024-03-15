#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const int led1 = D5;
const int led2 = D4;

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "Hello from Wemos D1 R1!");
}

void handleLED() {
  String message;
  
  if (server.arg("pin") == "ON1") {
    digitalWrite(led1, HIGH);
    message = "LED 1 is ON";
  } else if (server.arg("pin") == "OFF1") {
    digitalWrite(led1, LOW);
    message = "LED 1 is OFF";
  } else if (server.arg("pin") == "ON2") {
    digitalWrite(led2, HIGH);
    message = "LED 2 is ON";
  } else if (server.arg("pin") == "OFF2") {
    digitalWrite(led2, LOW);
    message = "LED 2 is OFF";
  }
  
  server.send(200, "text/plain", message);
}

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
 Serial.println("Scanning available networks...");
  int numNetworks = WiFi.scanNetworks();
  Serial.println("Available networks:");

  for (int i = 0; i < numNetworks; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(WiFi.SSID(i));
  }

  Serial.println("Enter the SSID of the network you want to connect to:");
  while (Serial.available() == 0) {
    // wait for user input
  }

  String ssid = Serial.readStringUntil('\n'); // Membaca SSID dari Serial Monitor

  Serial.print("Enter the password for ");
  Serial.println(ssid);

  while (Serial.available() == 0) {
    // wait for user input
  }

  String password = Serial.readStringUntil('\n'); // Membaca password dari Serial Monitor

  WiFi.begin(ssid.c_str(), password.c_str()); // Menggunakan SSID dan password yang dimasukkan oleh pengguna

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  server.on("/", handleLED);  
  server.begin();
}

void loop() {
  server.handleClient();
}
