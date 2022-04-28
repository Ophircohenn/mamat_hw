# Welcomre to Mamat, 044101
#
# This is the project's Makefile. It contains the instructions for compiling
# the projects C files, and then link the generated objects into an executable.
# This simple file will compile "main.c" to "main.o" and then link it (with C
# runtime library) to the executable "prog.exe".
#
# To compile, open the terminal in the folder that contains
# this file and run "make".
#
# To clean, open the terminal in the folder that contains
# this file and run "make clean".
#
# All eclipse projects in this machine are under /home/mamat/Documents/

CC     = gcc
CCLINK     = gcc
CFLAGS = -Wall -g -std=c99
OBJS   = main.o file0.o file1.o file2.o file3.o file4.o
EXEC = prog.exe
RM = *.exe *.o
#linking all files to main
prog.exe: $(OBJS)
	$(CCLINK) $(OBJS) -o prog.exe 
#we compile for each file the other relevant files
main.o: file0.h file1.h file2.h file3.h file4.h main.c
	$(CC) $(CFLAGS) -c main.c

file0.o: file0.h file3.h file0.c
	$(CC) $(CFLAGS) -c file0.c

file1.o: file1.h file2.h file3.h file1.c 
	$(CC) $(CFLAGS) -c file1.c

file2.o: file0.h file2.h file3.h file4.h file2.c 
	$(CC) $(CFLAGS) -c file2.c

file3.o: file0.h file2.h file3.h file3.c 
	$(CC) $(CFLAGS) -c file3.c
	
file4.o: file0.h file1.h file3.h file4.h file4.c
	$(CC) $(CFLAGS) -c file4.c

clean: #here we remove all
	rm -rf $(RM)
