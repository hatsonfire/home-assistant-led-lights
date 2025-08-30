#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <PubSubClient.h>
#include <stdbool.h> // For the 'bool' type
#include <stdint.h>  // For uint8_t (Arduino 'byte')
#include <WiFi.h>

#include "Settings.h"

// It's best practice to put all configuration in a separate file, like "config.h"
// #include "config.h"

// --- Global State Variables ---
// These are defined in mqtt_handler.c and can be used by other modules if declared 'extern'.
extern bool light_state;
extern int brightness;
extern uint8_t red, green, blue;
extern String current_effect_name;

// --- Function Prototypes ---

/**
 * @brief Initializes Wi-Fi, MQTT client, and LED settings.
 * Replaces the original setup() function.
 */
void mqtt_handler_init();

/**
 * Returns state of the mqtt connection
 */
bool mqtt_handler_connected();

/**
 * @brief Maintains the MQTT connection and processes incoming messages.
 * This should be called repeatedly in your main application loop.
 */
void mqtt_handler_loop();

/**
 * @brief The callback function for processing incoming MQTT messages.
 * This function is platform-specific and must match what your MQTT library expects.
 *
 * @param topic The MQTT topic the message arrived on.
 * @param payload The message data.
 * @param length The length of the message data.
 */
void mqtt_callback(char* topic, uint8_t* payload, unsigned int length);

/**
 * @brief Publishes the current state of the lights to the MQTT broker.
 */
void publish_state();

#endif // MQTT_HANDLER_H