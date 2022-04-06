#!/bin/bash


NAME1=Netanyahu
NAME2=Bennett
ADDERESS=https://www.ynetnews.com/category/3082
TARGET_ADDERESS=https://www.ynetnews.com/article/
TARGET_FILE=3082
RESULTS_FILE=results.csv

wget  $ADDERESS -q

grep -o "$TARGET_ADDERESS[0-9A-Za-z]\+" $TARGET_FILE | sort |uniq > tmp.txt

echo > $RESULTS_FILE

cat tmp.txt | wc -l > $RESULTS_FILE


while read -r line;
	do
		wget $line -q -O tmp2  
		COUNT1=$(grep -o "$NAME1" tmp2 | wc -w) 
		COUNT2=$(grep -o "$NAME2" tmp2 | wc -w) 
		
		if [ $COUNT1 -eq 0 -a $COUNT2 -eq 0 ]
			then
				echo "$line,-" >> $RESULTS_FILE
		else
			echo "$line,$NAME1,$COUNT1,$NAME2,$COUNT2" >> $RESULTS_FILE
		fi
	done < tmp.txt
	
rm tmp2
rm tmp.txt
rm $TARGET_FILE
	


