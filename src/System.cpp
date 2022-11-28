/**
 * @file System.h
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Interface for the System class
 * @version 0.5
 * @date 2022-11-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <SDL2/SDL.h>

#include "System.h"

using Clock = std::chrono::high_resolution_clock;

System::System()
    : processor {memory, display, keyboard}
{}

void System::run() { 
    // 60 FPS = 16.66666... ms per frame
    constexpr int time_per_frame = 17;
    while (is_running) {
        auto t1 = Clock::now();
        run_for_one_frame();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        std::this_thread::sleep_for(std::chrono::milliseconds(time_per_frame - duration));
    }
}

void System::run_for_one_frame() {
    display.clear_renderer();

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            is_running = false; 
        } else if (event.key.type == SDL_KEYDOWN) {
            keyboard.press_key(event.key.keysym.sym);
        } else if (event.key.type == SDL_KEYUP) {
            keyboard.release_key(event.key.keysym.sym);
        }
    }
    for (int i = 0; i < 10; ++i) {
        // step forward one processor instruction
        processor.step();
    }
    // decrease delay timer by one
    processor.decrease_delay_timer();

    if (processor.sound_timer() > 0) {
        sound.play_sound();
    } else {
        sound.stop_sound();
    }
    
    display.write_buffer_to_renderer();
    display.present();
}

void System::load_rom(const std::string &rom_path) {
    memory.load_file(rom_path.c_str());
}