#include "map.h"

#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>
#include "player.h"
#include "map_loader.h"


Map::Map(const string & map, const mat4 & projectionMatrix)
    : projectionMatrix(projectionMatrix)
{
    objects = MapLoader::loadMap(map);
}

Map::~Map()
{
    objects.clear();
}

void Map::setCamera()
{
    //cameraPosition = vec3(20.0f * cos(SDL_GetTicks() / 1000.0f) + 10.0f, 20.0f, 20.0f * sin(SDL_GetTicks() / 1000.0f) + 10.0f);
    int x, y;
    SDL_GetMouseState(&x, &y);

    cameraPosition.x = 20.0f * (x / 800.0f - 0.5f) + 5.5f;
    cameraPosition.y = 10.0f - 10.0f * (y / 600.0f);
    cameraPosition.z = 10.0f + 10.0f * (y / 600.0f);

    cameraTarget = vec3(5.5f, 0.0f, 5.5f);
    viewMatrix = glm::lookAt(cameraPosition, cameraTarget, vec3(0.0f, 1.0f, 0.0f));
}

void Map::render()
{
    setCamera();

	//for (auto & it : objects) {
	for (std::vector<Object3D *>::iterator it = objects.begin(); it != objects.end(); ++it) {
        (*it)->render(viewMatrix, projectionMatrix);
    }
}