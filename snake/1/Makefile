all: test file main
.PHONY: all

test: game_test.o game.o file.o ai.o
	gcc -o test game_test.o game.o file.o ai.o

file.o: file.c file.h game.h
	gcc -c file.c file.h

game_test.o: game_test.c
	gcc -c game_test.c

game.o: game.c game.h yyz.h
	gcc -c game.c game.h yyz.h

file: file_test.o file.o game.o
	gcc -o file file_test.o file.o game.o

file_test.o: file_test.c
	gcc -c file_test.c

ai.o: ai.c ai.h yyz.h
	gcc -c ai.c ai.h yyz.h



main: main.o game.o view.o file.o ai.o
	gcc -o main main.o game.o view.o file.o ai.o

main.o: main.c
	gcc -c main.c

view.o: view.c view.h
	gcc -c view.c view.h





	
clean:
	-rm *.o test file  main yyz.h.gch ai.h.gch file.h.gch view.h.gch game.h.gch




