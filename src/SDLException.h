#ifndef SDL_EXCEPTION_H_INCLUDED
#define SDL_EXCEPTION_H_INCLUDED

#include <stdexcept>

class SDLException : public std::exception {
public:
    const char *what() const noexcept override;
};

#endif