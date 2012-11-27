#
# Todo: learn how to write simple and effective makefiles
#
CC = clang
LIBS = -lGL -lglut -lSDL
CFLAGS = -Weverything -g

BINDIR=./build/

all: camera collada-viewer main

camera: camera.cpp
	$(CC) -c -o camera.o camera.cpp $(CFLAGS)

collada-viewer:
	$(CC) -c -o viewer.o colladaViewer.cpp $(CFLAGS)

main: camera collada-viewer
	$(CC) -o viewer viewer.o camera.o teapot.o $(LIBS) $(CFLAGS)

debug: 
	$(MAKE) CFLAGS += -ggdb all
