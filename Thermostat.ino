#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <Adafruit_BMP085_U.h>  // Unified library for BMP180
#include <Adafruit_Sensor.h>     // Unified sensor library

// BMP180 sensor object
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified();

// Pin definitions
#define ledOn D2
#define ledSafety D3
#define button D1

// WiFi credentials
const char* ssid = "Laboratorium-IoT";
const char* password = "IoTL@bolatorium";

// Change the port to 8080 for testing
ESP8266WebServer server(80);  // Change port from 80 to 8080

// Global variables
float currentTempBMP180 = 0.0;
float pressureBMP180 = 0.0;
float onThreshold = 25.0;  // Default threshold
float safetyThreshold = 35.0;  // Default safety threshold
bool thermostatOn = false;
bool inSafetyMode = false;

// Potentiometer value (range: 0 - 1023)
int potValue = 0;
float potVoltage = 0.0;

// Variables to keep track of previous states
bool previousThermostatOn = false;
bool previousInSafetyMode = false;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting setup...");

  // Initialize WiFi connection
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  // Wait until connected to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // WiFi connected successfully
  Serial.println("Connected to WiFi");
  Serial.print("ESP8266 IP address: ");
  Serial.println(WiFi.localIP());  // Print IP address to Serial Monitor

  // Configure pins
  pinMode(ledOn, OUTPUT);
  pinMode(ledSafety, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  digitalWrite(ledOn, LOW);
  digitalWrite(ledSafety, LOW);

  // Initialize BMP180 sensor
  Wire.begin(D6, D5);  // Set SDA to D6 (GPIO 12) and SCL to D5 (GPIO 14)
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
  } else {
    Serial.println("BMP180 sensor found and initialized");
  }

  // Set up the web server routes (handlers)
  server.on("/", handleRoot);      // Root URL
  server.on("/set", handleSet);    // /set URL for adjusting thresholds
  server.on("/status", handleStatus);  // /status URL for checking status in JSON

  // Start the web server
  server.begin();  // Don't forget this!
  Serial.println("HTTP server started on port 80");
}

void loop() {
  // Handle client requests
  server.handleClient();

  // Read BMP180 sensor data
  sensors_event_t event;
  bmp.getEvent(&event);
  if (event.pressure) {
    pressureBMP180 = event.pressure / 100.0;  // Convert to hPa
  }

  float temp;
  bmp.getTemperature(&temp);  // Read temperature from sensor
  currentTempBMP180 = temp;  // Assign temperature value

  // Read potentiometer value (0 - 1023)
  potValue = analogRead(A0);
  potVoltage = (potValue * 3.3) / 1024.0;  // Convert analog reading to voltage (0 - 3.3V)

  // Check thermostat state
  checkThermostatState();
}

// Function to check thermostat state and control LEDs
void checkThermostatState() {
  if (digitalRead(button) == LOW) {  // Emergency button pressed
    thermostatOn = false;
    digitalWrite(ledOn, LOW);
    digitalWrite(ledSafety, HIGH);
    inSafetyMode = true;
   
    // Only print if entering safety mode
    if (!previousInSafetyMode) {
      Serial.println("Emergency button pressed, entering safety mode");
      previousInSafetyMode = true;
    }
    return;
  }

  if (currentTempBMP180 > safetyThreshold) {  // Safety mode
    thermostatOn = false;
    digitalWrite(ledOn, LOW);
    digitalWrite(ledSafety, HIGH);
    inSafetyMode = true;

    // Only print if entering safety mode
    if (!previousInSafetyMode) {
      Serial.println("Temperature exceeds safety threshold, safety mode activated");
      previousInSafetyMode = true;
    }
  } else if (currentTempBMP180 > onThreshold && !inSafetyMode) {  // Normal mode
    thermostatOn = true;
    digitalWrite(ledOn, HIGH);
    digitalWrite(ledSafety, LOW);

    // Only print if thermostat state changed to ON
    if (!previousThermostatOn) {
      Serial.println("Temperature exceeds on threshold, thermostat ON");
      previousThermostatOn = true;
      previousInSafetyMode = false;  // Reset safety mode tracking
    }
  } else {
    thermostatOn = false;
    digitalWrite(ledOn, LOW);
    digitalWrite(ledSafety, LOW);

    // Only print if thermostat state changed to OFF
    if (previousThermostatOn) {
      Serial.println("Temperature below threshold, thermostat OFF");
      previousThermostatOn = false;
      previousInSafetyMode = false;  // Reset safety mode tracking
    }
  }
}

// Web server handler for the root page
void handleRoot() {
  Serial.println("Serving root page");
  if (!server.authenticate("admin", "password")) {
    return server.requestAuthentication();
  }

  String html = "<h1>Thermostat Control</h1>";
  html += "<meta http-equiv='refresh' content='10'>";  // Auto-refresh every 5 seconds
  html += "<p>Current Temperature (BMP180): " + String(currentTempBMP180) + " °C</p>";
  html += "<p>Current Pressure (BMP180): " + String(pressureBMP180) + " hPa</p>";
  html += "<p>Potentiometer Value: " + String(potValue) + " (Voltage: " + String(potVoltage) + "V)</p>";
  html += "<p>On Threshold: " + String(onThreshold) + " °C</p>";
  html += "<p>Safety Threshold: " + String(safetyThreshold) + " °C</p>";
  html += "<form action='/set' method='GET'>";
  html += "Set On Threshold: <input type='number' name='on' step='0.1'><br>";
  html += "Set Safety Threshold: <input type='number' name='safety' step='0.1'><br>";
  html += "<input type='submit' value='Set'>";
  html += "</form>";
  server.send(200, "text/html", html);
}

// Web server handler for updating thresholds
void handleSet() {
  Serial.println("Handling /set request");
  if (!server.authenticate("admin", "password")) {
    return server.requestAuthentication();
  }

  if (server.hasArg("on")) {
    onThreshold = server.arg("on").toFloat();
    Serial.println("Updated onThreshold: " + String(onThreshold) + " °C");
  }
  if (server.hasArg("safety")) {
    safetyThreshold = server.arg("safety").toFloat();
    Serial.println("Updated safetyThreshold: " + String(safetyThreshold) + " °C");
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

// Web server handler for returning status in JSON format
void handleStatus() {
  Serial.println("Handling /status request");
  String status = "{\"temperature_BMP180\": " + String(currentTempBMP180) + ", ";
  status += "\"pressure_BMP180\": " + String(pressureBMP180) + ", ";
  status += "\"potValue\": " + String(potValue) + ", ";
  status += "\"potVoltage\": " + String(potVoltage) + ", ";
  status += "\"on\": " + String(thermostatOn) + ", ";
  status += "\"safety\": " + String(inSafetyMode) + "}";
  server.send(200, "application/json", status);
}
