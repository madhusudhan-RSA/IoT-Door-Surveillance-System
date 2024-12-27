#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Wi-Fi credentials
const char* ssid = "RSA";
const char* password = "RSA";

// ThingSpeak API details
const char* server = "http://api.thingspeak.com";
const String apiKey = "4RBH8Q80QAI7EXOD";

// Pin configuration
const int irSensorPin = 5; // IR sensor connected to D1 (GPIO 5)
const int buzzerPin = 4;   // Buzzer connected to D2 (GPIO 4)

// Create a WiFiClient instance
WiFiClient client;

void setup() {
  Serial.begin(115200);
  pinMode(irSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output

  WiFi.begin(ssid, password);

  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
}

void loop() {
  // Read IR sensor value (HIGH or LOW)
  int irValue = digitalRead(irSensorPin);
  Serial.print("IR Sensor Value: ");
  Serial.println(irValue);

  // Turn on the buzzer if IR sensor detects something (HIGH)
  if (irValue == HIGH) {
    digitalWrite(buzzerPin, HIGH);  // Turn on the buzzer
  } else {
    digitalWrite(buzzerPin, LOW);   // Turn off the buzzer
  }

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(server) + "/update?api_key=" + apiKey + "&field1=" + String(irValue);
    http.begin(client, url);

    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("Data sent to ThingSpeak");
      Serial.println("Response Code: " + String(httpCode));
    } else {
      Serial.println("HTTP GET failed, error: " + http.errorToString(httpCode));
    }
    http.end();
  } else {
    Serial.println("Wi-Fi disconnected. Reconnecting...");
    WiFi.begin(ssid, password);
  }

  delay(15000); // 15 seconds delay for ThingSpeak rate limit
}
