CXX = g++
WARNINGS = -Wfatal-errors -Wall -Wextra -Wpedantic -Wconversion -Wshadow
CXX_FLAGS = -g -std=c++17

# Put all auto generated stuff to this build dir.
BUILD_DIR = build

# All .o files go to build dir.
OBJ = $(CPP:src/%.cpp=$(BUILD_DIR)/%.o)
# Gcc/Clang will create these .d files containing dependencies.
DEP = $(OBJ:%.o=%.d)
# Shows where to find the header files
INCLUDE =
# Libraries to link
LIBRARY = 
LINKER = 

all : main

main : $(BUILD_DIR)/main.o
	mkdir -p $(BUILD_DIR)
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
	rm -rf $(BUILD_DIR)