/**
 * @file Processor.cpp
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Implementation file for the Processor class
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
#include <sstream>

#include "Processor.h"

/**
 * @brief Construct a new Processor::Processor object
 * 
 * Seeds the random number generator used by the RANDOM instruction
 */
Processor::Processor() {
    // seed the random-number generator for future calls to RAND
    std::srand(std::time(0));
}

/**
 * @brief Run the processor until the end of memory.
 */
void Processor::run() {
    // TODO: implement proper program execution (not hardcoded to a test ROM)
    // loop from beginning of memory to the end of our test program
    while (pc < 0x6) {
        uint16_t instruction_to_run = read_instruction_from_memory();

        // TODO: implement decoding for all instructions
        // for now, just LD and ADD for the test ROM
        switch (instruction_to_run & 0xf000) {
            // instruction can be identified by 4 most significant bits
            case 0x6000: {
                // LD Vx, byte
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                // byte is bits 0-7
                uint8_t byte = instruction_to_run & 0xff;
                load_byte(vx, byte);
            } break;
            case 0x8000: {
                // ADD Vx, Vy
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                // vy is bits 4-7
                uint8_t vy = (instruction_to_run >> 4) & 0xf;
                add_registers(vx, vy);
            } break;
            default: {
                std::cout << "Unimplemented instruction! " << instruction_to_run << '\n';
            }
        }
    }
}

/**
 * @brief Load a byte-array into memory at 0x0.
 * @param byte_array The list of bytes to load into memory.
 */
void Processor::load_memory(const std::array<uint8_t, 0x10000> &byte_array) {
    memory = byte_array;
}

/**
 * @brief Dump the registers of the CPU into a printable string.
 *
 * @return a string containing all the register values
 */
std::string Processor::dump() {
    std::stringstream dump_ss;
    for (int i = 0; i < v_registers.size(); i++)
    {
        dump_ss << "Register V" << i << ": " << v_registers[i] << "\n";
    }
    dump_ss << "PC: " << pc << "\n";
    // convert SP to an int because stringstream interprets uint8_t's as chars
    dump_ss << "SP: " << static_cast<int>(sp) << "\n";
    dump_ss << "DT: " << dt << "\n";
    dump_ss << "ST: " << st << "\n";
    return dump_ss.str();
}

/**
 * @brief Read the byte stored at memory address addr
 *
 * @param addr A 16-byte address in memory
 * @return uint8_t
 */
uint8_t Processor::read_memory(uint16_t addr) {
    return memory[addr];
}

/**
 * @brief Write a byte to memory at address addr
 */
void Processor::write_memory(uint16_t addr, uint8_t byte) {
    memory[addr] = byte;
}

/**
 * @brief Read the next instruction from memory pointed
 * to by the PC, and increment the PC
 *
 * @return uint16_t
 */
uint16_t Processor::read_instruction_from_memory() {
    // read next 2 bytes pointed by PC, then concatenate
    uint8_t d1 = read_memory((uint16_t)pc++); //0x20
    uint8_t d2 = read_memory((uint16_t)pc++); //0x40

    uint16_t instr = ((uint16_t)d1 << 8) | d2;
    return instr;
}
