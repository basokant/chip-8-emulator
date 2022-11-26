# Final binary
BIN = chip8

CXX = g++
WARNINGS := -Wfatal-errors -Wall -Wextra -Wpedantic -Wconversion -Wshadow
CXXFLAGS := -g -std=c++17
CPPFLAGS :=

# system specific configurations (e.g. file include paths)
include config.mk
# specify defaults if not specified in config
SDL_INCLUDE_DIR ?= /usr/include/SDL2
SDL_LIB_DIR ?=

# Our object files
OBJS = \
src/main.o \
src/instructions.o \
src/Memory.o \
src/Processor.o \
src/System.o \
src/Display.o \
src/SDLException.o

# Libraries to link
LIBS = -lSDL2

CPPFLAGS += $(addprefix -I, \
	$(IMGUI_DIR) \
	$(IMGUI_DIR)/backends \
	include \
	$(SDL_INCLUDE_DIR) \
)

LD_FLAGS = -L$(SDL_LIB_DIR)



# Target of the binary - depends on all .o files.
$(BIN) : $(OBJS)
    # Just link all the object files.
	$(CXX) $(LD_FLAGS) `sdl2-config --cflags` $(CXXFLAGS) `sdl2-config --libs` $^ $(LIBS) -o $@

# Include all .d files


# Rule for building object files from C++ source
%.o: %.cpp
    # The -MMD flags additionaly creates a .d file with
    # the same name as the .o file.
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -MMD -c $< -o $@

# generated dependencies
DEPS = $(OBJS:%.o=%.d)

# Remove object files and generated dependencies
.PHONY: clean
clean:
	rm -rf $(OBJS) $(DEPS)

-include $(DEPS)