#include <SDL2/SDL.h>

#include "SDLException.h"

/**
 * @brief Custom exception class for all errors in the SDL Library 
 * 
 * @return const char* 
 */
const char *SDLException::what() const noexcept {
    return SDL_GetError(); 
}