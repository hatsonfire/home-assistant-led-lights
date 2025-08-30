#include "SolidEffect.h"

SolidEffect::SolidEffect() {}

void SolidEffect::loop() {
  color = CRGB(red, green, blue);
  for (int edge = 0; edge < NUM_EDGES; edge++) {
    for (int led = 0; led < NUM_LEDS_PER_EDGE; led++) {
      *edges[edge].leds[led] = color;
    }
  }
  FastLED.setBrightness(int_fast8_t(brightness * SOLID_BRIGHTNESS_RATIO));
  FastLED.show();
}