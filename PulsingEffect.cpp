#include "PulsingEffect.h"

PulsingEffect::PulsingEffect()
    : color(CRGB(red, green, blue)) {}

void PulsingEffect::loop() {
  unsigned long current_millis = millis();
  if (current_millis - last_update_time >= PULSING_ANIMATION_INTERVAL) {
    last_update_time = current_millis;

    if (pulsing_increasing) {
      pulsing_current_brightness += PULSING_BRIGHTNESS_PER_CYCLE;
      if (pulsing_current_brightness > MAX_BRIGHTNESS) {
        pulsing_current_brightness = MAX_BRIGHTNESS;
        pulsing_increasing = false;
      }
    } else {
      pulsing_current_brightness -= PULSING_BRIGHTNESS_PER_CYCLE;
      if (pulsing_current_brightness < MIN_BRIGHTNESS) {
        pulsing_current_brightness = MIN_BRIGHTNESS;
        pulsing_increasing = true;
      }
    }

    FastLED.setBrightness(int(pulsing_current_brightness * PULSING_BRIGHTNESS_RATIO));
    for (int i = 0; i < NUM_LEDS_1; i++) {
      leds_1[i] = color;
    }
    for (int i = 0; i < NUM_LEDS_2; i++) {
      leds_2[i] = color;
    }
    FastLED.show();
  }
}