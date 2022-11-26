/**
 * @file Memory.h
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Interface for the Memory class
 * @version 0.1
 * @date 2022-11-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include <array>
#include <cstdint>
#include <string>

class Memory
{
public:
    Memory();
    ~Memory() = default;
    /**
     * @brief Copies the binary data stored in the file into the memory array.
     * 
     * @param file_path path to the file
     */
    void load_file(char const* filename);


    /**
     * @brief Reads the byte in memory located at the given address
     * 
     * @param addr address in memory to read from
     * @return uint8_t byte read from memory
     */
    uint8_t read_memory(uint16_t addr) const;

    /**
     * @brief Writes a byte in memory to the given address
     * 
     * @param addr address in memory to write to
     * @param byte byte to write
     */
    void write_memory(uint16_t addr, uint8_t byte);

    /**
     * @brief Dump the raw memory array.
     * 
     * @return std::array<uint8_t, 0x10000> 
     */
    std::array<uint8_t, 0x10000> dump() const;

private:
    // Array storing memory
    // TODO: separate this into a memory class later
    // CHIP-8 has 4KB of addressable memory = 0x1000 bytes
    std::array<uint8_t, 0x1000> memory;


    const unsigned int START_MEMORY_ADRESS = 0X200;

    //Position where ROM files will know where fonts begin in memory 
    const static unsigned int FONTSET_ADDRESS = 0x50;
    //Length of the font array
    const static unsigned int FONTSET_LENGTH = 80;

    uint8_t font_characters[FONTSET_LENGTH] = {
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

};

#endif