#include <string>
#include <SDL2/SDL.h>

#include "System.h"

System::System()
    : processor {memory, display}
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

void System::load_rom(const std::string &rom_path) {
    memory.load_file(rom_path.c_str());
}