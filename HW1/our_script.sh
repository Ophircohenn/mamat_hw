#!/bin/bash


wget  https://www.ynetnews.com/category/3082 -q

grep -o "https://www.ynetnews.com/article/........." 3082 | sort |uniq > tmp.txt

echo > results.csv

cat tmp.txt | wc -l > results.csv


while read -r line;
	do
		wget $line -q -O tmp2  
		COUNT1=$(grep -o "Netanyahu" tmp2 | wc -w) 
		COUNT2=$(grep -o "Bennett" tmp2 | wc -w) 
		
		if [ $COUNT1 -eq 0 -a $COUNT2 -eq 0 ]
			then
				echo "$line,-" >> results.csv
		else
			echo "$line,Netanyahu,$COUNT1,Bennett,$COUNT2" >> results.csv
		fi
	done < tmp.txt
	
rm tmp2
rm tmp.txt
rm 3082
	


