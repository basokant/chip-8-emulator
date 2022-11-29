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

#ifndef SYSTEM_H_INCLUDED
#define SYSTEM_H_INCLUDED

#include <string>

#include "Display.h"
#include "Processor.h"
#include "Memory.h"
#include "Keyboard.h"
#include "Sound.h"

/**
 * @brief The full emulator consisting of the processor, memory, display, keyboard, and sound.
 * 
 */
class System
{
public:
    System();
    ~System() = default;

    /**
     * @brief Run the emulator.
     * 
     */
    void run();

    /**
     * @brief Load the ROM specified at the given path into memory.
    */
    void load_rom(const std::string &rom_path);

    /**
     * @brief Set a new emulation speed
     * 
     * @param new_speed 
     */
    void set_emulation_speed(double new_speed);

private:
    /**
     * @brief Run the emulator for one frame
     */
    void run_for_one_frame();

    /**
     * @brief Event handler fired on keypress
     * @param keycode the SDL keycode of the pressed key 
     */
    void on_key_press(SDL_Keycode keycode);

    /**
     * @brief Event handler fired on key release 
     * @param keycode the SDL keycode of the released key
     */
    void on_key_release(SDL_Keycode keycode);

private:
    Processor processor;
    Memory memory;
    Display display;
    Keyboard keyboard;
    Sound sound;

    // flag indicating if the emulator is running
    bool is_running = true;

    // The speed of the emulator
    double emulation_speed = 1.0;
};

#endif