CC = gcc
CFLAGS = -Wall -g
OBJECTS = main.o functions.o utility.o

all : main

main : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main -lm

%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean :
	rm -rf *.o pred_coeff.txt main 

.PHONY: all clean
