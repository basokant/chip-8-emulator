# CHIP OFF THE BLOCK
A CHIP-8 emulator written in C++.

## Build

### Dependencies
* SDL2
* SDL2-mixer

The default SDL2 include path is under `/usr/include` on Linux. The proper lib path is also included by default.
If yours differs, add the paths to a `config.mk` file in the root directory as follows:

```makefile
# in /config.mk
SDL_INCLUDE_DIR := <your_path_here>
SDL_LIB_DIR := <your_path_here>
```

Using a UNIX environment, run `make` in the root directory to build the executable. Then, run `./chip8 <path_to_rom_file>` to run a specified .ch8 file.

* run `make clean` to clean up the intermediate build files in the build directory `build/`.

## Configuration

Keyboard mapping and emulation speed can be controlled from `chip8.config.json`.

```json
{
    "custom_keymap" : {
        <SDL_key_name>: <chip8_key>
    },
    "emulation_speed" : 1.0, // factor: 2.0 runs twice as fast
    "screen_width": 960 // screen height is half the screen width
}
```

The SDL key names can be found [here](https://wiki.libsdl.org/SDL2/SDL_Keycode) under "Key Name".

There are 16 CHIP-8 keys to map: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15

## Controls

The default key mapping is as follows (to match the original hardware):

Keyboard
|||||
|---|---|---|---|
|1|2|3|4|
|Q|W|E|R|
|A|S|D|F|
|Z|X|C|V|

CHIP-8 Mapping
|||||
|---|---|---|---|
|1|2|3|C
|4|5|6|D|
|7|8|9|E|
|A|0|B|F|

Note: A-F are referenced by their hex values (e.g. 10 = A, 11 = B, etc.)


