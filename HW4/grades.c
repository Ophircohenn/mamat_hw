#include <stdio.h>
#include <stdlib.h>
#include "grades.h"
#include <string.h>
#include "linked-list.h"

struct course_grade
{
	int grade;
	char* course_name;
};
struct grades
{
	struct list* student_list;
};

struct student
{
	char* name;
	int id;
	struct list* grades_of_student;
};

typedef struct course_grade* Course_Grade;
typedef struct student* Student;
typedef struct grades* Grades;

int student_clone(void* student,void** out);
void student_destroy(void* student);
void grades_destroy(Grades grades);
void course_grade_destroy (void* course_grade);
int course_grade_clone(void* course_grade, void** out);
int grades_add_student(struct grades *grades, const char *name, int id);

Grades grades_init()
{
	Grades my_grades=NULL;
	my_grades=malloc(sizeof(struct grades));
	my_grades->student_list=list_init(student_clone,student_destroy);
	return my_grades;
}


void grades_destroy(Grades grades)
{
	struct iterator* itr=list_begin(grades->student_list);
	Student s_student=list_get(itr);

	list_destroy(grades->student_list);
	//grades=NULL;
	free((void*)grades);
}


int grades_add_student(Grades grades, const char* name, int id)
{
	if(grades == NULL)
	{
		return 1;
	}
	struct iterator* itr=list_begin(grades->student_list);
	Student new_student=list_get(itr);
	while(new_student != NULL)
		{
			if(new_student->id==id)
			{
				return 1;
			}
			itr=list_next(itr);
			new_student=list_get(itr);
		}
	new_student=malloc(sizeof(struct student));
	new_student->id=id;
	new_student->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
		if(new_student->name == NULL)
		{
			printf("Error on Malloc");
					exit(0);
		}
	strcpy(new_student->name,name);
	new_student->grades_of_student=
			list_init(course_grade_clone,course_grade_destroy);
	list_push_back(grades->student_list,new_student);
	student_destroy((void*)new_student);

	return 0;
}



int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade)
{
	if((grades==NULL) || (grade<0) || (grade>100))
	{
		return 1;
	}
	struct iterator* itr=list_begin(grades->student_list);
	Student s_student=list_get(itr);
	while(s_student!=NULL)// if student exists
	{
		if(s_student->id==id)
		{
			break;
		}
		itr=list_next(itr);
		s_student=list_get(itr);
	}
	if(s_student==NULL)
	{
		return 1;
	}
	struct iterator* itr2 = list_begin(s_student->grades_of_student);
	Course_Grade course=list_get(itr2);

	while(course!=NULL)// if course exists
	{
		if(strcmp((course->course_name),name) == 0)//if equal
		{
			return 1;
		}
		itr2=list_next(itr2);
		course=list_get(itr2);
	}

	//if there is no course with same name
	course=malloc(sizeof(struct course_grade));
	course->grade=grade;
	course->course_name=(char*)malloc(sizeof(char)*(strlen(name)+1));
	if(course->course_name == NULL)
		{
			printf("Error on Malloc");
			exit(0);
		}
	strcpy(course->course_name,name);
	list_push_back(s_student->grades_of_student,(void*)course);
	course_grade_destroy((void*)course);

	return 0;

}




void student_destroy(void* student)
{
	Student tmp=student;
	list_destroy(tmp->grades_of_student);
	student=NULL;
	free(tmp->name);
	//free(student);
	free(tmp);
}
int student_clone(void* student, void** out)
{
	*out=malloc(sizeof(struct student));
	Student* tmp=(Student*)out;
	Student tmp2=student;
	Course_Grade o_head=NULL;
	struct iterator* itr;

	(*tmp)->id=tmp2->id;
	(*tmp)->name = (char*)malloc(sizeof(char)*strlen(tmp2->name)+1);
	if((*tmp)->name == NULL)
				{
					printf("Error on Malloc");
							exit(0);
				}
	strcpy((*tmp)->name,tmp2->name);
	itr=list_begin(tmp2->grades_of_student);
	o_head=list_get(itr);
	(*tmp)->grades_of_student=
			list_init(course_grade_clone,course_grade_destroy);
	while(o_head != NULL)
	{
		list_push_back((*tmp)->grades_of_student,(void*)o_head);
		itr=list_next(itr);
		o_head=list_get(itr);
	}
	return 0;
}


