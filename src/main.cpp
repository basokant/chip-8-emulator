#include <array>
#include <iostream>
#include <string>

#include "Processor.h"

int main() {
    Processor processor;
    // sequence of test instructions to run
    std::array<uint8_t, 0x10000> instructions = {
        0x6011, // ld v0, 0x11
        0x6122, // ld v1, 0x22
        0x8014 // add v0, v1
    };

    // CPU dump BEFORE running the instructions
    std::cout << processor.dump();
    // load the intsructions into memory
    // processor.load_memory(instructions);
    // processor.run();
    // CPU dump AFTER running the instructions
    // std::cout << processor.dump();
    return 0;
}