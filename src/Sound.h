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

    /**
    * @brief open a audio mixer from SDL_mixer Mix_OpenAudio()
    * and load a sound file into current sound chunk via Mix_LoadWAV and error check them both
    */
    Sound();  

    /**
    * @brief play a pre-loaded sound in a loop
    * with a fixed volum and nearest channal 
    * via Mix_Volume() and Mix_PlayChannel()
    */
    void play_sound();
    
    /**
    * @brief stop the looping sound from playing
    * via Mix_HaltChannel();
    */
    void stop_sound();
    
    /**
    * @brief closes the mix chucks from SDL_Mixer
    * via Mix_FreeChunk, and quit the Mixer all together 
    */
    void close_mix_chuck();

private:
    //Initializing the sound members 
    Mix_Chunk *curr_sound = nullptr;
    bool is_playing = false;
};
