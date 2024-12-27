# ESP8266 IR Sensor and ThingSpeak Integration

This project demonstrates how to use an ESP8266 microcontroller to interface with an IR sensor and a buzzer while sending sensor data to the ThingSpeak platform.

## Features
- Connects the ESP8266 to a Wi-Fi network.
- Reads the state of an IR sensor to detect obstacles.
- Activates a buzzer when an obstacle is detected.
- Sends IR sensor data to the ThingSpeak platform at regular intervals.

## Components Used
1. **ESP8266 Microcontroller**
2. **IR Sensor** (Connected to GPIO5 / D1)
3. **Buzzer** (Connected to GPIO4 / D2)
4. **Wi-Fi Network**
5. ThingSpeak API Key for data logging

## Circuit Diagram

- **IR Sensor**
  - VCC -> 3.3V (ESP8266)
  - GND -> GND (ESP8266)
  - Signal -> D1 (GPIO5)

- **Buzzer**
  - Positive Terminal -> D2 (GPIO4)
  - Negative Terminal -> GND

## Prerequisites
- Arduino IDE with the ESP8266 board package installed.
- ThingSpeak account and channel set up.

## Usage

1. **Setup Wi-Fi Credentials:**
   - Update the `ssid` and `password` variables in the code with your Wi-Fi network details.

2. **ThingSpeak API Key:**
   - Replace `apiKey` with your ThingSpeak channel's API write key.

3. **Upload Code:**
   - Upload the code to your ESP8266 using the Arduino IDE.

4. **Monitor Data:**
   - Open the Serial Monitor (baud rate: 115200) to view the sensor's status and ThingSpeak response codes.
   - Check the ThingSpeak channel to view the logged sensor data.

## Code Explanation

### Wi-Fi Connection
```cpp
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}
Serial.println("\nConnected to Wi-Fi");
```
Establishes a connection to the specified Wi-Fi network.

### IR Sensor and Buzzer Logic
```cpp
int irValue = digitalRead(irSensorPin);
if (irValue == HIGH) {
  digitalWrite(buzzerPin, HIGH); // Activate buzzer
} else {
  digitalWrite(buzzerPin, LOW);  // Deactivate buzzer
}
```
Reads the IR sensor state and activates the buzzer when an obstacle is detected.

### ThingSpeak Integration
```cpp
String url = String(server) + "/update?api_key=" + apiKey + "&field1=" + String(irValue);
HTTPClient http;
http.begin(client, url);
int httpCode = http.GET();
if (httpCode > 0) {
  Serial.println("Data sent to ThingSpeak");
} else {
  Serial.println("HTTP GET failed");
}
http.end();
```
Sends the IR sensor value to the ThingSpeak channel using HTTP GET requests.

## Notes
- Ensure that your ThingSpeak channel is set up to receive data on `field1`.
- Comply with the ThingSpeak rate limit (1 update every 15 seconds).

## Dependencies
- **ESP8266WiFi.h**
- **ESP8266HTTPClient.h**
