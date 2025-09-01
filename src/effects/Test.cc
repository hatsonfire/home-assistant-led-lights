#include "Test.h"

TestEffect::TestEffect() {
    current_edge = NUM_EDGES - 1;
    current_led = NUM_LEDS_PER_EDGE - 1;
    // Clear all LEDs when the effect starts
    FastLED.clear();
    FastLED.show();
}

void TestEffect::loop() {
  // Check if enough time has passed since last update.
  unsigned long current_millis = millis();
  if (current_millis - last_update_time < ANIMATION_INTERVAL_MS) {
    return;
  }
  last_update_time = current_millis;

  // Turn off current LED
  *edges[current_edge].leds[current_led] = CRGB::Black;

  // Increment LED
  current_led++;
  if (current_led >= NUM_LEDS_PER_EDGE) {
    current_led = 0;
    current_edge++;
    if (current_edge >= NUM_EDGES) {
      current_edge = 0;
    }
  }

  // Turn on new LED
  *edges[current_edge].leds[current_led] = CRGB(red, green, blue);

  FastLED.setBrightness(brightness);
  FastLED.show();
}