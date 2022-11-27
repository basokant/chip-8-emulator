ROMS := \
loop.ch8 \
fonttest.ch8

CUSTOMASM_DIR := ../customasm

all: customasm $(ROMS)

# build the assembler
.PHONY: customasm
customasm:
	cargo build --release --manifest-path=$(CUSTOMASM_DIR)/Cargo.toml

.PHONY: clean
clean:
	rm *.ch8

%.ch8 : %.asm chip8.asm
	../customasm/target/release/customasm $< -o $@
