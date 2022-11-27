ROMS := \
loop.rom

CUSTOMASM_DIR := ../customasm

all: customasm $(ROMS)

# build the assembler
.PHONY: customasm
customasm:
	cargo build --manifest-path=$(CUSTOMASM_DIR)/Cargo.toml

%.rom : %.asm rules.asm
	../customasm/target/release/customasm $<