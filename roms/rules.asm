#bankdef rombank
{
    #addr 0x200
    #outp 0
}

#ruledef
{
    sys {addr: u12} => 0x0 @ addr
    ret => 0x00ee
    jp {addr: u12} => 0x1 @ addr
    call {addr: u12} => 0x2 @ addr
    se v{x: u4}, {byte: u8}  => 0x3 @ x @ byte
    sne v{x: u4}, {byte: u8} => 0x4 @ x @ byte
    se v{x: u4}, v{y: u4} => 0x5 @ x @ y @ 0x0
    ld v{x: u4}, {byte: u8} => 0x6 @ x @ byte
    add v{x: u4}, {byte: u8} => 0x7 @ x @ byte
    ld v{x: u4}, v{y: u4} => 0x8 @ x @ y @ 0x0
    or v{x: u4}, v{y: u4} => 0x8 @ x @ y @ 0x1
    and v{x: u4}, v{y: u4} => 0x8 @ x @ y @ 0x2
    xor v{x: u4}, v{y: u4} => 0x8 @ x @ y @ 0x3
    add v{x: u4}, v{y: u4} => 0x8 @ x @ y @ 0x4
    sub v{x: u4}, v{y: u4} => 0x8 @ x @ y @ 0x5
    shr v{x: u4}, v{y: u4} => 0x8 @ x @ y @ 0x6
    subn v{x: u4}, v{y: u4} => 0x8 @ x @ y @ 0x7
    shl v{x: u4}, v{y: u4} => 0x8 @ x @ y @ 0xe
    sne v{x: u4}, v{y: u4} => 0x9 @ x @ y @ 0x0
    ld i, {addr: u12} => 0xa @ addr
    jp v0, {addr: u12} => 0xb @ addr
    rnd v{x: u4}, {byte: u8} => 0xc @ x @ byte
    drw v{x: u4}, v{y: u4}, {n: u4} => 0xd @ x @ y @ n
    skp v{x: u4} => 0xe @ x @ 0x9e
    sknp v{x: u4} => 0xe @ x @ 0xa1
    ld v{x: u4}, dt => 0xf @ x @ 0x07
    ld v{x: u4}, k => 0xf @ x @ 0x0a
    ld dt, v{x: u4} => 0xf @ x @ 0x15
    ld st, v{x: u4} => 0xf @ x @ 0x18
    add i, v{x: u4} => 0xf @ x @ 0x1e
    ld f, v{x: u4} => 0xf @ x @ 0x29
    ld b, v{x: u4} => 0xf @ x @ 0x33
    ld [i], v{x: u4} => 0xf @ x @ 0x55
    ld v{x: u4}, [i] => 0xf @ x @ 0x65
}