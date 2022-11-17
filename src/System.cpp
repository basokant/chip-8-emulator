#include "System.h"

System::System()
    : processor {
        // read memory callback: anonymous function that forwards to memory.read_memory
        [this](uint16_t addr) { return this->memory.read_memory(addr); },
        // write memory callback: anonymous function that forwards to memory.write_memory
        [this](uint16_t addr, uint8_t byte) { return this->memory.write_memory(addr, byte); }
    }
{}