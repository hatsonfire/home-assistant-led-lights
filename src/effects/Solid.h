#ifndef SOLID_H
#define SOLID_H

#include "Effect.h"

class SolidEffect : public Effect {
public:
  SolidEffect();
  void loop() override;

private:
  CRGB color;
  const float SOLID_BRIGHTNESS_RATIO = 0.5;
};

#endif // SOLID_H