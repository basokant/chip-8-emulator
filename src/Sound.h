/**
 * @file Sound.h
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Interface for the Sound class
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
 
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

/**
 * @brief The audio unit of the processor that produces sound.
 * 
 */
class Sound 
{
    
public:
    Sound();  

    void play_sound();

    void stop_sound();

    void close_mix_chuck();

private:
    Mix_Chunk *curr_sound = nullptr;
};
