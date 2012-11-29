#
# Todo: learn how to write simple and effective makefiles
# ...Cmake?
#

CC = clang
LIBS = -lGL -lglut -lSDL -lstdc++
CFLAGS = -W -std=c++11

BINDIR=./build/
OBJ = event.o app.o camera.o teapot.o loader.o

all: camera application event-process loader main

loader:
	$(CC) -c -o loader.o wavefrontLoader.cpp $(CFLAGS)

event-process: event.cpp
	$(CC) -c -o event.o event.cpp $(CFLAGS)

camera: camera.cpp
	$(CC) -c -o camera.o camera.cpp $(CFLAGS)

application: application.cpp
	$(CC) -c -o app.o application.cpp $(CFLAGS)

main: camera application event-process
	$(CC) -o app $(OBJ) $(LIBS) $(CFLAGS)

debug: 
	$(MAKE) CFLAGS += -g all
