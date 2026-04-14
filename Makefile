# Compiler and flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I src/core
# -std sets standard version of c++
# -Wall and -Wextra enables warnings
#  -I src tells the compiler to look into src/ when resolving #include paths

# Directories
ROOT_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
SRC_DIR := $(ROOT_DIR)/src
BIN_DIR := $(ROOT_DIR)/bin
 
# Targets
RENDERER := $(BIN_DIR)/renderer
 
# Default target — built when you run 'make' with no arguments or 'make all'
all: $(RENDERER)
 
# Rule to build the renderer
$(RENDERER): $(SRC_DIR)/tracer/renderer.cpp $(SRC_DIR)/core/vec3.h $(SRC_DIR)/core/color.h
	mkdir -p $(ROOT_DIR)/bin
	$(CXX) $(CXXFLAGS) $(SRC_DIR)/tracer/renderer.cpp -o $(RENDERER)
 
# Instruction to the command 'make clean'
clean: 
	rm -f $(BIN_DIR)/*
