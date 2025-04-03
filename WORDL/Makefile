# Variables
# File type
CXX = g++
# Compiler flags
CXXFLAGS = -Wall -g -MMD
# Target, i.e., executable
TARGET = WORDL
# Source:
SRC = main.cpp words_array.cpp classes/*.cpp
# Purpose
OBJ = $(SRC:.cpp=.o)
# Dependency files
DEPS = $(SRC:.cpp=.d)

# Compiler's objective
all: $(TARGET)

# Creation of the executable file
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule for building object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for including dependencies
-include $(DEPS)

# Cleans up after the process
clean:
	rm -f $(TARGET) $(OBJ) $(DEPS)

# Helper rules
help:
	@echo "Available targets:"
	@echo "  all       - Build the $(TARGET) executable"
	@echo "  clean     - Remove the generated files"
	@echo "  help      - Show this help message"

# Rules that should always run
.PHONY: all clean