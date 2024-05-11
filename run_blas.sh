#!/bin/bash

make -f ./src/Makefile

for i in 1 .. 3; do
	./src/tema3_blas input/input

	./src/compare ./src/out$i ./references/out$i 0.0001
done