#include "SolidEffect.h"

SolidEffect::SolidEffect() {}

void SolidEffect::loop() {
  color = CRGB(red, green, blue);
  for (int i = 0; i < NUM_LEDS_1; i++) {
    leds_1[i] = color;
  }
  for (int i = 0; i < NUM_LEDS_2; i++) {
    leds_2[i] = color;
  }
  FastLED.setBrightness(int_fast8_t(brightness * SOLID_BRIGHTNESS_RATIO));
  FastLED.show();
}