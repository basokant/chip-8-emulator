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

#ifndef PROCESSOR_H_INCLUDED
#define PROCESSOR_H_INCLUDED

#include <array>
#include <cstdint>

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
     * @brief Read the next instruction from memory pointed
     * to by the PC, and increment the PC
     * 
     * @return uint16_t 
     */
    uint16_t read_instruction_from_memory();
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
    * @brief The values of Vx and Vy are added together. 
    * If the result is greater than 8 bits (i.e., > 255,) VF is set to 1, otherwise 0. 
    * Only the lowest 8 bits of the result are kept, and stored in Vx.
    * @param vx number of the register (0x0-0xf for v0-vf)
    * @param vy number of the register (0x0-0xf for v0-vf)
    */
    void add_2(uint8_t vx, uint8_t vy);
    
    /**
    * @brief If Vx > Vy, then VF is set to 1, otherwise 0. 
    * Then Vy is subtracted from Vx, and the results stored in Vx.
    * @param vx number of the register (0x0-0xf for v0-vf)
    * @param vy number of the register (0x0-0xf for v0-vf)
    */
    void sub(uint8_t vx, uint8_t vy);
    
    /**
    * @brief If the least-significant bit of Vx is 1, then VF is set to 1, otherwise 0. 
    * Then Vx is divided by 2.
    * @param vx number of the register (0x0-0xf for v0-vf)
    */
    void shr(uint8_t vx);
    
    /**
    * @brief If Vy > Vx, then VF is set to 1, otherwise 0. 
    * Then Vx is subtracted from Vy, and the results stored in Vx.
    * @param vx number of the register (0x0-0xf for v0-vf)
    * @param vy number of the register (0x0-0xf for v0-vf)
    */
    void subn(uint8_t vx, uint8_t vy);

    /**
    * @brief If the most-significant bit of Vx is 1, then VF is set to 1, otherwise to 0. 
    * Then Vx is multiplied by 2.
    * @param vx number of the register (0x0-0xf for v0-vf)
    */
    void shl(uint8_t vx);

    /**
    * @brief The values of Vx and Vy are compared, 
    * and if they are not equal, the program counter is increased by 2.
    * @param vx number of the register (0x0-0xf for v0-vf)
    * @param vy number of the register (0x0-0xf for v0-vf)
    */
    void sne(uint8_t vx, uint8_t vy);

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
    void jump_register(uint8_t v0, uint16_t addr);

    
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
     */
    void load_key(uint8_t vx);


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

    /**
     * @brief The values of index and the value stored in the register Vx are added, and the results are stored in index.
     * 
     * @param index 8 byte integer value
     * @param vx number of the register (0x0-0xf for v0-vf)
     */
    void add_sum(uint8_t index, uint8_t vx);

    /**
     * @brief Set the value of index to the location of the sprite for the digit stored in Vx. 
     * Get the address of the first byte of any character by taking an offset from the start address.
     * 
     * @param Vx number of the register (0x0-0xf for v0-vf)  
     */
    void load_loc_of_sprite(uint8_t vx);

    /**
     * @brief Store BCD representation of Vx in memory locations I, I+1, and I+2
     * 
     * @param Vx number of the register (0x0-0xf for v0-vf)
     */
    void str_bcd_in_memory(uint8_t vx);

    /**
     * @brief Store registers V0 through Vx in memory starting at location I
     * 
     * @param i an 8 byte memory starting location integer value, 
     * @param  Vx number of the register (0x0-0xf for v0-vf)
     */
    void str_registers_in_memory(uint8_t i, uint8_t vx);
   
    /**
     * @brief Read registers V0 through Vx from memory starting at location I.
     * 
     * @param i an 8 byte memory starting location integer value, 
     * @param  Vx number of the register (0x0-0xf for v0-vf)
     */
    void read_registers(uint8_t vx, uint8_t i);

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

    uint8_t index = 0; //index 

    const uint16_t FONTSET_ADDRESS = 0x50; //Start location in memory of the font characters 

    // Array storing memory 
    // TODO: separate this into a memory class later
    // CHIP-8 has 4KB of addressable memory = 0x10000 bytes
    std::array<uint16_t, 0x10000> memory;

    bool is_running = true;
};

#endif
