#!/bin/bash

grep -o "https://www.ynetnews.com/article/........." 3082 | sort |uniq > tmp.txt

echo > results.csv

cat tmp.txt | wc -l > results.csv


while read -r line;
	do
		echo "$line" >> results.csv
	done < tmp.txt