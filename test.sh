#!/bin/bash

set -x

if [ "$#" -ne 1 ] ; then
	echo "$0 < run | clean >"
	exit -1
fi

if [ "$1" == "run" ] ; then
	make main
	make main_cpp11_stl
	./main > output
	./main_cpp11_stl > output_cpp11_stl
	diff output output_cpp11_stl
fi

if [ "$1" == "clean" ] ; then
	rm output output_cpp11_stl
	make clean
fi
