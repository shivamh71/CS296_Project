#!/bin/bash

make
rm -rf ./data/lab05_g16_data.csv
for i in {1..100}
do
	for j in {1..100}
	do
		echo -n $i >> ./data/lab05_g16_data.csv
		while read line
		do
			echo -n "," >> ./data/lab05_g16_data.csv
			new_line=`echo ${line##* }`
			echo -n "$new_line" | sed 's/m//' | sed 's/s//' >> ./data/lab05_g16_data.csv
		done < ./data/out-$j-$i.txt
		printf "\n" >> ./data/lab05_g16_data.csv
	done
done

