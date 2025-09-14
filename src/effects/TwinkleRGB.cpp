#include "TwinkleRGB.h"

TwinkleRGBEffect::TwinkleRGBEffect() {
  // Clear all LEDs when the effect starts
  FastLED.clear();
  FastLED.show();
  current_color = 0;
  colors[0] = CRGB(255,0,0);
  colors[1] = CRGB(0,255,0);
  colors[2] = CRGB(0,0,255);
}

void TwinkleRGBEffect::loop() {
  // Check if enough time has passed since last update.
  unsigned long current_millis = millis();
  if (current_millis - last_update_time < ANIMATION_INTERVAL_MS) {
    return;
  }
  last_update_time = current_millis;

  // 1. Fade all existing LEDs down slightly
  // This is what makes them look like they are fading out
  for (int edge = 0; edge < NUM_EDGES; edge++) {
    for (int led = 0; led < NUM_LEDS_PER_EDGE; led++) {
      edges[edge].leds[led]->fadeToBlackBy(FADE_SPEED);
    }
  }

  // 2. Light up a few new random LEDs at full brightness
  for (int i = 0; i < NEW_SPARKLES_PER_FRAME; i++) {
    // Pick a random edge
    int random_edge = random8(NUM_EDGES);
    // Pick a random LED on that edge
    int random_led = random8(NUM_LEDS_PER_EDGE);

    // Set it to the current color from MQTT
    *edges[random_edge].leds[random_led] = colors[current_color];
    current_color = (current_color + 1) % max_colors;
  }

  // Set brightness and push the data to the LED strip
  FastLED.setBrightness(brightness);
  FastLED.show();
}