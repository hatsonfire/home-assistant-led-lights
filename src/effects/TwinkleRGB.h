#ifndef EFFECT_TWINKLE_RGB_H
#define EFFECT_TWINKLE_RGB_H

#include "Effect.h"

class TwinkleRGBEffect : public Effect {
public:
  TwinkleRGBEffect();
  void loop() override;

private:
  // How many new LEDs to light up each frame
  const int NEW_SPARKLES_PER_FRAME = 1; 
  
  // How quickly the sparkles fade. Higher number = faster fade.
  const int FADE_SPEED = 10; 

  // How often to run the animation loop.
  unsigned long last_update_time = 0;
  const long ANIMATION_INTERVAL_MS = 20;

  // Rotation of colors
  int current_color;
  const int max_colors = 3;
  CRGB colors[3];
};

#endif // EFFECT_TWINKLE_RGB_H