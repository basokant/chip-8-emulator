CXX = g++
WARNINGS = -Wfatal-errors -Wall -Wextra -Wpedantic -Wconversion -Wshadow
CXX_FLAGS = -g -std=c++17

# Final binary
BIN = main

# Put all auto generated stuff to this build dir.
BUILD_DIR = build

# List of all .cpp source files.
SRC = $(wildcard src/*.cpp)
# All .o files go to build dir.
OBJ = $(SRC:src/%.cpp=$(BUILD_DIR)/%.o)
# Gcc/Clang will create these .d files containing dependencies.
DEP = $(OBJ:%.o=%.d)
# Shows where to find the header files
INCLUDE = -Iinclude
# Libraries to link
LIBRARY = 
LINKER = 

# Target of the binary - depends on all .o files.
$(BIN) : $(OBJ)
    # Create build directories - same structure as sources.
	mkdir -p $(BUILD_DIR)
    # Just link all the object files.
	$(CXX) $(CXX_FLAGS) $^ $(LIBRARY) $(LINKER) -o $@

# Include all .d files
-include $(DEP)

# Build target for every single object file.
# The potential dependency on header files is covered
# by calling `-include $(DEP)`.
$(BUILD_DIR)/%.o : src/%.cpp
	mkdir -p $(BUILD_DIR)
    # The -MMD flags additionaly creates a .d file with
    # the same name as the .o file.
	$(CXX) $(CXX_FLAGS) $(INCLUDE) -MMD -c $< -o $@

.PHONY : clean
clean :
    # This should remove all generated files.
	rm -rf $(BUILD_DIR)