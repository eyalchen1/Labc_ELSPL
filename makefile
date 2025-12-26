all : link

link: compile
	gcc -g -m32 -Wall -o mypipe mypipe.o

compile:clean mypipe.c

	gcc -g -m32 -Wall -c -o mypipe.o mypipe.c

clean:
	rm -f *.o mypipe