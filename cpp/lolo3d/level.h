#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include <string>
#include "

class Level
{
public:
    Level();

    std::string name;
    std::multimap<int, int> map;
    int width;
    int height;
};

#endif
