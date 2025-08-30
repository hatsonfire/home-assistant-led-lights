#include <ArduinoJson.h>
#include "MQTTHandler.h"

long lastReconnectAttempt = 0;

int brightness = BRIGHTNESS;
uint8_t red = 255, green = 255, blue = 255;
bool light_state = false;
String current_effect_name = "Solid";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP());
}

void publishAvailability(const char* light_availability_topic) {
  if (client.connected()) {
    client.publish(light_availability_topic, "online", true); // Retain availability
  }
}

void publishState() {
  if (!client.connected()) {
    Serial.println("Client disconected: Cannot Publish State");
    return;
  }

  char json_payload[200];
  if (light_state) {
    sprintf(json_payload, "{\"state\":\"ON\",\"brightness\":%d,\"color\":{\"r\":%d,\"g\":%d,\"b\":%d},\"effect\":\"%s\"}",
            brightness, red, green, blue, current_effect_name.c_str());
  } else {
    sprintf(json_payload, "{\"state\":\"OFF\"}");
  }
  client.publish(LIGHT_STATE_TOPIC, json_payload, true); // Retain state
  Serial.print("Published state: ");
  Serial.println(json_payload);
}

// MQTT Callback function
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.printf("Message arrived [%s] ", topic);
  char message[length + 1];
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';
  Serial.println(message);

  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, message);

  if (error) {
    Serial.printf("deserializeJson() failed: %s\n", error.f_str());
    return;
  }

  if (doc.containsKey("state")) {
    light_state = (strcmp(doc["state"], "ON") == 0);
  }

  if (doc.containsKey("brightness")) {
    brightness = doc["brightness"].as<int>();
  }

  bool color_set_in_command = false;
  if (doc.containsKey("color")) {
    JsonObject color_obj = doc["color"];
    red = color_obj["r"];
    green = color_obj["g"];
    blue = color_obj["b"];
    color_set_in_command = true;
  }

  if (doc.containsKey("effect")) {
    current_effect_name = doc["effect"].as<String>();
  }
  publishState();
}

void mqtt_handler_init() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  lastReconnectAttempt = 0;
}

bool mqtt_handler_connected() {
  return client.connected();
}

bool reconnect_mqtt() {
  Serial.print("Attempting MQTT connection...");
  // Attempt to connect
  if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD, LIGHT_AVAILABILITY_TOPIC, 0, true, "offline")) {
    Serial.println("connected");
    // Once connected, publish an announcement...
    publishAvailability(LIGHT_AVAILABILITY_TOPIC);
    client.subscribe(LIGHT_COMMAND_TOPIC);
    publishState(); // Publish current state on reconnect
    return true;
  }
  Serial.print("failed, rc=");
  Serial.println(client.state());
  return false;
}

void mqtt_handler_loop() {
  if (!mqtt_handler_connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) { // Reconnect every 5 seconds
      lastReconnectAttempt = now;
      if (reconnect_mqtt()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client is connected, so process incoming messages and maintain the connection.
    client.loop();
  }
}