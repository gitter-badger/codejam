#include "datamanager.h"

#include "levels.h"
#include "objects/text.h"
#include "objects/floor.h"
#include "objects/enemy.h"
#include "objects/blagger.h"
#include "fontmanager.h"
#include "spritemanager.h"

DataManager::DataManager()
{
  this->spriteManager = new SpriteManager();
  this->fontManager = new FontManager();
  this->blagger = NULL;
}

DataManager::~DataManager()
{
  this->flushObjects();
  delete this->spriteManager;
  delete this->fontManager;
}

void
DataManager::flushObjects()
{
  std::map<std::pair<int, int>, Object *>::const_iterator it;
  for (it = this->map.begin(); it != this->map.end(); it++) {
    delete it->second;
  }
  this->blagger = NULL;
}

void
DataManager::setLevel(int level)
{
  this->flushObjects();

  this->setTiles(level);
  this->setSprites(level);
  this->setBlagger(level);
  this->setLabels(level);
}

void
DataManager::setTiles(int level)
{
  int levelIdx = level * Levels::cols * Levels::rows;
  for (int i = 0; i < Levels::rows; i++) {
    for (int j = 0; j < Levels::cols; j++) {
      int idx = i * Levels::cols + j + levelIdx;
      int x = j;
      int y = i;
      Sprites::e type = (Sprites::e) Levels::levels[idx];
      switch (type) {
        case Sprites::WALL:
        case Sprites::KEY:
        case Sprites::BUSH:
        case Sprites::TRAVELATOR_LEFT:
        case Sprites::TRAVELATOR_RIGHT:
        case Sprites::CROSS:
        case Sprites::METAL_FLOOR:
          this->map.insert(std::make_pair(std::make_pair(x, y), new Object(x, y, this->spriteManager->sprites[type])));
          break;
          
        case Sprites::SINKING_FLOOR:
          this->map.insert(std::make_pair(std::make_pair(x, y), new Floor(x, y, this->spriteManager->sprites[type], Floor::SINKING)));
          break;
          
        default:
          break;
      }
    }
  }
}

void
DataManager::setSprites(int level)
{
  int spriteIdx = 0;
  for (int i = 0; i < level; i++) {
    spriteIdx += Levels::numSprites[i];
  }
  spriteIdx *= 6;
  for (int i = 0; i < Levels::numSprites[level]; i++) {
    int idx = i * 6 + spriteIdx;
    Sprites::e type = (Sprites::e) Levels::sprites[idx];
    int x = Levels::sprites[idx + 1];
    int y = Levels::sprites[idx + 2];
    int from = Levels::sprites[idx + 3];
    int to = Levels::sprites[idx + 4];
    Direction::e direction = (Direction::e) Levels::sprites[idx + 5];
    Axis::e axisDirection = direction == Direction::LEFT || direction == Direction::RIGHT ? Axis::HORIZONTAL : Axis::VERTICAL;
    
    switch (type) {
      case Sprites::HANDCAR:
        this->map.insert(std::make_pair(std::make_pair(x, y), new Enemy(x, y - 2, from, to, direction, axisDirection, this->spriteManager->sprites[type])));
        break;
        
      default:
        break;
    }
  }
}

void
DataManager::setBlagger(int level)
{
  int idx = level * 2;
  int x = Levels::start[idx];
  int y = Levels::start[idx + 1] - 2;

  this->blagger = new Blagger(x, y, this->spriteManager->sprites[Sprites::BLAGGER]);
  this->map.insert(std::make_pair(std::make_pair(x, y), this->blagger));
}

void
DataManager::setLabels(int level)
{    
  /*int levelNamePosition = (31 - sizeof(Levels::levelNames[level])) / 2;
  this->objects[Layer::TEXT].push_back(new Text(levelNamePosition, 19, Levels::levelNames[level], Fonts::SMALL, this->fontManager));

  char level_cstr[4];
  sprintf(level_cstr, "%03d", 4);
  level_cstr[3] = NULL;
  this->objects[Layer::TEXT].push_back(new Text(32, 12, "level", Fonts::SMALL, this->fontManager));
  this->objects[Layer::TEXT].push_back(new Text(32, 13, level_cstr, Fonts::LARGE, this->fontManager));

  char lives_cstr[3];
  sprintf(lives_cstr, "%02d", 3);
  lives_cstr[2] = NULL;
  this->objects[Layer::TEXT].push_back(new Text(32, 15, "men", Fonts::SMALL, this->fontManager));
  this->objects[Layer::TEXT].push_back(new Text(32, 16, lives_cstr, Fonts::LARGE, this->fontManager));

  char score_cstr[7];
  sprintf(score_cstr, "%06d", 600);
  score_cstr[6] = NULL;
  this->objects[Layer::TEXT].push_back(new Text(0, 22, "score", Fonts::SMALL, this->fontManager));
  this->objects[Layer::TEXT].push_back(new Text(6, 22, score_cstr, Fonts::LARGE, this->fontManager));

  char hiscore_cstr[7];
  sprintf(hiscore_cstr, "%06d", 6581);
  hiscore_cstr[6] = NULL;
  this->objects[Layer::TEXT].push_back(new Text(20, 22, "hiscore", Fonts::SMALL, this->fontManager));
  this->objects[Layer::TEXT].push_back(new Text(28, 22, hiscore_cstr, Fonts::LARGE, this->fontManager));*/
}
