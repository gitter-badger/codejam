#ifndef MAP_LOADER
#define MAP_LOADER

#include <string>
#include <vector>

using namespace std;

class Object3D;

class MapLoader
{
public:
    static vector<Object3D *> loadMap(const string & filename);
};

#endif