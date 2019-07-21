main: main.o game.o file.o view.o ai.o


main.o: main.c
	gcc -c main.c -o main.o
game.o: game.c
	gcc -c game.c -o game.o
file.o: file.c
	gcc -c file.c -o file.o
view.o: view.c
	gcc -c view.c -o view.o
ai.o: ai.c
	gcc -c ai.c -o ai.o
clean: 
	rm -rf *.o main game_test file_test ai_test
