#ifndef EFFECT_PULSING_H
#define EFFECT_PULSING_H

#include "Effect.h"

class PulsingEffect : public Effect {
public:
  PulsingEffect();
  void loop() override;

private: 
  CRGB color;
  int pulsing_current_brightness = 0;
  bool pulsing_increasing = true;
  unsigned long last_update_time = 0;
  const long ANIMATION_INTERVAL_MS = 50;
  const float BRIGHTNESS_PER_CYCLE = 6;
  const float BRIGHTNESS_RATIO = 0.5;
};

#endif // EFFECT_PULSING_H