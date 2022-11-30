# chip-8-emulator
A CHIP-8 emulator written in C++.

## Build

### Dependencies
* SDL2

The default SDL2 include path is under `/usr/include` on Linux. The lib path is also searched by default.
If yours differs, add the paths to a `config.mk` file in the root directory as follows:

```makefile
# in /config.mk
SDL_INCLUDE_DIR := <your_path_here>
SDL_LIB_DIR := <your_path_here>
```

Using a UNIX environment, run `make` in the root directory to build the executable. Then, run `./chip8` to run the hard-coded test ROM.

* run `make clean` to clean up the intermediate build files in the build directory `build/`.

## Expected Output
The emulator runs the following CHIP8 binary ROM stored in the array `instructions` in the `main.cpp` file.
```asm
ld v0, 0x1
ld v1, 0x2
add v0, v1
```
The value 1 is loaded into register v0; the value 2 is loaded into register v1; the sum of v0 and v1 is stored in v0.

The expected output should demonstrate that v0 contains the value 3 (1 + 2) and v1 contains the value 2.

The PC register will have incremented to 6 because it has run 6 instructions (from 0x0000 to 0x0005).

## Notes from the Professor
* We used GitHub instead of BitBucket for familiarity with the team: we recieved permission from the professor to use Github.
