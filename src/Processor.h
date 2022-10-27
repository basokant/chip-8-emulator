/**
 * @file Processor.h
 * @author David Tran, Ben Asokanthan, Dhruv Panicker, Davis Mtui, Sean Hou
 * @brief Interface for the Processor class
 * @version 0.1
 * @date 2022-11-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <array>

/*
See CHIP-8 documentation
http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#2.5
*/

class Processor
{
public:
    Processor() = default;
    ~Processor() = default;

    // Start running the processor
    void run();

private:
    /**
     * @brief Read the byte stored at memory address addr
     * 
     * @param addr A 16-byte address in memory
     * @return uint8_t 
     */
    uint8_t read_memory(uint16_t addr);

    /**
     * @brief Write a byte to memory at address addr
     * 
     */
    void write_memory(uint16_t addr, uint8_t byte);

private:
    // 36 CHIP-8 instructions
    /* declare all instruction names following documentation */
    void sys(uint16_t addr);

    /**
     * @brief ADD Vx, byte instruction: add byte to Vx register
     *
     * @param vx number of the register (0x0-0xf for v0-vf)
     * @param byte 8-bit value (0x00-0xff)
     */
    void add(uint8_t vx, uint8_t byte);

    /**
     * @brief Return from a subroutine.
     * 
     * The interpreter sets the program counter to the address at the top of the stack, 
     * then subtracts 1 from the stack pointer.
     *
     */
    void ret();

private:
    /*
    v0-vF: 16 8-bit registers

    PC: 16-bit register
    SP: 8-bit register

    DT: 16-bit delay timer register
    ST: 16-bit sound timer register
    */

    std::array<uint16_t, 16> v_registers = {0};
    uint16_t pc = 0; // program counter
    uint8_t sp = 0; // stack pointer

    uint16_t dt = 0; // delay timer
    uint16_t st = 0; // sound timer
};
