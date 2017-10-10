#Author: Giang Vu
#Course: CS170
#Date: 3/23/2017
#To run, put this file together with lexer.h, and lexer.c
#in the same directory. Run "make". Then the executable
#is "scheme," which just takes a line of input and
#breaks it up into tokens.

scheme: interpreter.o parser.o lexer.o list.o list_func.o
	gcc -o scheme interpreter.o parser.o lexer.o list.o list_func.o

interpreter.o: interpreter.c
	gcc -c interpreter.c

parser.o: parser.c
	gcc -c parser.c

lexer.o: lexer.c
	gcc -c lexer.c

list.o: list.c
	gcc -c list.c

list_func.o: list_func.c
	gcc -c list_func.c

clean:
	rm -f *~ *.o *.a scheme

#^^^^^^This space must be a TAB!!.

