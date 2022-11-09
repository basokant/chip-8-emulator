#include <array>
#include <iostream>
#include <string>

#include "Processor.h"

int main() {
    Processor processor;
    // sequence of test instructions to run
    std::array<uint8_t, 0x10000> instructions = {
        0x60, // ld v0, 0x1
        0x01,
        0x61, // ld v1, 0x2
        0x02,
        0x80, // add v0, v1
        0x14
    };

    // CPU dump BEFORE running the instructions
    std::cout << processor.dump();
    std::cout << "******************\n";
    std::cout << "EXECUTING PROGRAM\n";
    // load the intsructions into memory
    processor.load_memory(instructions);
    // run the instructions currently loaded in memory
    processor.run();
    std::cout << "******************\n";
    // CPU dump AFTER running the instructions
    std::cout << processor.dump();
    return 0;
}
