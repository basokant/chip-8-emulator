/**
 * @file Memory.cpp
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Implementation file for the Memory class
 * @version 0.1
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <array>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <fstream>

#include "Memory.h"


/**
    * @brief Copies the binary data stored in the file into the memory array.
    * 
    * @param file_path path to the file
    */
void load_file(char const* filename) {
    // Open the file as binary stream set the pointer to the begginig of the file  
    std::ifstream file(filename, std::ios::binary | std::ios::ate)

    if(file.is_open()) {
        //Get size of the file, and store it in a buffer
        int size = file.tellg();
        char * buffer  = new char[size];

        //Cheeck this 
        file.seekg(0, std::ios:beg);
        file.read(buffer, size);
        file.close();

        //Load the 
        for(uint8_t i = 0; i < size; ++i ){
            memory[START_MEMORY_ADRESS + i] = buffer[i];
        }

        delete[] buffer;

    }

    /**
    * @brief Reads the byte in memory located at the given address
    * 
    * @param addr address in memory to read from
    * @return uint8_t byte read from memory
    */
    uint8_t read_memory(uint16_t addr) {
        return memory[addr]
    }


    /**
    * @brief Writes a byte in memory to the given address
    * 
    * @param addr address in memory to write to
    * @param byte byte to write
    */
    void write_memory(uint16_t addr, uint8_t byte) {
        memory[addr] = byte
    }   
}




