//file4.c
#include <stdio.h>
#include <stdlib.h>
#include "file4.h"
#include "file0.h"
#include "file1.h"
#include "file3.h"
int file4_function(){
	printf("This is file4_function()\n");
	file0_function();
	file1_function();
	file3_function();
	return 0;
}
