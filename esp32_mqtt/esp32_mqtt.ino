/*
  ================================================================
  |                        ESP32 MQTT Client                     |
  |---------------------------------------------------------------|
  | This code is designed to connect an ESP32 to an MQTT broker   |
  | using WiFi. The device publishes and subscribes to a topic,   |
  | allowing for two-way communication between the ESP32 and      |
  | other devices or systems connected to the broker.             |
  ================================================================
  
  Board and Library Versions:
  - ESP32 by Espressif Systems         -> 3.0.3
  - ArduinoJson by Benoit Blanchon     -> 7.1.0

  Key Features:
  - Connects to a WiFi network using SSID and Password.
  - Establishes a connection to an MQTT broker.
  - Publishes an introductory message upon successful connection.
  - Subscribes to a topic and listens for incoming messages.
  - Displays received messages via Serial Monitor.

  Note:
  - Customize the SSID, PASSWORD, MQTT_BROKER, TOPIC, 
    MQTT_USERNAME, and MQTT_PASSWORD according to your setup.
  - Ensure the correct library versions are installed for compatibility.
*/

#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

// WiFi
const char *SSID = "xxxxx";
const char *PASSWORD = "xxxxx";

// MQTT Broker
const char *MQTT_BROKER = "xxxxx";
const char *TOPIC = "xxxxx";
const char *MQTT_USERNAME = "xxxxx";
const char *MQTT_PASSWORD = "xxxxx";
const int MQTT_PORT = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the Wi-Fi network");
  client.setServer(MQTT_BROKER, MQTT_PORT);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("MQTT broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  client.publish(TOPIC, "Hi, I'm ESP32 ^^");
  client.subscribe(TOPIC);
}

void mqtt_reconnect() {
  while (!client.connected()) {
    String client_id = "jcores-iot-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD)) {
      Serial.println("MQTT broker connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");

  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, payload);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  String state = doc["state"].as<String>();
}

void loop() {
  if (!client.connected()) {
    mqtt_reconnect();
  }
  client.loop();
  client.publish(IOT_TOPIC, String(millis()/1000).c_str());
}
}
