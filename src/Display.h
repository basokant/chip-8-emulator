/**
 * @file Display.h 
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Interface for the Display class
 * @version 0.1
 * @date 2022-11-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

#include <cstdint>
#include <vector>

#include <SDL2/SDL.h>

class Display
{
public:
    /**
     * @brief Initialize the display's window and renderer.
     * 
     */
    Display();
    ~Display();

    /**
     * @brief Write a sequence of bytes to the screen at (x_coordinate, y_coordinate).
     * The display XORs the bytes onto the screen: pixels that are already set are cleared and vice-versa.
     * 
     * @param pixels bytes to XOR onto the screen 
     * @return true Collision detected: bits were cleared from the screen
     * @return false No collision detected: no bits were cleared from the screen
     */
    bool write_pixels_to_screen(uint8_t x_coordinate, uint8_t y_coordinate, const std::vector<uint8_t> &pixels);

    /**
     * @brief Clear the screen (set all pixels to background)
     * 
     */
    void clear();

private:
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
};

#endif