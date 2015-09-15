
all: hw1

hw1: hw1.c
	gccx -o hw1 hw1.c

clean: 
	rm -f *.o hw1
