/**
 * @file System.h
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Interface for the Systen class
 * @version 0.1
 * @date 2022-11-08
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


private:
    Processor processor;
    Memory memory;
    Display display;
};

#endif