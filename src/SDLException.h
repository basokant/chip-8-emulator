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