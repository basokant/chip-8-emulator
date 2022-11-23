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
#include <vector>

#include "Memory.h"

Memory::Memory() {}
    
/**
* @brief Copies the binary data stored in the file into the memory array.
* 
* @param file_path path to the file
*/
void Memory::load_file(char const* filename) {

    // Open the file as binary stream set the pointer to the beginning of the file
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    // get size of file
    std::streampos size = file.tellg();
    file.seekg(0, std::ios::beg);

    // create buffer for file as a vector
    std::vector<char> buffer(size);

    // if we are able to read data into buffer
    if  (file.read(buffer.data(), size)) {

        for(uint8_t i = 0; i < size; ++i ){

            // copy data from beginning of buffer to the start addr of memory
            memory[START_MEMORY_ADRESS + i] = buffer[i];
        }
    }

    // close file
    file.close();

}


/**
* @brief Reads the byte in memory located at the given address
* 
* @param addr address in memory to read from
* @return uint8_t byte read from memory
*/
uint8_t Memory::read_memory(uint16_t addr) const {
    return memory[addr];
}


/**
* @brief Writes a byte in memory to the given address
* 
* @param addr address in memory to write to
* @param byte byte to write
*/
void Memory::write_memory(uint16_t addr, uint8_t byte) {
    memory[addr] = byte;
}   







