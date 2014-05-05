#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <map>
#include <vector>
#include "types.h"

class Object;
class FontManager;
class SpriteManager;
class Blagger;

class DataManager
{
public:
  DataManager();
  ~DataManager();
  void setLevel(int level);

  std::map<std::pair<int, int>, Object *> map;
  Blagger * blagger;

private:
  void flushObjects();
  void setTiles(int level);
  void setSprites(int level);
  void setBlagger(int level);
  void setLabels(int level);

  FontManager * fontManager;
  SpriteManager * spriteManager;
};

#endif
