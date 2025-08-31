#include "Pulsing.h"

PulsingEffect::PulsingEffect() {}

void PulsingEffect::loop() {
  // Check if enough time has passed since last update.
  unsigned long current_millis = millis();
  if (current_millis - last_update_time < ANIMATION_INTERVAL_MS) {
    return;
  }
  last_update_time = current_millis;

  if (pulsing_increasing) {
    pulsing_current_brightness += BRIGHTNESS_PER_CYCLE;
    if (pulsing_current_brightness > MAX_BRIGHTNESS) {
      pulsing_current_brightness = MAX_BRIGHTNESS;
      pulsing_increasing = false;
    }
  } else {
    pulsing_current_brightness -= BRIGHTNESS_PER_CYCLE;
    if (pulsing_current_brightness < MIN_BRIGHTNESS) {
      pulsing_current_brightness = MIN_BRIGHTNESS;
      pulsing_increasing = true;
    }
  }

  FastLED.setBrightness(int(pulsing_current_brightness * BRIGHTNESS_RATIO));
  color = CRGB(red, green, blue);
  for (int edge = 0; edge < NUM_EDGES; edge++) {
    for (int led = 0; led < NUM_LEDS_PER_EDGE; led++) {
      *edges[edge].leds[led] = color;
    }
  }
  FastLED.show();
}