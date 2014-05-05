#include "event.h"

#include <SDL/SDL.h>
#include "objects/blagger.h"

void
Event::processEvents()
{
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
          case SDLK_q:
            *this->run = false;
            break;

          case SDLK_LEFT:
            this->blagger->direction = Direction::LEFT;
            break;

          case SDLK_RIGHT:
            this->blagger->direction = Direction::RIGHT;
            break;

          case SDLK_SPACE:
            this->blagger->jump(); // TODO use State::JUMP
            break;

          default:
            break;
        }
        break;

      case SDL_KEYUP:
        switch (event.key.keysym.sym) {
          case SDLK_LEFT:
            if (this->blagger->direction == Direction::LEFT)
              this->blagger->direction = Direction::STOP;
            break;

          case SDLK_RIGHT:
            if (this->blagger->direction == Direction::RIGHT)
              this->blagger->direction = Direction::STOP;
            break;

          default:
            break;
        }
        break;

      default:
        break;
    }
  }
}
