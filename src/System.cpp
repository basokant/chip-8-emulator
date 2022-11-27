#include <string>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>

#include "System.h"

using Clock = std::chrono::high_resolution_clock;

System::System()
    : processor {memory, display}
{}

void System::run() {
    bool quit = false;
    SDL_Event event;
    while (!quit) {
        auto t1 = Clock::now();
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        // Run 10 instructions per frame
        // 16.66666... ms per frame
        const int time_per_frame = 17;
        for (int i = 0; i < 10; ++i) {
            // step forward one processor instruction
            processor.step();
        }
        // decrease delay timer by one
        processor.decrease_delay_timer();
        
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        std::this_thread::sleep_for(std::chrono::milliseconds(time_per_frame - duration));
    }
}

void System::load_rom(const std::string &rom_path) {
    memory.load_file(rom_path.c_str());
}