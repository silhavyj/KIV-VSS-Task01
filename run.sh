#!/bin/bash

rm -rf build || true

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && make -C build
if [ $? -eq 0 ]; then
    ./build/src/kivvss01 $1 $2 $3
else
    echo "ERROR: Failed to compile and build the application";
fi