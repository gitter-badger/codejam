#include "game.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "map.h"

Game::Game(int width, int height, SDL_Renderer * renderer) : renderer(renderer)
{
    projectionMatrix = glm::perspective(60.0f, float(width) / height, 0.1f, 100.0f);
    map = new Map("data/lolo1.map", projectionMatrix);

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
}

Game::~Game()
{
    delete map;
}

void Game::run()
{
    bool run = true;
    bool wireframe = false;
    SDL_Event event;

    do {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                SDL_Keycode sym = event.key.keysym.sym;

                if (sym == SDLK_w) {
                    wireframe = !wireframe;
                    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_LINE : GL_FILL);
                }
                if (sym == SDLK_q)
                    run = false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        map->render();

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    } while (run);
}