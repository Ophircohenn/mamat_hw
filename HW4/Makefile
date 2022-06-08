
CC     = gcc
CCLINK     = gcc
CFLAGS = -Wall -g -std=c99
RM = *.o libgrades.so

#we compile for each file the other relevant files
libgrades.so: grades.o
	$(CCLINK) -shared grades.o -o libgrades.so -llinked-list -L.

grades.o: grades.c grades.h linked-list.h
	$(CC) -c -g -fpic grades.c
	
clean: #here we remove all
	rm -rf $(RM)
