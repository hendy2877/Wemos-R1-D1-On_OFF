The project in MIT App Inventor for controlling Wemos outputs utilizes components such as buttons, labels, and settings tailored for managing LEDs via an ESP8266. 
Users can interact with the LEDs in real-time through the mobile app by employing buttons and settings for immediate control. 
Additionally, the project offers the functionality of uploading files and enables customization of the app screen appearance. 
This customization includes options like aligning the screen horizontally and vertically, choosing background colors and images, setting default text, screen animations, orientation, scrollability, and displaying or hiding the status bar. 
These features allow users to personalize the visual presentation of the app screen according to their preferences. 
Wemos D1 R1 is used with a relay to control the switching on and stopping using the C3198 transistor as the relay driver. The relay is connected to Wemos pins D5 and D4. These settings will be controlled via an application created with MIT App Inventor. Here is the program code for Wemos D1 R1:

```cpp
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

  String ssid = Serial.readStringUntil('\n'); // Read SSID from Serial Monitor

  Serial.print("Enter the password for ");
  Serial.println(ssid);

  while (Serial.available() == 0) {
    // wait for user input
  }

  String password = Serial.readStringUntil('\n'); // Reads the password from the Serial Monitor

  WiFi.begin(ssid.c_str(), password.c_str()); // Uses the SSID and password entered by the user

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
```

With this setup, you can control the LEDs through an app that you can create using MIT App Inventor. 
To add steps in using Wemos D1 R1 ESP8266 to control relays connected to digital pins D5 and D4, here are some additional actions you can take:

1. **Physical Circuit:**
  - Ensure the relay is correctly connected to digital pins D5 and D4 on Wemos D1 R1.
  - Check the connection between transistor C3198 and the relay to ensure the relay driver functions properly.

2. **Relay Configuration:**
  - Adjust the program code to determine the activation and deactivation conditions of the relay as needed.
  - Ensure that the relay control logic (ON/OFF) is properly implemented in the program code.

3. **MIT App Inventor Application Setup:**
  - Create a user interface in the MIT App Inventor application to control the activation and deactivation of the relay.
  - Add functions to send ON and OFF commands from the application to Wemos D1 R1 via WiFi network.

4. **WiFi Connection:**
  - Ensure that Wemos D1 R1 is connected to the WiFi network with the SSID and password you provided.
  - Regularly check the WiFi connection to ensure that Wemos D1 R1 remains connected to the network.

5. **Serial Monitor Monitoring:**
  - Use the Serial Monitor to monitor debug messages and other important information from Wemos D1 R1 during testing and operation.

By ensuring that your Wemos D1 R1 ESP8266 can be successfully used to control relays connected to digital pins D5 and D4 according to your needs. I hope this explanation helps!.
