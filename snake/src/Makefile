all: test file main test_ai1
.PHONY: all

test: game_test.o game.o file.o
	gcc -o test game_test.o game.o file.o

game_test.o: game_test.c
	gcc -c game_test.c

game.o: game.c game.h
	gcc -c game.c 

file.o: file.c file.h game.h
	gcc -c file.c

file: file_test.o file.o game.o
	gcc -o file file_test.o file.o game.o

file_test.o: file_test.c
	gcc -c file_test.c

main: main.o game.o view.o file.o ai1.o
	gcc -o main main.o game.o view.o file.o ai1.o

main.o: main.c
	gcc -c main.c

view.o: view.c view.h
	gcc -c view.c 

ai1.o: ai1.c ai1.h 
	gcc -c ai1.c 

test_ai1: test_ai1.o file.o ai1.o game.o
	gcc -o test_ai1 test_ai1.o file.o ai1.o game.o

test_ai1.o: test_ai1.c
	gcc -c test_ai1.c



clean:
	-rm *.o test file main test_ai1




