#ifndef PULSINGEFFECT_H
#define PULSINGEFFECT_H

#include "Effect.h"

class PulsingEffect : public Effect {
public:
  PulsingEffect();
  void loop() override;

private:
  CRGB color;
  int pulsing_current_brightness = 0;
  bool pulsing_increasing = true;
  const long PULSING_ANIMATION_INTERVAL = 50;
  const float PULSING_BRIGHTNESS_PER_CYCLE = 6;
  const float PULSING_BRIGHTNESS_RATIO = 0.5;
  unsigned long last_update_time = 0;
};

#endif // PULSINGEFFECT_H