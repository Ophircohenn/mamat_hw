#!/bin/bash

# checking number of arguments
if [ "$#" != 1 ] ; then
echo "Wrong number of arguments" >&2
exit;
fi

#checking if the text file exists
if [ ! -f $1.txt ] ; then
echo "Course not found" >&2
exit;
fi

#checking if dir exist
if [ -d $1_stat ] ; then
rm -r $1_stat;
fi

mkdir $1_stat;

awk '{ print $2 }' $1.txt | tail -n +2 > grades.txt

gcc -g -Wall calc_statistics.c -o prog.exe

./prog.exe

mv course_statistics.txt $1_stat 
mv grades.txt $1_stat

cat $1_stat/course_statistics.txt

rm prog.exe
