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
#include <vector>

#include "Processor.h"

/**
 * @brief Construct a new Processor::Processor object
 * 
 * Seeds the random number generator used by the RANDOM instruction
 */
Processor::Processor(
    std::function<uint8_t(uint16_t)> read_memory_callback,
    std::function<void(uint16_t, uint8_t)> write_memory_callback,
    std::function<bool(uint8_t, uint8_t, const std::vector<uint8_t> &)> write_pixels_to_screen_callback
) : read_memory {read_memory_callback},
    write_memory {write_memory_callback},
    write_pixels_to_screen {write_pixels_to_screen_callback} {
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
        decode_and_execute(instruction_to_run);        
    }
}

void Processor::decode_and_execute(uint16_t instruction_to_run) {
        switch (instruction_to_run & 0xf000) {
            // instruction can be identified by 4 most significant bits
            case 0x1000: {
                // JP addr
                // addr is bits 0-11
                uint16_t addr = instruction_to_run & 0xfff;
                jp(addr);
            } break;
            case 0x2000: {
                // CALL addr 
                // addr is bits 0-11
                uint16_t addr = instruction_to_run & 0xfff;
                call(addr);
            } break;
            case 0x3000: {
                // SE Vx, byte
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                // byte is bits 0-7
                uint8_t byte = instruction_to_run & 0xff;
                se_byte(vx, byte);
            } break;
            case 0x4000: {
                // SNE Vx, byte
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                // byte is bits 0-7
                uint8_t byte = instruction_to_run & 0xff;
                sne_byte(vx, byte);
            } break;
            case 0x5000: {
                // SE Vx, Vy
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                // vy is bits 4-7
                uint8_t vy = (instruction_to_run >> 4) & 0xf;
                se_register(vx, vy);
            } break;
            case 0x6000: {
                // LD Vx, byte
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                // byte is bits 0-7
                uint8_t byte = instruction_to_run & 0xff;
                load_byte(vx, byte);
            } break;
            case 0x7000: {
                // ADD Vx, byte
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                // byte is bits 0-7
                uint8_t byte = instruction_to_run & 0xff;
                add(vx, byte);
            } break;
            case 0x8000: {
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                // vy is bits 4-7
                uint8_t vy = (instruction_to_run >> 4) & 0xf;

                switch (instruction_to_run & 0xf) {
                    case 0x0: {
                        // LD Vx, Vy
                        load_register(vx, vy);
                    } break;
                    case 0x1: {
                        // OR Vx, Vy
                        chip_or(vx, vy);
                    } break;
                    case 0x2: {
                        // AND Vx, Vy
                        chip_and(vx, vy);
                    } break;
                    case 0x3: {
                        // XOR Vx, Vy
                        chip_xor(vx, vy);
                    } break;
                    case 0x4: {
                        // ADD Vx, Vy
                        add_registers(vx, vy);
                    } break;
                    case 0x5: {
                        // SUB Vx, Vy
                        sub(vx, vy);
                    } break;
                    case 0x6: {
                        // SHR Vx {, Vy}
                        shr(vx);
                    } break;
                    case 0x7: {
                        // SUBN Vx, Vy
                        subn(vx, vy);
                    } break;
                    case 0xE: {
                        // SHL Vx {, Vy}
                        shl(vx);
                    } break;
                }
            } break;
            case 0x9000: {
                // SNE Vx, Vy
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                // vy is bits 4-7
                uint8_t vy = (instruction_to_run >> 4) & 0xf;
                sne(vx, vy);
            } break;
            case 0xA000: {
                // LD I, addr
                // addr is bits 0-11
                uint16_t addr = instruction_to_run & 0xfff;
                load_addr(addr);
            } break;
            case 0xB000: {
                // JP V0, addr
                // addr is bits 0-11
                uint16_t addr = instruction_to_run & 0xfff;
                jump_register(addr);
            } break;
            case 0xC000: {
                // RND Vx, byte
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                // byte is bits 0-7
                uint16_t byte = instruction_to_run & 0xff;
                random(vx, byte);
            } break;
            case 0xD000: {
                // DRW Vx, Vy, nibble
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                // vy is bits 4-7
                uint8_t vy = (instruction_to_run >> 4) & 0xf;
                // nibble is bits 0-3
                uint8_t nibble = instruction_to_run & 0xf;
                display(vx, vy, nibble);
            } break;
            case 0xE000: {
                uint8_t id = instruction_to_run & 0xf;
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                if (id == 0xE) {
                    // SKP Vx
                    skip_pressed(vx);
                } else if (id == 0x1) {
                    // SKNP Vx
                    skip_not_pressed(vx);
                }
            } break;
            case 0xF000: {
                // vx is bits 8-11
                uint8_t vx = (instruction_to_run >> 8) & 0xf;
                switch (instruction_to_run & 0xff) {
                    case 0x07: {
                        // LD Vx, DT
                        load_register_from_dt(vx);
                    } break;
                    case 0x0A: {
                        // LD Vx, K
                        load_key(vx);
                    } break;
                    case 0x15: {
                        // LD DT, Vx
                        load_dt_from_register(vx);
                    } break;
                    case 0x18: {
                        // LD ST, Vx
                        load_st_from_register(vx);
                    } break;
                    case 0x1E: {
                        // ADD I, Vx
                        add_sum(vx);
                    } break;
                    case 0x29: {
                        // LD F, Vx
                        load_loc_of_sprite(vx);
                    } break;
                    case 0x33: {
                        // LD B, Vx
                        str_bcd_in_memory(vx);
                    } break;
                    case 0x55: {
                        // LD [I], Vx
                        str_registers_in_memory(vx);
                    } break;
                    case 0x65: {
                        // LD Vx, [I]
                        read_registers(vx);
                    }
                }
            }
            default: {
                std::cout << "Unimplemented instruction! " << instruction_to_run << '\n';
            }
        }
    }
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
