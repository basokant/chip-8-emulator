#include <iostream>
#include <SDL2/SDL.h>

#include "System.h"
#include "ProcessorException.h"

int main() {
    System emulator;
    try {
        emulator.run();
    } catch (ProcessorException &e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}