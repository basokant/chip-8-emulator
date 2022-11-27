/**
 * @file Sound.cpp
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Implementation file for the Sound class
 * @version 0.1
 * @date 2022-11-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>

#include "Sound.h"

Sound::Sound() {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        std::cerr << "SDL sound mixer error" << Mix_GetError();
    }

    curr_sound = Mix_LoadWAV("assets/buzz.wav");
    if (curr_sound == NULL){
        std::cerr << "SDL sound mixer load audio file error" << Mix_GetError();
    }
}

void Sound::play_sound() {
    //first arg is the channal we want to use to play the sound, -1 will use the nearest available channel
    //2nd arg is the mix_chunk being played
    //3rd arg is the number of repeats of the give mix_chunk, set to 0 for only play once needed
    Mix_Volume(-1, 128);
    Mix_PlayChannel(-1, curr_sound, -1);
}

void Sound::stop_sound() {
    Mix_HaltChannel(-1);
}

void Sound::close_mix_chuck() {
    Mix_FreeChunk(Sound::curr_sound);
    Sound::curr_sound == NULL;
    Mix_Quit();
}