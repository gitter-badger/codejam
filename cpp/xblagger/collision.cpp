#include "collision.h"

#include <SDL/SDL.h>

bool
CollisionManager::test(SDL_Surface * source, SDL_Surface * target, bool bboxTest)
{
  return false;
}

bool
CollisionManager::pixelTest(SDL_Surface * source, SDL_Surface * target, Uint32 transparent)
{
  return false;
}

bool
CollisionManager::bboxTest(SDL_Surface * source, SDL_Surface * target)
{
  return false;
}
