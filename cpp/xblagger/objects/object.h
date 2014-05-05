#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include "../types.h"

struct SDL_Surface;
struct SDL_Rect;

class Object
{
public:
  Object(int x, int y, std::vector<SDL_Surface *> sprites = std::vector<SDL_Surface *>());
  virtual ~Object();
  virtual void render();
  virtual void update();
  SDL_Surface * getSurface();
  SDL_Rect * pos;
  //bool lethal;

protected:
  std::vector<SDL_Surface *> sprites;
  SDL_Rect * offset;
  int frame;
};

#endif