void course_grade_destroy (void* course_grade)
{
	Course_Grade tmp=course_grade;
	free(tmp->course_name);
	course_grade=NULL;
	//free(course_grade);
	free(tmp);
}
int course_grade_clone(void* course_grade, void** out)
{
	Course_Grade* tmp=(Course_Grade*)out;
	Course_Grade tmp2=course_grade;

	(*out) =malloc(sizeof(struct course_grade));
	if((*tmp) == NULL)
	{
		printf("Error on malloc");
				exit(0);
	}
	(*tmp)->grade = tmp2->grade;

	(*tmp)->course_name =
			(char*)malloc(sizeof(char)*(strlen(tmp2->course_name)+1));
		if((*tmp)->course_name == NULL)
			{
				printf("Error on Malloc");
						exit(0);
			}
	strcpy((*tmp)->course_name,tmp2->course_name);
	return 0;
}


float grades_calc_avg(struct grades *grades, int id, char **out)
{
	struct iterator* itr=NULL;
	struct iterator* itr2=NULL;

	if(grades==NULL)
		{
			out=NULL;
			return -1;
		}
	Student s_student=NULL;//selected student
	itr=list_begin(grades->student_list);
	s_student=list_get(itr);
	while(s_student != NULL)
	{
		if(s_student->id==id)
		{
			break;
		}
		itr=list_next(itr);
		s_student=list_get(itr);
	}
	if(s_student==NULL)
	{
		*out=NULL;
		return -1;
	}
	*out=(char*)malloc(sizeof(char)*(strlen(s_student->name)+1));
	if(*out== NULL)
	{
		printf("Error on Malloc");
				exit(0);
	}
	strcpy(*out,s_student->name);
	int counter=0;
	int sum=0;
	float avg=0;
	Course_Grade course=NULL;
	itr2=list_begin(s_student->grades_of_student);
	course=list_get(itr2);
	while(course != NULL)
	{
		counter++;
		sum += course->grade;
		itr2=list_next(itr2);
		course=list_get(itr2);
	}
	if(counter==0)
	{
		return 0;
	}
	else
	{
		avg= ((float)(sum))/counter;
	}
	return avg;
}


int grades_print_student(struct grades *grades, int id)
{
	struct iterator* itr=NULL;
	struct iterator* itr2=NULL;
	if(grades==NULL)
		{
			return -1;
		}
	Student s_student=NULL;//selected student
	itr=list_begin(grades->student_list);
	s_student=list_get(itr);
	while(s_student != NULL)
	{
		if(s_student->id==id)
		{
			break;
		}
		itr=list_next(itr);
		s_student=list_get(itr);
	}
	if(s_student==NULL)
	{
		return -1;
	}
	// we coutinue only if ID found
	Course_Grade course=NULL;

	itr2=list_begin(s_student->grades_of_student);
	course=list_get(itr2);
	printf("%s %d:",s_student->name,s_student->id);
	while(course!=NULL)
	{
		printf(" %s %d",course->course_name,course->grade);///!!!//
		itr2=list_next(itr2);
		course=list_get(itr2);
		if(course!=NULL)
		{
			printf(",");/// YAKKKKK
		}
	}

	printf("\n");
	return 0;

}
int grades_print_all(struct grades *grades)
{
	struct iterator* itr=NULL;
	if(grades==NULL)
	{
		return -1;
	}
	Student s_student=NULL;//selected student
	itr=list_begin(grades->student_list);
	s_student=list_get(itr);
	Course_Grade course=NULL;
	struct iterator* itr2=NULL;
	while(s_student != NULL)
		{
		itr2=list_begin(s_student->grades_of_student);
		course=list_get(itr2);
		printf("%s %d:",s_student->name,s_student->id);
		while(course!=NULL)
		{
			printf(" %s %d",course->course_name,course->grade);///!!!//
			itr2=list_next(itr2);
			course=list_get(itr2);
			if(course!=NULL)
			{
				printf(",");/// YAKKKKK
			}
		}

		printf("\n");
		itr=list_next(itr);
		s_student=list_get(itr);
		}
	return 0;
}


