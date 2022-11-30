/**
 * @file SDLExcetion.cpp
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Implementation file for SDLException
 * @version 0.1
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */

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