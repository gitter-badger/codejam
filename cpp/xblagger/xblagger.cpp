#include "xblagger.h"

#include <SDL/SDL.h>

#include "scene.h"

int XBlagger::width;
int XBlagger::height;
int XBlagger::scale;

XBlagger::XBlagger(int scale)
{
  int w = 320 * scale;
  int h = 200 * scale;
  
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_SetVideoMode(w, h, 32, SDL_HWSURFACE);
  
  XBlagger::width = 8;
  XBlagger::height = 8;
  XBlagger::scale = scale;

  this->scene = new Scene;
  this->scene->start();
}

XBlagger::~XBlagger()
{
  delete this->scene;
  SDL_Quit();
}
