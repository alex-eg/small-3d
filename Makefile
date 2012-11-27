#
# Todo: learn how to write simple and effective makefiles
#

CC = clang
LIBS = -lGL -lglut -lSDL -lstdc++
CFLAGS = -Weverything -g -std=c++11

BINDIR=./build/

all: camera collada-viewer event-process main

event-process: events.cpp
	$(CC) -c -o events.o events.cpp $(CFLAGS)

camera: camera.cpp
	$(CC) -c -o camera.o camera.cpp $(CFLAGS)

application: application.cpp
	$(CC) -c -o app.o application.cpp $(CFLAGS)

main: camera collada-viewer
	$(CC) -o app app.o camera.o teapot.o events.o $(LIBS) $(CFLAGS)

debug: 
	$(MAKE) CFLAGS += -g all
