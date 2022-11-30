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
#include <fstream>
#include "json.h"
using json = nlohmann::json;

#include "System.h"

using Clock = std::chrono::high_resolution_clock;

System::System()
    : processor {memory, display, keyboard}
{
    std::ifstream f("./chip8.config.json");
    json data = json::parse(f);
    emulation_speed = data.value("emulation_speed", 1.0);
}

/**
 * @brief Method that will be running the emulator
 * 
 */
void System::run() { 
    // 60 FPS = 16.66666... ms per frame
    constexpr int time_per_frame = 0;
    while (is_running) {
        auto t1 = Clock::now();
        run_for_one_frame();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - t1).count();
        std::this_thread::sleep_for(std::chrono::milliseconds(time_per_frame - duration));
    }
}

/**
 * @brief Running the emulator for one frame 
 * 
 */
void System::run_for_one_frame() {
    display.clear_renderer();

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            is_running = false; 
        } else if (event.key.type == SDL_KEYDOWN) {
            SDL_Keycode keycode = event.key.keysym.sym;
            on_key_press(keycode);
        } else if (event.key.type == SDL_KEYUP) {
            SDL_Keycode keycode = event.key.keysym.sym;
            on_key_release(keycode);
        }
    }
    //Number of instructions that are run by increasing the emulation speed 
    for (int i = 0; i < 5 * emulation_speed; ++i) {
        // step forward one processor instruction
        processor.step();
    }
    // decrease delay timer by one
    processor.decrease_delay_timer();
    processor.decrease_sound_timer();

    //Play the sound
    if (processor.sound_timer() > 0) {
        sound.play_sound();
    } else {
        sound.stop_sound();
    }
    
    //Writing to the buffer to keep track of pixels on the screen 
    display.write_buffer_to_renderer();
    //Display to screen
    display.present();
}

/**
 * @brief Event handler fired on keypress
 * 
 * @param keycode the SDL keycode of the pressed key 
 */
void System::on_key_press(SDL_Keycode keycode) {
    keyboard.press_key(keycode);
    if (keyboard.is_mapped_key(keycode)) {
        uint8_t chip8_keycode = keyboard.chip8_keycode(keycode);
        processor.wake_from_key_input(chip8_keycode);
    }
}

/**
 * @brief Event handler fired on key release 
 * @param keycode the SDL keycode of the released key
 */
void System::on_key_release(SDL_Keycode keycode) {
    keyboard.release_key(keycode);
}

/**
 * @brief Load the ROM specified at the given path into memory.
 * 
 * @param rom_path path to the specified rom file 
 */
void System::load_rom(const std::string &rom_path) {
    memory.load_file(rom_path.c_str());
}

/**
 * @brief Set a new emulation speed 
 * 
 * @param new_speed specified speed for emulation 
 */
void System::set_emulation_speed(double new_speed) {
    emulation_speed = new_speed;
}