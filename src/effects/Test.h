#ifndef EFFECT_TEST_H
#define EFFECT_TEST_H

#include "Effect.h"

class TestEffect : public Effect {
public:
  TestEffect();
  void loop() override;

private:
  CRGB color;
  int current_edge;
  int current_led;
  unsigned long last_update_time = 0;
  const long ANIMATION_INTERVAL_MS = 50;
};

#endif // EFFECT_TEST_H