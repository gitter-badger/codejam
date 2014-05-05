#include "scene.h"

#include <SDL/SDL.h>
#include "datamanager.h"
#include "event.h"
#include "collision.h"
#include "objects/blagger.h"

Scene::Scene()
{
  this->dataManager = new DataManager;
  this->dataManager->setLevel(0);
  
  this->event = new Event;
  this->event->run = &this->run;
  this->event->blagger = this->dataManager->blagger;
  
  this->collisionManager = new CollisionManager;

  SDL_initFramerate(&this->fpsManager);
}

Scene::~Scene()
{
  delete this->dataManager;
  delete this->event;
}

void
Scene::start()
{
  this->run = true;

  while (this->run) {
    this->event->processEvents();

    SDL_Surface * screen = SDL_GetVideoSurface();
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

    std::map<std::pair<int, int>, Object *>::const_iterator it;
    for (it = this->dataManager->map.begin(); it != this->dataManager->map.end(); it++) {
      Object * object = it->second;
      object->render();
      object->update();
    }

    SDL_Flip(screen);
    SDL_framerateDelay(&this->fpsManager);
  }
}
