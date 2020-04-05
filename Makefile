game: main.o gamestate.o bird.o pipe.o text.o
	gcc main.o gamestate.o bird.o pipe.o text.o -o game -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf

main.o: main.c main.h
	gcc -c main.c -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf

gamestate.o: gamestate.c gamestate.h
	gcc -c gamestate.c -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf

bird.o: bird.c bird.h
	gcc -c bird.c -lSDL2 -lSDL2main

pipe.o: pipe.c pipe.h
	gcc -c pipe.c -lSDL2 -lSDL2main

text.o: text.c text.h 
	gcc -c text.c -lSDL2 -lSDL2main -lSDL2_ttf -lSDL2_image
