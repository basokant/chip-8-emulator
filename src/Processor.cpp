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
* @brief Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx
* @param vx number of the register (0x0-0xf for v0-vf)
* @param vy number of the register (0x0-0xf for v0-vf)
*/
void Processor::chip_and(uint8_t vx, uint8_t vy) {
    v_registers[vx] = v_registers[vx] & v_registers[vy];
}

/**
* @brief Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx
* @param vx number of the register (0x0-0xf for v0-vf)
* @param vy number of the register (0x0-0xf for v0-vf)
*/
void Processor::chip_or(uint8_t vx, uint8_t vy) {
    v_registers[vx] = v_registers[vx] | v_registers[vy];

}

/**
* @brief Performs a bitwise XOR on the values of Vx and Vy, then stores the result in Vx
* @param vx number of the register (0x0-0xf for v0-vf)
* @param vy number of the register (0x0-0xf for v0-vf)
*/
void Processor::chip_xor(uint8_t vx, uint8_t vy) {
    v_registers[vx] = v_registers[vx] ^ v_registers[vy];
}

/**
 * @brief The interpreter puts the value byte into register Vx.
 * @param vx number of the register (0x0-0xf for v0-vf)
 * @param byte 8-bit value (0x00-0xff)
 */
void Processor::load_byte(uint8_t vx, uint8_t byte) {
    v_registers[vx] = byte;
}

/**
 * @brief Stores the value of register Vy in register Vx.
 * @param vx number of the register (0x0-0xf for v0-vf)
 * @param vy number of the register (0x0-0xf for v0-vf)
 */
void Processor::load_register(uint8_t vx, uint8_t vy) {
    v_registers[vx] = v_registers[vy];
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
 * @brief Stores the address in register i.
 * 
 * @param i number of the register (0x-0xf for v0-vf)
 * @param addr A 16-bit address in memory
 */
void Processor::load_addr(uint8_t i, uint16_t addr) {
    v_registers[i] = addr;
}


/**
 * @brief The program jumps by setting the program counter to an address (addr plus the value of v0)
 * 
 * @param v0 number of the register (0x0-0xf for v0-vf)
 * @param addr A 16-bit address in memory
 */
void Processor::jump_register(uint8_t v0, uint16_t addr) {
    pc = addr + v_registers[v0];
}


/**
 * @brief Generate a random number from 0 to 255, which is then ANDed with a value byte, and stored in a register vx.
 * 
 * @param vx number of the register (0x0-0xf for v0-vf)
 * @param byte 8-bit value (0x00-0xff)
 */
void Processor::random(uint8_t vx, uint8_t byte) {

}


/**
 * @brief Display n-byte sprite starting at memory location I at (vx, vy), set VF = collision.
 * 
 * @param vx number of the register (0x0-0xf for v0-vf)
 * @param vy number of the register (0x0-0xf for v0-vf)
 * @param nibble 4-bit value (0x0-0xf)
 */
void Processor::display(uint8_t vx, uint8_t vy, uint8_t nibble) {

}


/**
 * @brief Skip next instruction if key with the value of vx is pressed.
 * 
 * @param vx number of the register (0x0-0xf for v0-vf)
 */
void Processor::skip_pressed(uint8_t vx) {
    if (is_pressed(vx)) {
        pc += 2;
    }
}


/**
 * @brief Skip next instruction if key with the value of vx is NOT pressed.
 * 
 * @param vx number of the register (0x0-0xf for v0-vf)
 */
void Processor::skip_not_pressed(uint8_t vx) {
    if (!is_pressed(vx)) {
        pc += 2;
    }
}


/**
 * @brief Set register vx to the value of the delay timer.
 * 
 * @param vx number of the register (0x0-0xf for v0-vf)
 */
void Processor::load_register_from_dt(uint8_t vx) {
    v_registers[vx] = dt;
}


/**
 * @brief Wait for a key press, store the value of the key in register vx.
 * 
 * @param vx number of the register (0x0-0xf for v0-vf)
 */
void Processor::load_key(uint8_t vx) {
    uint16_t key = key_input();

    v_registers[vx] = key;
}


/**
 * @brief Set delay timer to the value of register vx
 * 
 * @param vx number of the register (0x0-0xf for v0-vf)
 */
void Processor::load_dt_from_register(uint8_t vx) {
    dt = v_registers[vx];
}


/**
 * @brief Set the sound timer to the value of register vx
 * 
 * @param vx number of the register (0x0-0xf for v0-vf)
 */
void Processor::load_st_from_register(uint8_t vx) {
    st = v_registers[vx];
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


bool is_pressed(uint16_t key) {
    // TODO: implement emulator input
}


uint16_t key_input() {
    // TODO: implement emulator input
    return 1;
}