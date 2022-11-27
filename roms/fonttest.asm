#include "chip8.asm"

ld v1, 0x0 ; sprite to load
ld v2, 0x0 ; x-coordinate
ld v3, 0x0 ; y-coordinate
loop:
    sne v1, 0x10 ; stop when we've gone through all the sprites [0x0..0x10)
    jp end
    ld f, v1 ; load the location of the sprite into memory
    drw v2, v3, 0x5 ; sprite is 5 bytes tall
    add v1, 1 ; go to next sprite
    add v2, 5 ; space sprites apart by 3
    jp loop

end:
    jp end ; loop infinitely