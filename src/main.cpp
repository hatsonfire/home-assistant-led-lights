#include <ArduinoJson.h>

#include "effects/Effect.h"
#include "effects/PulsingEffect.h"
#include "effects/SolidEffect.h"
#include "LedStructure.h"
#include "MqttHandler.h"
#include "Settings.h"
// Include other effect headers here

// LED Definitions
LedStructure ledStructure;

// Effect names
const char* EFFECT_SOLID = "Solid";
const char* EFFECT_PULSING = "Pulsing";
const char* EFFECT_TEST = "Test";

// Global Variables
Effect* currentEffect = nullptr;
String applied_effect_name = "";

// MQTT Global Variables
extern bool light_state;
extern String current_effect_name;

void set_effect(const String& effect_name) {
  // Delete the old effect to free up memory
  if (currentEffect != nullptr) {
    delete currentEffect;
    currentEffect = nullptr;
  }

  // Create a new effect based on the effect_name
  if (effect_name == EFFECT_SOLID) {
    currentEffect = new SolidEffect();
  } else if (effect_name == EFFECT_PULSING) {
    currentEffect = new PulsingEffect();
  }

  current_effect_name = effect_name;
}

void setup() {
  ledStructure.initialize();
  mqtt_handler_init();

  // FastLED setup
  FastLED.addLeds<LED_TYPE, DATA_PIN_1, COLOR_ORDER>(leds_1, NUM_LEDS_1);
  FastLED.addLeds<LED_TYPE, DATA_PIN_2, COLOR_ORDER>(leds_2, NUM_LEDS_2);

  // Initialize the first effect
  set_effect(EFFECT_SOLID);
}

void loop() {
  mqtt_handler_loop(); // Process MQTT messages, which might update global state vars

  // Check if the desired effect from MQTT has changed. We do this check only when the
  // light is supposed to be ON.
  if (current_effect_name != applied_effect_name) {
    set_effect(current_effect_name);
    applied_effect_name = current_effect_name;
  }

  if (light_state && currentEffect != nullptr) {
    // Trigger the next loop of the current effect
    currentEffect->loop();
  } else {
    // If the light is off, clear the LEDs.
    FastLED.clear();
    FastLED.show();

    // By clear the applied_effect_name so we force the effect to be recreated when
    // LEDs are turned back on.
    if (applied_effect_name != "") {
      applied_effect_name = "";
    }
  }
}