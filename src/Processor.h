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


    /**
     * @brief Return from a subroutine.
     * 
     * The interpreter sets the program counter to the address at the top of the stack, 
     * then subtracts 1 from the stack pointer.
     *
     */
    void ret();

    /**
     * @brief Stores the address in register i.
     * 
     * @param i number of the register (0x-0xf for v0-vf)
     * @param addr A 16-bit address in memory
     */
    void load_addr(uint8_t i, uint16_t addr);


    /**
     * @brief The program jumps by setting the program counter to an address (addr plus the value of v0)
     * 
     * @param v0 number of the register (0x0-0xf for v0-vf)
     * @param addr A 16-bit address in memory
     */
    void jump(uint8_t v0, uint16_t addr);

    
    /**
     * @brief Generate a random number from 0 to 255, which is then ANDed with a value byte, and stored in a register vx.
     * 
     * @param vx number of the register (0x0-0xf for v0-vf)
     * @param byte 8-bit value (0x00-0xff)
     */
    void random(uint8_t vx, uint8_t byte);


    /**
     * @brief Display n-byte sprite starting at memory location I at (vx, vy), set VF = collision.
     * 
     * @param vx number of the register (0x0-0xf for v0-vf)
     * @param vy number of the register (0x0-0xf for v0-vf)
     * @param nibble 4-bit value (0x0-0xf)
     */
    void display(uint8_t vx, uint8_t vy, uint8_t nibble);

    
    /**
     * @brief Skip next instruction if key with the value of vx is pressed.
     * 
     * @param vx number of the register (0x0-0xf for v0-vf)
     */
    void skip_pressed(uint8_t vx);


    /**
     * @brief Skip next instruction if key with teh value of vx is NOT pressed.
     * 
     * @param vx number of the register (0x0-0xf for v0-vf)
     */
    void skip_not_pressed(uint8_t vx);


    /**
     * @brief Set register vx to the value of the delay timer.
     * 
     * @param vx number of the register (0x0-0xf for v0-vf)
     */
    void load_register_from_dt(uint8_t vx);


    /**
     * @brief Wait for a key press, store the value of the key in register vx.
     * 
     * @param vx number of the register (0x0-0xf for v0-vf)
     * @param key value of the key (0x0-0xf)
     */
    void load_key(uint8_t vx, uint16_t key);


    /**
     * @brief Set delay timer to the value of register vx
     * 
     * @param vx number of the register (0x0-0xf for v0-vf)
     */
    void load_dt_from_register(uint8_t vx);


    /**
     * @brief Set the sound timer to the value of register vx
     * 
     * @param vx number of the register (0x0-0xf for v0-vf)
     */
    void load_st_from_register(uint8_t vx);

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
