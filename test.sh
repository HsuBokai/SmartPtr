#!/bin/bash

set -v

make main
make main_cpp11_stl
./main > output
./main_cpp11_stl > output_cpp11_stl
diff output output_cpp11_stl
rm output output_cpp11_stl
make clean
