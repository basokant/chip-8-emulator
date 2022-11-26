#include <SDL2/SDL.h>

#include "System.h"

System::System()
    : processor {
        // read memory callback: anonymous function that forwards to memory.read_memory
        [this](uint16_t addr) { return this->memory.read_memory(addr); },
        // write memory callback: anonymous function that forwards to memory.write_memory
        [this](uint16_t addr, uint8_t byte) { return this->memory.write_memory(addr, byte); },
        // write to display callback: anonymous function that forwards to display.write_pixels_to_screen
        [this](uint8_t x_coordinate, uint8_t y_coordinate, const std::vector<uint8_t> &pixels) {
            return this->display.write_pixels_to_screen(x_coordinate, y_coordinate, pixels);
        }
    }
{}


void System::run() {
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        // step forward one processor instruction
        processor.step();
    }
}