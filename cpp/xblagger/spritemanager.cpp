#include "spritemanager.h"

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include "xblagger.h"

SpriteManager::SpriteManager()
{
  this->loadSprites();
}

SpriteManager::~SpriteManager()
{
  std::map<Sprites::e, std::vector<SDL_Surface *> >::const_iterator it;
  for (it = sprites.begin(); it != sprites.end(); it++) {
    std::vector<SDL_Surface *> list = it->second;
    while (!list.empty()) {
      SDL_FreeSurface(list.back());
      list.pop_back();
    }
  }
}

void SpriteManager::loadSprites()
{
  SDL_Surface * image = SDL_LoadBMP("sprites.bmp");  
  SDL_Surface * spriteSheet = zoomSurface(image, XBlagger::scale, XBlagger::scale, SMOOTHING_OFF);
  SDL_FreeSurface(image);
  
  this->loadSprite(Sprites::WALL, 0, 71, 8, 8, 1, spriteSheet);
  this->loadSprite(Sprites::KEY, 24, 71, 8, 8, 1, spriteSheet);
  this->loadSprite(Sprites::BUSH, 48, 71, 8, 8, 1, spriteSheet);
  this->loadSprite(Sprites::TRAVELATOR_LEFT, 0, 96, 8, 8, 8, spriteSheet);
  this->loadSprite(Sprites::TRAVELATOR_RIGHT, 0, 104, 8, 8, 8, spriteSheet);
  this->loadSprite(Sprites::CROSS, 56, 71, 8, 8, 1, spriteSheet);
  this->loadSprite(Sprites::SINKING_FLOOR, 128, 87, 8, 8, 8, spriteSheet);
  this->loadSprite(Sprites::BLAGGER, 0, 0, 24, 16, 16, spriteSheet);
  this->loadSprite(Sprites::METAL_FLOOR, 104, 87, 8, 8, 1, spriteSheet);
  this->loadSprite(Sprites::HANDCAR, 96, 21, 24, 16, 2, spriteSheet);
  SDL_FreeSurface(spriteSheet);
}

void SpriteManager::loadSprite(Sprites::e spriteType, int x, int y, int w, int h, int frames, SDL_Surface * spriteSheet)
{
  x *= XBlagger::scale;
  y *= XBlagger::scale;
  w *= XBlagger::scale;
  h *= XBlagger::scale;
  
  for (int i = 0; i < frames; i++) {
    SDL_Surface * sprite = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0, 0, 0, 0);
    SDL_Rect rect = {w * i + x, y, w, h};
    SDL_BlitSurface(spriteSheet, &rect, sprite, NULL);
    SDL_SetColorKey(sprite, SDL_SRCCOLORKEY, 0xff00ff);

    this->sprites[spriteType].push_back(sprite);
  }
}
