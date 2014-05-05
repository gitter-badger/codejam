#ifndef COLLISION_H
#define COLLISION_H

struct SDL_Surface;
typedef unsigned int Uint32;

class CollisionManager
{
public:
  static bool test(SDL_Surface * source, SDL_Surface * target, bool bboxTest);
  
private:
  static bool pixelTest(SDL_Surface * source, SDL_Surface * target, Uint32 transparent = 0xff00ff);
  static bool bboxTest(SDL_Surface * source, SDL_Surface * target);
};

#endif
