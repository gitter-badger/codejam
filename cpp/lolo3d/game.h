#ifndef GAME_H
#define GAME_H

#include <glm/glm.hpp>

using glm::mat4;

class Map;
struct SDL_Renderer;

class Game
{
public:
    Game(int width, int height, SDL_Renderer * renderer);
    ~Game();
    void run();

private:
    SDL_Renderer * renderer;
    mat4 projectionMatrix;
    Map * map;
};

#endif