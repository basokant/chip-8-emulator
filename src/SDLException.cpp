#include <SDL2/SDL.h>

#include "SDLException.h"

const char *SDLException::what() const noexcept {
    return SDL_GetError(); 
}