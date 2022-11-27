#include <stdlib.h>
#include <vector>
#include <SDL2/SDL.h>

#include "Display.h"
#include "SDLException.h"

Display::Display() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw SDLException {};
    }
    
    window = SDL_CreateWindow("CHIP OFF THE BLOCK", 100, 100, screen_width, screen_height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    
    clear();

    // TODO: test, remove later
    // write_pixel(1, 10, 10);
    // SDL_Rect rect {10, 10, 100, 100};
    // SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

Display::~Display() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


// 00100010 <- pixel_row
// 10010100
// 10101010


bool Display::write_pixels_to_screen(uint8_t x_coordinate, uint8_t y_coordinate, const std::vector<uint8_t> &sprite) {
    const int sprite_height = sprite.size(); // sprites can be up to 15 pixels tall
    const int sprite_width = 8; // sprites are ALWAYS 8 pixels wide

    // check if this sprite overwrites a pixel
    bool pixel_overwritten = false;
    for (int row = 0; row < sprite_height; ++row) {
        uint8_t pixel_row = sprite[row];
        for (int column = 0; column < sprite_width; ++column) {
            bool pixel = (pixel_row >> (7 - column)) & 1;
            if (write_pixel(pixel, x_coordinate + column, y_coordinate + row))
                pixel_overwritten = true;
        }
    }
    
    // Present the pixels drawn to the renderer
    SDL_RenderPresent(renderer);
    return pixel_overwritten;
}

void Display::clear() {
    // set draw color to black for clearing
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    // set draw color to white for drawing pixels
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    // clear the buffer
    pixel_buffer = std::array<std::array<bool, 64>, 32> {0};
}

bool Display::write_pixel(bool pixel, uint8_t x_coordinate, uint8_t y_coordinate) {
    // CHIP8 XORs the current pixel with the pixel to draw to determine the new pixel to show

    bool old_pixel_value = pixel_buffer[y_coordinate][x_coordinate];
    bool new_pixel_value = pixel ^ old_pixel_value;
    bool pixel_was_cleared = false;
    if (new_pixel_value == old_pixel_value) {
        // nothing changed, nothing to do
        return pixel_was_cleared; // false => no overwrite
    }

    // black if pixel is cleared, white if pixel is set
    pixel_buffer[y_coordinate][x_coordinate] = new_pixel_value;
    if (new_pixel_value) {
        // pixel is set, use white
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    } else {
        // pixel is cleared, use black
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
        pixel_was_cleared = true;
    }

    // get the scaling factor of the window
    const int x_scale = screen_width / CHIP8_WIDTH;
    const int y_scale = screen_height / CHIP8_HEIGHT;

    const int pixel_x = x_coordinate * x_scale;
    const int pixel_y = y_coordinate * y_scale;
    const int pixel_width = x_scale;
    const int pixel_height = y_scale;

    SDL_Rect scaled_pixel {pixel_x, pixel_y, pixel_width, pixel_height};
    if (SDL_RenderFillRect(renderer, &scaled_pixel) != 0) {
        throw SDLException {};
    }

    return pixel_was_cleared;
}
