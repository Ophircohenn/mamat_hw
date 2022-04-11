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
    //printf("\n%d", &tmp_grade);
    int hist[101] = {0};
    int min = 100, max = 0, mid = 0,counter2 = 0, counter3 = 0;
    double avg=0;
   // printf("before while\n");
    //int x=fscanf(fp2, "%d", &tmp_grade);
    //printf("x = %d", &tmp_grade);
    while (fscanf(fp2, "%d", &tmp_grade) > 0)
    {
        //fscanf(fp2, "%s", tmp_grade);
        //fread(tmp_grade, sizeof(int), 1, fp2);

        printf("%d\n", tmp_grade);
        sum_of_grades += tmp_grade;
        counter++;
        hist[tmp_grade]++;
        min= (min > tmp_grade ? tmp_grade : min);
        max=(max < tmp_grade ? tmp_grade : max);
    }
   // printf("after while \n %d\n ",sum_of_grades);
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
    //printf("/n--%.2f--\n%d\n%d",pass,counter3,counter);
    fprintf(fp,"num of students = %d\n",counter);
    fprintf(fp,"avg = %.3f\n",avg);
    fprintf(fp,"the median is - %d\n",mid);
    fprintf(fp,"max grade = %d, min grade = %d\n",max,min);
    fprintf(fp,"pass rate = %.2f%%\n",pass);
    for (size_t i = 1; i < 101; i++)
       {
    	fprintf(fp,"%d ",hist[i]);
    	if(!(i%10))
    	{
    		fprintf(fp,"\n");
    	}
       }
    fclose(fp);
    fclose(fp2);


    return 0;
}
