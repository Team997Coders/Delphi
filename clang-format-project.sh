#!/bin/bash
echo "Formatting..."
find ./src -name '*.cpp' -o -name '*.h' | xargs clang-format --style=file -i
echo "Formatting done!"