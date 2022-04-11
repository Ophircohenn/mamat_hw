#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int main(int argc, char* argv[]) {
    if (argc < 1) {
        fprintf(stderr, "Error\n");
        return 1;
    }
    FILE* fp;
    FILE* fp2;

    fp = fopen("course_statistics.txt", "w");
    fp2= fopen("grades.txt", "r");
    int counter = 0;
    double pass=0;
    int sum_of_grades = 0;
    int tmp_grade = 0;

    int hist[101] = {0};
    int min = 100, max = 0, mid = 0,counter2 = 0, counter3 = 0;
    double avg=0;

    while (fscanf(fp2, "%d", &tmp_grade) > 0)
    {
        sum_of_grades += tmp_grade;
        counter++;
        hist[tmp_grade]++;
        min= (min > tmp_grade ? tmp_grade : min);
        max=(max < tmp_grade ? tmp_grade : max);
    }

    avg = (double)sum_of_grades /counter;
    for (size_t i = 0; i < 101; i++)
    {
        counter2 += hist[i];
        if (counter2 >= (counter / 2))
        {
            mid=i;
        	break;
        }
    }
    for (size_t i = 55; i < 101; i++)
    {
        counter3 += hist[i];
    }
    pass = (double)(((double)(counter3*100))/ counter);
    fprintf(fp,"num of students = %d\n",counter);
    fprintf(fp,"avg = %.3f\n",avg);
    fprintf(fp,"the median is - %d\n",mid);
    fprintf(fp,"max grade = %d, min grade = %d\n",max,min);
    fprintf(fp,"pass rate = %.2f%%\n",pass);
    for (size_t i = 1; i < 101; i++)
       {
    	if(!(i%10))
    	{
    		fprintf(fp,"%d\n",hist[i]);
    	}
    	else
    	{
    		fprintf(fp,"%d ",hist[i]);
    	}
       }
    fclose(fp);
    fclose(fp2);


    return 0;
}
