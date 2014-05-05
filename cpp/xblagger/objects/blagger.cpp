#include "blagger.h"

#include <SDL/SDL.h>
#include "levels.h"

Blagger::Blagger(int x, int y, std::vector<SDL_Surface *> sprites) : Object(x, y, sprites)
{
  this->direction = Direction::STOP;
  this->jumpTimer = 0;
}

void
Blagger::update()
{
  int totalFrames = static_cast<int>(this->sprites.size() / 2);
  
  int x = 0;
  int y = 1;
  
  if (this->direction == Direction::LEFT) {
    x--;
    this->frame = (this->frame + 1) % totalFrames + totalFrames;
  } else if (this->direction == Direction::RIGHT) {
    x++;
    this->frame = (this->frame + 1) % totalFrames;
  }
  
  if (this->jumpTimer > 0) {
    y = this->jumpTimer <= 20 ? 1 : -1;
    this->jumpTimer--;
  }
  
  int levelIdx = 0 * Levels::cols * Levels::rows;
  int idx;
  
  idx = (((this->pos->y) / 8) + 1) * Levels::cols + ((this->pos->x + x) / 8 + 1) + levelIdx;
  if (Levels::levels[idx] == 0)
    this->pos->x += x;

  idx = (((this->pos->y + y) / 8 + 1) + 1) * Levels::cols + ((this->pos->x) / 8 + 1) + levelIdx;
  if (Levels::levels[idx] == 0)
    this->pos->y += y;

  //  Object::update();
}

void
Blagger::jump()
{
  if (this->jumpTimer == 0)
    this->jumpTimer = 40;
}