#!/bin/bash

# Create build directory if not exists
mkdir -p build
cd build || exit 1

# Run CMake to generate build files
cmake ..

# Build the project using Make
make

# Run the executable
./slam

# Clean up (optional)
# make clean

cd ..
