#include <vector>
#include <fstream>
#include <SDL2/SDL.h>
#include <iostream>

#include "json.h"
using json = nlohmann::json;

#include "Display.h"
#include "SDLException.h"

/**
* @brief Initialize the display's window and renderer.
* 
*/
Display::Display() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw SDLException {};
    }

    std::ifstream f("./chip8.config.json");
    json json = json::parse(f);

    screen_width = json.value("screen_width", 640);
    screen_height = (screen_width / CHIP8_WIDTH) * CHIP8_HEIGHT;
    
    window = SDL_CreateWindow("CHIP OFF THE BLOCK", 100, 100, screen_width, screen_height, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    
    clear_renderer();

    SDL_RenderPresent(renderer);
}


/**
* @brief destroy the display's window and renderer.
* 
*/
Display::~Display() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


// 00100010 <- pixel_row
// 10010100
// 10101010


/**
* @brief Write a sequence of bytes to the buffer at (x_coordinate, y_coordinate).
* The display XORs the bytes onto the screen: pixels that are already set are cleared and vice-versa.
* 
* @param sprite sprite bytes to XOR onto the screen 
* @return true Collision detected: bits were cleared from the screen
* @return false No collision detected: no bits were cleared from the screen
*/
bool Display::write_pixels_to_buffer(uint8_t x_coordinate, uint8_t y_coordinate, const std::vector<uint8_t> &sprite) {
    const int sprite_height = sprite.size(); // sprites can be up to 15 pixels tall
    const int sprite_width = 8; // sprites are ALWAYS 8 pixels wide

    // check if this sprite overwrites a pixel
    bool pixel_overwritten = false;
    for (int row = 0; row < sprite_height; ++row) {
        uint8_t pixel_row = sprite[row];
        for (int column = 0; column < sprite_width; ++column) {
            bool pixel = (pixel_row >> (7 - column)) & 1;
            if (write_pixel_to_buffer(pixel, x_coordinate + column, y_coordinate + row))
                pixel_overwritten = true;
        }
    }

    return pixel_overwritten;
}

/**
* @brief Writes the pixel buffer to the renderer
* 
*/
void Display::write_buffer_to_renderer() const {
    for (int row = 0; row < pixel_buffer.size(); ++row) {
        const std::array<bool, 64> &pixel_row = pixel_buffer[row];
        for (int column = 0; column < pixel_row.size(); ++column) {
            bool pixel = pixel_row[column];
            write_pixel_to_renderer(pixel, column, row);
        }
    }
}

/**
* @brief Presents the SDL renderer
* 
*/
void Display::present() const {
    SDL_RenderPresent(renderer);
}

/**
* @brief Clear the screen (set all pixels to background)
* 
*/
void Display::clear_renderer() const {
    // set draw color to black for clearing
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    // set draw color to white for drawing pixels
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    
}

/**
* @brief clear the buffer(set all buffer mermory to zero)
* 
*/
void Display::clear_buffer() {
    // clear the buffer
    pixel_buffer = std::array<std::array<bool, 64>, 32> {0};
}

/**
* @brief 
* 
* @param pixel 
* @param x_coordinate 
* @param y_coordinate 
*/
void Display::write_pixel_to_renderer(bool pixel, uint8_t x_coordinate, uint8_t y_coordinate) const {
    if (pixel) {
        // pixel is set, use white
        SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    } else {
        SDL_SetRenderDrawColor(renderer, 0x0, 0x0, 0x0, 0xff);
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
}

/**
* @brief XOR a pixel to the buffer at x_coordinate and y_coordinate
* 1 = on
* 0 = off
* 
* @param pixel pixel value: 0 = off, 1 = on
* @param x_coordinate x-coordinate of the pixel
* @param y_coordinate y-coordinate of the pixel
* @return true the given coordinate pixel was overwritten
* @return false the given pixel was not overwritten
*/
bool Display::write_pixel_to_buffer(bool pixel, uint8_t x_coordinate, uint8_t y_coordinate) {
    // CHIP8 XORs the current pixel with the pixel to draw to determine the new pixel to show

    // Handle coordinates outside of the screen bounds by wrapping coordinates
    x_coordinate %= 64;
    y_coordinate %= 32;

    bool old_pixel_value = pixel_buffer[y_coordinate][x_coordinate];
    bool new_pixel_value = pixel ^ old_pixel_value;
    bool pixel_was_cleared = (old_pixel_value == 1) && (new_pixel_value == 0);

    // black if pixel is cleared, white if pixel is set
    pixel_buffer[y_coordinate][x_coordinate] = new_pixel_value;
    return pixel_was_cleared;
}
