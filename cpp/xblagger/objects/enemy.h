#ifndef ENEMY_H
#define ENEMY_H

#include "object.h"

class Enemy : public Object
{
public:
  Enemy(int x, int y, int from, int to, Direction::e direction, Axis::e axisDirection, std::vector<SDL_Surface *> sprites);
  void update();
  
private:
  Direction::e direction;
  Axis::e axisDirection;
  int from, to;
  int timer, timerLength;
};

#endif