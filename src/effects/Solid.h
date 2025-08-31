#ifndef EFFECT_SOLID_H
#define EFFECT_SOLID_H

#include "Effect.h"

class SolidEffect : public Effect {
public:
  SolidEffect();
  void loop() override;

private:
  CRGB color;
  const float SOLID_BRIGHTNESS_RATIO = 0.5;
};

#endif // EFFECT_SOLID_H