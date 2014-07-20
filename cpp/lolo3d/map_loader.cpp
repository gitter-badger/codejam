#include "map_loader.h"

#include <tinyxml2.h>
#include <sstream>

using namespace tinyxml2;

Level * MapLoader::loadMap(const string & filename)
{
    Level * level = new Level;

    XMLDocument doc;
    XMLError status = doc.LoadFile(filename.c_str());
    if (status) return NULL;
    
    XMLElement * element = doc.FirstChildElement("package")->FirstChildElement("level");
    //string levelName = element->Attribute("name");
    level->width = element->IntAttribute("width");
    level->height = element->IntAttribute("height");

    stringstream ss;
    ss << hex << element->GetText();
    int x = 0;
    int y = 0;
    int value;
    while (ss >> value) {
        //int layer1 = extractBits(value, 2, 4);
        //int layer2 = extractBits(value, 5, 5);
        //int layer3 = extractBits(value, 6, 10);
        //int direction = extractBits(value, 0, 1);

        //if (layer3 == 0x1);

        x++;
        if (x >= level->width) {
            x = 0;
            y++;
        }
    }

    return level;
}

int MapLoader::extractBits(int value, int from, int to)
{
    return (value >> from) & ((1 << ((to + 1) - from)) - 1);
}
