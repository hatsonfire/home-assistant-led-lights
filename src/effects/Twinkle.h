#ifndef EFFECT_TWINKLE_H
#define EFFECT_TWINKLE_H

#include "Effect.h"

class TwinkleEffect : public Effect {
public:
  TwinkleEffect();
  void loop() override;

private:
  // How many new LEDs to light up each frame
  const int NEW_SPARKLES_PER_FRAME = 1; 
  
  // How quickly the sparkles fade. Higher number = faster fade.
  const int FADE_SPEED = 10; 

  // How often to run the animation loop.
  unsigned long last_update_time = 0;
  const long ANIMATION_INTERVAL_MS = 20;
};

#endif // EFFECT_TWINKLE_H
