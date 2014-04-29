#include "map_loader.h"

#include <tinyxml2.h>
#include "player.h"

using namespace tinyxml2;

vector<Object3D *> MapLoader::loadMap(const string & filename)
{
    vector<Object3D *> objects;
    
    XMLDocument doc;
    XMLError status = doc.LoadFile(filename.c_str());
    if (status) return objects;
    
    XMLElement * element = doc.FirstChildElement("package")->FirstChildElement("level");
    string levelName = element->Attribute("name");
    //int levelWidth = element->IntAttribute("width");
    //int levelHeight = element->IntAttribute("height");

    element = element->FirstChildElement();
    while (element) {
        string type = element->Attribute("type");
        int x = element->IntAttribute("x");
        int y = element->IntAttribute("y");
        int width = element->IntAttribute("width");
        int height = element->IntAttribute("height");

        if (width == 0) width = 1;
        if (height == 0) height = 1;
        
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (type == "lolo") objects.push_back(new Tux(x + j, y + i));
                if (type == "rock") objects.push_back(new Rock(x + j, y + i));
                if (type == "tree") objects.push_back(new Tree(x + j, y + i));
            }
        }

        element = element->NextSiblingElement();
    }
    
    return objects;
}