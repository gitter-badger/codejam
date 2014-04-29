#include <SDL2/SDL.h>
#include "glsl_utils.h"
#include "game.h"
#include <GL/glew.h>

int main(int argc, char * argv[])
{
    int width = 800;
    int height = 600;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("Lolo 3D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    glewInit();
    GLSLUtils::installShaders();

    Game game(width, height, renderer);
    game.run();

    SDL_Quit();
    return 0;
}