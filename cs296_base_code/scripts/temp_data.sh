#!/bin/bash
rm -rf data/data.csv
format=","
for k in {1..100}
do
	rm -rf temp.csv
	for i in {0..99}
	do
		j=$(( $i*100+$k ))
		head -$j ./data/lab05_g16_data.csv | tail -1 >> temp.csv
	done
	echo -n "$k," >> ./data/data.csv
	awk -F$format '{s+=$3} END {printf "%f,",s/NR}' temp.csv >> ./data/data.csv
	awk -F$format '{if(min==""){min=$3}; if($3<min){min=$3}} END {printf "%f,",min}' temp.csv >> ./data/data.csv
	awk -F$format '{if(max==""){max=$3}; if($3>max){max=$3}} END {printf "%f\n",max}' temp.csv >> ./data/data.csv
done
rm -rf temp.csv

