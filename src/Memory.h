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

#ifndef PROCESSOR_H_INCLUDED
#define PROCESSOR_H_INCLUDED

#include <array>
#include <cstdint>
#include <string>

class Memory
{
public:
    /**
     * @brief Copies the binary data stored in the file into the memory array.
     * 
     * @param file_path path to the file
     */
    void load_file(const std::string &file_path);

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
    // CHIP-8 has 4KB of addressable memory = 0x10000 bytes
    std::array<uint8_t, 0x10000> memory;
};

