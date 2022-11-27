ROMS := \
loop.rom \
fonttest.rom

CUSTOMASM_DIR := ../customasm

all: customasm $(ROMS)

# build the assembler
.PHONY: customasm
customasm:
	cargo build --release --manifest-path=$(CUSTOMASM_DIR)/Cargo.toml

.PHONY: clean
clean:
	rm *.bin

%.rom : %.asm chip8.asm
	../customasm/target/release/customasm $<
