#!/usr/bin/env bash
set -eu

# Set the source and build directories
SRC_DIR="src"
BUILD_DIR="build"
EXECUTABLE="p1"

# Create build directory if it doesn't exist
mkdir -p "$BUILD_DIR"

# Compile the C++ files
g++ -Wall -o "$BUILD_DIR/$EXECUTABLE" "$SRC_DIR/main.cc"

# Check if compilation was successful
if [ $? -eq 0 ]; then
  echo "Build successful! Executable created: $BUILD_DIR/$EXECUTABLE"
else
  echo "Build failed."
fi
