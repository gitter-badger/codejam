#ifndef FLOOR_H
#define FLOOR_H

#include "object.h"

class Floor : public Object
{
public:
  enum Type {NONE, LEFT, RIGHT, SINKING};
  Floor(int x, int y, std::vector<SDL_Surface *> sprites, Type t);
  void update() {
    if (false)
      Object::update();
  }
};

#endif