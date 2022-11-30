/**
 * @file main.cpp
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief The main entry point of the program
 * @version 0.1
 * @date 2022-11-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

#include "System.h"
#include "ProcessorException.h"
#include "FileNotFoundException.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "enter a ROM file to load\n";
        return 1;
    }

    const std::string rom_name(argv[1]);

    System emulator;
    try {
        emulator.load_rom(rom_name);
        emulator.run();
    } catch (ProcessorException &e) {
        std::cerr << "Error: " << e.what() << '\n';
    } catch (FileNotFoundException &e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}