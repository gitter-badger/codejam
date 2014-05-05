#ifndef SPRITEMANAGER_H
#define SPRITEMANAGER_H

#include <map>
#include <vector>
#include "types.h"

struct SDL_Surface;

class SpriteManager
{
public:
  SpriteManager();
  ~SpriteManager();
  void loadSprites();

  std::map<Sprites::e, std::vector<SDL_Surface *> > sprites;

private:
  void loadSprite(Sprites::e spriteType, int x, int y, int w, int h, int frames, SDL_Surface * spriteSheet);
};

#endif
