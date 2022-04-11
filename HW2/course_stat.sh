#!/bin/bash


if [ "$#" != 1 ] ; then
echo "Wrong number of arguments" > our_out1.txt;
#echo "Wrong number of arguments" > 2;
exit;
fi

if [ ! -f $1.txt ] ; then
echo "Course not found" > our_out2.txt;
#echo "Course not found" > 2;
exit;
fi

if [ -d $1_stat ] ; then
rm -r $1_stat;
fi

mkdir $1_stat;

awk '{ print $2 }' $1.txt | tail -n +2 > grades.txt

gcc -g -Wall course_statistics.c -o prog.exe

./prog.exe

mv course_statistics.txt $1_stat 
mv grades.txt $1_stat

cat $1_stat/course_statistics.txt

rm prog.exe
