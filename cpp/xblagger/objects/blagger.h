#ifndef BLAGGER_H
#define BLAGGER_H

#include "object.h"

class Blagger : public Object
{
public:
  Blagger(int x, int y, std::vector<SDL_Surface *> sprites);
  void update();
  void jump();
  
  Direction::e direction;
  int jumpTimer;
};

#endif