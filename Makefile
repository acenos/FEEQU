
LIBS= -lsfml-graphics -lsfml-window -lsfml-system
CC= g++
CFLAGS= -g
CCFLAGS= $(CFLAGS)
CXXFLAGS= $(CFLAGS)
OBJ= main.o game.o



all: game.exe

game.exe: main.o game.o
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) $(LIBS) -o game.exe

clean:
	rm -f $(OBJ) game.exe
