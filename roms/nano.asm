#include "chip8.asm"

ld v1, 0; x-coordinate
ld v2, 0; y-coordinate
ld v4, 0; characters on this line
ld v5, 12; max characters per line
loop:
    ld v3, k; wait for pressed key
    ld f, v3; load sprite of pressed key
    drw v1, v2, 5; draw sprite
    add v1, 5; increment x coordinate
    add v4, 1; increment number of characters on this line
    sne v4, v5; check if need to jump to new line
    call newline
    jp loop; otherwise continue writing

newline:
    ld v1, 0; reset x-coordinate
    add v2, 6; increment y-coordinate (next line)
    ld v4, 0; reset number of characters on this line
    ret