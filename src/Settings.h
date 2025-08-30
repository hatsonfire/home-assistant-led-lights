#ifndef SETTINGS_H
#define SETTINGS_H

#include <FastLED.h>
#include "ArduinoSecrets.h"

// LED
#define BRIGHTNESS 20 // Default brightness (0-255)
#define MIN_BRIGHTNESS 0 // Default brightness (0-255)
#define MAX_BRIGHTNESS 255 // Default brightness (0-255)
#define DATA_PIN_1 2 // GPIO pin connected to the LED strip's 1st data line
#define DATA_PIN_2 5 // GPIO pin connected to the LED strip's 2nd data line
#define NUM_LEDS_1 238 // Number of LEDs Attached to DATA_PIN_1 in your strip
#define NUM_LEDS_2 322 // Number of LEDs Attached to DATA_PIN_2 in your strip
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_NODES 25
#define NUM_EDGES 40
#define NUM_LEDS_PER_EDGE 14

// MQTT Definitions
#define MQTT_SERVER "192.168.86.31"
#define MQTT_PORT 1883
#define MQTT_USER "mqtt_broker_user"
#define MQTT_CLIENT_ID "esp32_leds"
#define LIGHT_AVAILABILITY_TOPIC "homeassistant/light/esp32_leds/availability"
#define LIGHT_COMMAND_TOPIC "homeassistant/light/esp32_leds/set"
#define LIGHT_STATE_TOPIC "homeassistant/light/esp32_leds/state"

// LED Data Struct
struct Edge;
struct Node {
  Edge *n, *ne, *se, *s, *sw, *nw;  
};
struct Edge {
  Node *low_node, *high_node;
  CRGB *leds[NUM_LEDS_PER_EDGE];
};

extern Node nodes[NUM_NODES];
extern Edge edges[NUM_EDGES];

#endif // SETTINGS_H