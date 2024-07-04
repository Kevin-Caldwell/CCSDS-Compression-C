#!/bin/bash

BUILD_DIR="build"

if [ -d "$BUILD_DIR" ]; then
    echo "Build directory already exists. Cleaning up..."
    rm -rf "$BUILD_DIR"
fi

mkdir "$BUILD_DIR"

cd "$BUILD_DIR" || exit

cmake ..
make

echo "Build process complete."