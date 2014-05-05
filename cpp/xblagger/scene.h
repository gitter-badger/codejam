#ifndef SCENE_H
#define SCENE_H

#include <SDL/SDL_framerate.h>

class DataManager;
class Event;
class CollisionManager;

class Scene
{
public:
  Scene();
  ~Scene();
  void start();

private:
  DataManager * dataManager;
  Event * event;
  CollisionManager * collisionManager;
  FPSmanager fpsManager;
  bool run;
};

#endif
