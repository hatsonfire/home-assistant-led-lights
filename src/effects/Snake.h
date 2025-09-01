#ifndef EFFECT_SNAKE_H
#define EFFECT_SNAKE_H

#include "Effect.h"

class SnakeEffect : public Effect {
public:
  SnakeEffect();
  void loop() override;

private:
  struct SnakeHead {
    Edge* edge;
    int led_index;
    int direction;
  };
  SnakeHead pickNewDirection(Node* current_node, Edge* current_edge);
  SnakeHead snake_head;

  unsigned long last_update_time = 0;
  const long ANIMATION_INTERVAL_MS = 30;
  const int FADE_SPEED = 5; // How quickly the tail fades
};

#endif // EFFECT_SNAKE_H
