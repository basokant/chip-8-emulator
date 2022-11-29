/**
 * @file Keyboard.h
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Interface for the Keyboard class
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include <array>
#include <cstdint>
#include <unordered_map>
#include <SDL2/SDL.h>

/**
 * @brief A class representing the keyboard for the emulator controlled through the keyboard.
 */
class Keyboard
{
public:
    Keyboard();
    ~Keyboard() = default;

    /**
     * @brief Press the CHIP8 key associated with the given keyboard key
     */
    void press_key(SDL_Keycode code);
    
    /**
     * @brief Release the CHIP8 key associated with the given keyboard key
     */
    void release_key(SDL_Keycode code);

    /**
     * @brief Check if the given CHIP-8 key is pressed
     */
    bool is_pressed(uint8_t chip8_key);

    /**
     * @brief Check if the pressed key is mapped to one of the CHIP-8 keys.
     */
    bool is_mapped_key(SDL_Keycode keycode);

    /**
     * @brief Get the mapped CHIP-8 key (0x0 to 0xF) of this key.
     */
    uint8_t chip8_keycode(SDL_Keycode keycode);

private:
    /**
     * The layout of the chip-8 virtual keyboard.
     * 
     * 1 2 3 C
     * 4 5 6 D
     * 7 8 9 E
     * A 0 B F
     */
    std::array<bool, 16> key_pressed = {0};

    // maps hardware keycode to CHIP8 virtual keycode.
    const std::unordered_map<SDL_Keycode, uint8_t> keymap;
};

#endif