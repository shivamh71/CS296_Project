#!/bin/bash

make
for i in {1..100}
do
	for j in {1..100}
	do
		./bin/cs296_base_16 $i > ./data/out-$i-$j.txt
	done
done

