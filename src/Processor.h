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

    /**
     * @brief Jumps to a machine code routine at addr.
     *
     * This instruction is only used on the old computers on which Chip-8 was originally
     * implemented. It is ignored by modern interpreters.
     * @param addr The 16-bit address to jump to
     */
    void sys(uint16_t addr);

    /**
     * @brief Return from a subroutine.
     *
     * The interpreter sets the program counter to the address at the top of the stack,
     * then subtracts 1 from the stack pointer.
     *
     */
    void ret();

    /**
     * @brief The interpreter sets the program counter to addr.
     * 
     * @param addr 16-bit address to jump to
     */
    void jp(uint16_t addr);

    /**
     * @brief The interpreter jumps to addr, pushing the current PC to the stack.
     * 
     * @param addr 16-bit address to jump to
     */
    void call(uint16_t addr);

    /**
     * @brief Skips the next instruction if vx == byte
     * 
     * @param vx The number of the register (0x0-0xf)
     * @param byte The byte to compare with
     */
    void se_byte(uint8_t vx, uint8_t byte);

    /**
     * @brief Skips the next instruction if vx != byte
     * @param vx The number of the register (0x0-0xf)
     * @param byte The byte to compare with
     */
    void sne_byte(uint8_t vx, uint8_t byte);

    /**
     * @brief Skips the next instruction if vx == vy
     * 
     * @param vx The number of the first register (0x0-0xf)
     * @param vy The number of the second register (0x0-0xf)
     */
    void se_register(uint8_t vx, uint8_t vy);

    /**
     * @brief ADD Vx, byte instruction: add byte to Vx register
     *
     * @param vx number of the register (0x0-0xf for v0-vf)
     * @param byte 8-bit value (0x00-0xff)
     */
    void add(uint8_t vx, uint8_t byte);

    /**
     * @brief Performs a bitwise AND on the values of Vx and Vy, then stores the result in Vx
     * @param vx number of the register (0x0-0xf for v0-vf)
     * @param vy number of the register (0x0-0xf for v0-vf)
     */

    void chip_and(uint8_t vx, uint8_t vy);


    /**
    * @brief Performs a bitwise OR on the values of Vx and Vy, then stores the result in Vx
    * @param vx number of the register (0x0-0xf for v0-vf)
    * @param vy number of the register (0x0-0xf for v0-vf)
    */
    void chip_or(uint8_t vx, uint8_t vy);

    /**
    * @brief Performs a bitwise XOR on the values of Vx and Vy, then stores the result in Vx
    * @param vx number of the register (0x0-0xf for v0-vf)
    * @param vy number of the register (0x0-0xf for v0-vf)
    */
    void chip_xor(uint8_t vx, uint8_t vy);


    /**
     * @brief The interpreter puts the value kk into register Vx.
     * @param vx number of the register (0x0-0xf for v0-vf)
     * @param byte 8-bit value (0x00-0xff)
     */
    void load_byte(uint8_t vx, uint8_t byte);

    /**
     * @brief Stores the value of register Vy in register Vx.
     * @param vx number of the register (0x0-0xf for v0-vf)
     * @param vy number of the register (0x0-0xf for v0-vf)
     */
    void load_register(uint8_t vx, uint8_t vy);

private:
    /*
    v0-vF: 16 8-bit registers

    PC: 16-bit register
    SP: 8-bit register

    DT: 16-bit delay timer register
    ST: 16-bit sound timer register
    */

    std::array<uint16_t, 16> v_registers;
    uint16_t pc = 0; // program counter
    uint8_t sp = 0; // stack pointer

    uint16_t dt = 0; // delay timer
    uint16_t st = 0; // sound timer

    // Internal call stack: stores return address from subroutine calls
    std::array<uint16_t, 16> stack;
};
