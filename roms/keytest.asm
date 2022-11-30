#include "chip8.asm"

ld v2, 0; x-coordinate of sprite
ld v3, 0; y-coordinate of sprite
loop:
    ld v1, k; wait for keypress, load key into v1 register
    ld f, v1; load location of sprite of pressed key into I register
    cls; clear screen before drawing new number
    drw v2, v3, 0x5; sprite is 5 bytes tall
    jp loop