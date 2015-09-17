
LIBS= -lsfml-graphics -lsfml-window -lsfml-system
CC= g++
all: game.exe

game.exe: main.o game.o
	$(CC) main.o game.o $(LIBS) -o game.exe

clean:
	rm -f main.o game.o game.exe
