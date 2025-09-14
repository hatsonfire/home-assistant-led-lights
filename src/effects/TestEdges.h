#ifndef EFFECT_TEST_EDGES_H
#define EFFECT_TEST_EDGES_H

#include "Effect.h"

class TestEffectEdges : public Effect {
public:
  TestEffectEdges();
  void loop() override;

private:
  CRGB color;
  int current_edge;
  int current_led;
  unsigned long last_update_time = 0;
  const long ANIMATION_INTERVAL_MS = 50;
};

#endif // EFFECT_TEST_EDGES_H