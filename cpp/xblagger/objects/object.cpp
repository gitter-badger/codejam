#include "object.h"

#include <SDL/SDL.h>
#include "xblagger.h"

Object::Object(int x, int y, std::vector<SDL_Surface *> sprites)
{
  this->pos = new SDL_Rect;
  this->pos->x = x * XBlagger::width;
  this->pos->y = y * XBlagger::height;
  this->offset = new SDL_Rect;

  this->frame = 0;

  this->sprites = sprites;
}

Object::~Object()
{
  delete this->pos;
  delete this->offset;
}

SDL_Surface *
Object::getSurface()
{
  return this->sprites[this->frame];
}

void
Object::render()
{
  SDL_Surface * screen = SDL_GetVideoSurface();
  int x = (this->pos->x + this->offset->x) * XBlagger::scale;
  int y = (this->pos->y + this->offset->y) * XBlagger::scale;
  SDL_Rect pos = {x, y};
  SDL_BlitSurface(this->sprites[this->frame], NULL, screen, &pos);
}

void
Object::update()
{
  this->frame = (this->frame + 1) % static_cast<int>(this->sprites.size());
}
