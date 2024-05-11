#!/bin/bash

make

./tema3_neopt ../input/input

for i in {1..3}; do
	./compare out$i ../references/out$i 0.0001
	rm out$i
done
