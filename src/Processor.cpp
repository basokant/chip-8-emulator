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

#include "Processor.h"

/*
void Processor::run() {
    while (running) {
        instruction (integer) = read_instruction_from_memory()
        switch (instruction & 0xf) {
            case 0: run_instruction_0(); break;
            case 0: run_instruction_1(); break;
            ...
            case 0: run_instruction_100(); break;
        }
    }
}
*/

void Processor::sys(uint16_t addr) {
    // TODO
}

/**
 * @brief ADD Vx, byte instruction: add byte to Vx register
 * 
 * @param vx number of the register (0x0-0xf for v0-vf)
 * @param byte 8-bit value (0x00-0xff)
 */
void Processor::add(uint8_t vx, uint8_t byte) {
    v_registers[vx] += byte;
}

/**
 * @brief Return from a subroutine.
 *
 * The interpreter sets the program counter to the address at the top of the stack,
 * then subtracts 1 from the stack pointer.
 *
 */
void Processor::ret() {
    uint8_t top_of_stack = read_memory(sp);
    pc = top_of_stack;
    // pop stack: decrement stack pointer
    sp -= 1;
}

/**
 * @brief Read the byte stored at memory address addr
 *
 * @param addr A 16-byte address in memory
 * @return uint8_t
 */
uint8_t read_memory(uint16_t addr) {
    return 1;
}

/**
 * @brief Write a byte to memory at address addr
 */
void write_memory(uint16_t addr, uint8_t byte) {
    // TODO: implement write
}
