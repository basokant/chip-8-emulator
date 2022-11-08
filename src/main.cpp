#include <array>
#include <iostream>
#include <string>

#include "Processor.h"

int main() {
    Processor processor;
    // sequence of instructions to run
    // TODO: write in assembly
    std::array<uint8_t, 0x10000> instructions = {
        0x12, // LOAD 5 into A
        0x23, // LOAD 56
    };

    // CPU dump BEFORE running the instructions
    std::cout << processor.dump();
    // load the intsructions into memory
    processor.load_memory(instructions);
    processor.run();
    // CPU dump AFTER running the instructions
    std::cout << processor.dump();
    return 0;
}