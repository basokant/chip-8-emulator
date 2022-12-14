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

#include <array>
#include <cstdint>
#include <vector>

#include <SDL2/SDL.h>

/**
 * @brief A class representing the window and renderer for the emulator.
 * 
 */
class Display
{
public:
    /**
     * @brief Initialize the display's window and renderer.
     * 
     */
    Display();

    /**
    * @brief destroy the display's window and renderer.
    * 
    */
    ~Display();

    /**
     * @brief Write a sequence of bytes to the buffer at (x_coordinate, y_coordinate).
     * The display XORs the bytes onto the screen: pixels that are already set are cleared and vice-versa.
     * 
     * @param sprite sprite bytes to XOR onto the screen 
     * @return true Collision detected: bits were cleared from the screen
     * @return false No collision detected: no bits were cleared from the screen
     */
    bool write_pixels_to_buffer(uint8_t x_coordinate, uint8_t y_coordinate, const std::vector<uint8_t> &sprite);

    /**
     * @brief Writes the pixel buffer to the renderer
     * 
     */
    void write_buffer_to_renderer() const;

    /**
     * @brief Presents the SDL renderer
     * 
     */
    void present() const;

    /**
     * @brief Clear the screen (set all pixels to background)
     * 
     */
    void clear_renderer() const;

    /**
     * @brief clear the buffer(set all buffer mermory to zero)
     * 
     */
    void clear_buffer();

private:

    /**
     * @brief 
     * 
     * @param pixel 
     * @param x_coordinate 
     * @param y_coordinate 
     */
    void write_pixel_to_renderer(bool pixel, uint8_t x_coordinate, uint8_t y_coordinate) const;

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
    bool write_pixel_to_buffer(bool pixel, uint8_t x_coordinate, uint8_t y_coordinate);

private:
    static constexpr int CHIP8_WIDTH = 64;
    static constexpr int CHIP8_HEIGHT = 32;

    std::array<std::array<bool, CHIP8_WIDTH>, CHIP8_HEIGHT> pixel_buffer = {0};

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    int screen_width = 640; // default width
    int screen_height = 320; // default height

    std::array<int, 3> foreground_color {255,255,255};
    std::array<int, 3> background_color {0,0,0};
};

#endif