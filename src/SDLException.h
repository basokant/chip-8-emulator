/**
 * @file SDLException.h
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Interface for the SDLException
 * @version 0.1
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SDL_EXCEPTION_H_INCLUDED
#define SDL_EXCEPTION_H_INCLUDED

#include <stdexcept>

/**
 * @brief A custom exception class for errors produced by the SDL library.
 * 
 */
class SDLException : public std::exception {
public:
    const char *what() const noexcept override;
};

#endif