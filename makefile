all: clean link
link: compile 
	gcc -g -m32 -Wall -o myshell myshell.o
	gcc -g -m32 -Wall -o mypipeline mypipeline.o

compile: myshell.c mypipeline.c
	gcc -m32 -g -Wall -c -o myshell.o myshell.c
	gcc -m32 -g -Wall -c -o mypipeline.o mypipeline.c

myshell.o: 
	gcc -m32 -g -Wall -c -o myshell.o myshell.c

mypipeline.o:
	gcc -m32 -g -Wall -c -o mypipeline.o mypipeline.c

clean:
	rm -f *.o myshell mypipeline
