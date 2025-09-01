#include "Snake.h"
#include <vector>

SnakeEffect::SnakeEffect() {
  // Clear all LEDs when the effect starts
  FastLED.clear();
  FastLED.show();

  snake_head = {
    .edge = &edges[0],
    .led_index = 0,
    .direction = 1
  };
}

SnakeEffect::SnakeHead SnakeEffect::pickNewDirection(Node* current_node, Edge* current_edge) {
  std::vector<SnakeHead> possible_heads;

  // Gather all valid, non-null edges connected to the current node
  if (current_node->nw && current_edge != current_node->nw) {
    possible_heads.push_back(SnakeHead{.edge = current_node->nw, .led_index = 0, .direction = 1});
  }
  if (current_node->n && current_edge != current_node->n) {
    possible_heads.push_back(SnakeHead{.edge = current_node->n, .led_index = 0, .direction = 1});
  }
  if (current_node->ne && current_edge != current_node->ne) {
    possible_heads.push_back(SnakeHead{.edge = current_node->ne, .led_index = 0, .direction = 1});
  }
  if (current_node->se && current_edge != current_node->se) {
    possible_heads.push_back(SnakeHead{.edge = current_node->se, .led_index = NUM_LEDS_PER_EDGE - 1, .direction = -1});
  }
  if (current_node->s && current_edge != current_node->s) {
    possible_heads.push_back(SnakeHead{.edge = current_node->s, .led_index = NUM_LEDS_PER_EDGE - 1, .direction = -1});
  }
  if (current_node->sw && current_edge != current_node->sw) {
    possible_heads.push_back(SnakeHead{.edge = current_node->sw, .led_index = NUM_LEDS_PER_EDGE - 1, .direction = -1});
  }

  if (possible_heads.empty()) {
    // Failsafe in case a node has no connections, just restart
    return SnakeHead{
      .edge = &edges[0],
      .led_index = 0,
      .direction = 1
    };
  }

  // Pick a random next_head location
  return possible_heads[random8(possible_heads.size())];
}

void SnakeEffect::loop() {
  // Check if enough time has passed since the last update.
  unsigned long current_millis = millis();
  if (current_millis - last_update_time < ANIMATION_INTERVAL_MS) {
    return;
  }
  last_update_time = current_millis;

  // 1. Fade all existing LEDs down to create the tail effect
  for (int edge = 0; edge < NUM_EDGES; edge++) {
    for (int led = 0; led < NUM_LEDS_PER_EDGE; led++) {
      edges[edge].leds[led]->fadeToBlackBy(FADE_SPEED);
    }
  }
  
  // 2. Set the new head pixel to the current color
  *(snake_head.edge->leds[snake_head.led_index]) = CRGB(red, green, blue);

  // 3. Move the head for the next frame
  snake_head.led_index += snake_head.direction;

  // 4. Check if new edge needs to be chosen
  if (snake_head.led_index < 0) {
    snake_head = pickNewDirection(snake_head.edge->low_node, snake_head.edge);
  }
  if (snake_head.led_index >= NUM_LEDS_PER_EDGE) {
    snake_head = pickNewDirection(snake_head.edge->high_node, snake_head.edge);
  }

  // 4. Set brightness and show the updated frame
  FastLED.setBrightness(brightness);
  FastLED.show();
}