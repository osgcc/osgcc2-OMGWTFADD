CFLAGS = -I/usr/include/SDL
CC = g++
CLINK = -lGL -lSDL -lSDL_net -lSDL_mixer -lSDL_image -lglut -lGLU

all: audio.cpp breakout.cpp components.cpp engine.cpp game.cpp main.cpp tetris.cpp
	$(CC) audio.cpp -c $(CFLAGS)
	$(CC) breakout.cpp -c $(CFLAGS)
	$(CC) components.cpp -c $(CFLAGS)
	$(CC) engine.cpp -c $(CFLAGS)
	$(CC) game.cpp -c $(CFLAGS)
	$(CC) main.cpp -c $(CFLAGS)
	$(CC) tetris.cpp -c $(CFLAGS)
	$(CC) -o ../omgwtfadd audio.o breakout.o components.o engine.o game.o main.o tetris.o $(CLINK)

clean:
	rm *.o
