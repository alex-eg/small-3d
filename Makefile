#
# Todo: learn how to write simple and effective makefiles
#

CC = clang
LIBS = -lGL -lglut -lSDL -lstdc++
CFLAGS = -Weverything -g -std=c++11

BINDIR=./build/

all: camera application event-process main

event-process: event.cpp
	$(CC) -c -o event.o event.cpp $(CFLAGS)

camera: camera.cpp
	$(CC) -c -o camera.o camera.cpp $(CFLAGS)

application: application.cpp
	$(CC) -c -o app.o application.cpp $(CFLAGS)

main: camera application event-process
	$(CC) -o app app.o camera.o teapot.o event.o $(LIBS) $(CFLAGS)

debug: 
	$(MAKE) CFLAGS += -g all
