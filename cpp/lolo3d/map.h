#ifndef MAP_H
#define MAP_H

#include <glm/glm.hpp>
#include <vector>
#include <string>

using glm::mat4;
using glm::vec3;
using namespace std;

class Object3D;

class Map
{
public:
    Map(const string & map, const mat4 & projectionMatrix);
    ~Map();
    void render();
    void setCamera();

private:
    mat4 viewMatrix;
    mat4 projectionMatrix;
    vec3 cameraPosition;
    vec3 cameraTarget;
    vector<Object3D *> objects;
};

#endif