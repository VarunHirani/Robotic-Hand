#include <WiFi.h>
#include <PubSubClient.h>
#include <ESP32Servo.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

// 4 servos
Servo servos[4];
int pins[4] = {13, 14, 26,33};

// Topics
const char* topics[4] = {
  "robotic/servo1",
  "robotic/servo2",
  "robotic/servo3",
  "robotic/servo4"
};

void callback(char* topic, byte* payload, unsigned int length) {
  String msg = "";

  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }

  int angle = constrain(msg.toInt(), 0, 180);

  // Find which servo to control
  for (int i = 0; i < 4; i++) {
    if (String(topic) == topics[i]) {
      Serial.print("Servo ");
      Serial.print(i + 1);
      Serial.print(" → ");
      Serial.println(angle);

      servos[i].write(angle);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting MQTT...");
    if (client.connect("ESP32_4SERVO")) {
      Serial.println("connected");

      // Subscribe to all servo topics
      for (int i = 0; i < 4; i++) {
        client.subscribe(topics[i]);
      }

    } else {
      Serial.println("retrying...");
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Attach servos
  for (int i = 0; i < 4; i++) {
    servos[i].setPeriodHertz(50);
    servos[i].attach(pins[i], 500, 2400);
    servos[i].write(0);
  }

  // WiFi connect
  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();
}