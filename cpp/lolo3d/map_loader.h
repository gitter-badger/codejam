#ifndef MAP_LOADER
#define MAP_LOADER

#include <string>
#include "level.h"

using namespace std;

class Object3D;

class MapLoader
{
public:
    static Level * loadMap(const string & filename);

private:
    static int extractBits(int value, int from, int to);
};

#endif
