#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting MQTT...");
    if (client.connect("ESP32_CLIENT")) {
      Serial.println("connected");
    } else {
      Serial.println("retrying...");
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected");

  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  // Forward motion
  for (int angle = 0; angle <= 180; angle++) {

    client.publish("robotic/servo1", String(angle).c_str());
    client.publish("robotic/servo2", String(angle).c_str());
    client.publish("robotic/servo3", String(angle).c_str());
    client.publish("robotic/servo4", String(angle).c_str());

    Serial.print("Sent angle: ");
    Serial.println(angle);

    delay(40); // smooth motion
  }

  delay(1000);

  // Backward motion
  for (int angle = 180; angle >= 0; angle--) {

    client.publish("robotic/servo1", String(angle).c_str());
    client.publish("robotic/servo2", String(angle).c_str());
    client.publish("robotic/servo3", String(angle).c_str());
    client.publish("robotic/servo4", String(angle).c_str());

    Serial.print("Sent angle: ");
    Serial.println(angle);

    delay(40);
  }

  delay(1000);
}