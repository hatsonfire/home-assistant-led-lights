#ifndef EFFECT_H
#define EFFECT_H

#include <FastLED.h>
#include "Settings.h"

extern bool light_state;
extern int brightness;
extern uint8_t red, green, blue;
extern String current_effect_name;

class Effect {
public:
  // Pure virtual function that must be implemented by each effect.
  // This is where the magic happens for each animation.
  virtual void loop() = 0;

  // Virtual destructor to ensure proper cleanup of derived classes.
  virtual ~Effect() {}
};

#endif // EFFECT_H