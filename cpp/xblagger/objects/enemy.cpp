#include "enemy.h"

#include <SDL/SDL.h>
#include "xblagger.h"

Enemy::Enemy(int x, int y, int from, int to, Direction::e direction, Axis::e axisDirection, std::vector<SDL_Surface *> sprites) : Object(x, y, sprites), from(from), to(to), direction(direction), axisDirection(axisDirection)
{
  this->timer = 0;
  this->timerLength = 10;
}

void
Enemy::update()
{
  if (this->axisDirection == Axis::HORIZONTAL) {
    if (this->pos->x < this->from * XBlagger::width)
      this->direction = Direction::RIGHT;
    if (this->pos->x > this->to * XBlagger::width)
      this->direction = Direction::LEFT;
    
    this->pos->x += direction == Direction::LEFT ? -1 : 1;
  } else {
    if (this->pos->y < this->from * XBlagger::height)
      this->direction = Direction::DOWN;
    if (this->pos->y > this->to * XBlagger::height)
      this->direction = Direction::UP;
    
    this->pos->y += direction == Direction::UP ? -1 : 1;
  }
  
  if (timer == 0)
    Object::update();
  this->timer = (this->timer + 1) % this->timerLength;
}