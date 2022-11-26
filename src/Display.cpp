#include <stdlib.h>
#include <vector>
#include <SDL2/SDL.h>

#include "Display.h"
#include "SDLException.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 320

Display::Display() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw SDLException {};
    }
    
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer);
    SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
}

Display::~Display() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Display::write_pixels_to_screen(uint8_t x_coordinate, uint8_t y_coordinate, const std::vector<uint8_t> &pixels) {
    // TODO: implement write_pixels_to_screen to interface with SDL2
    return true;
}