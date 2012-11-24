#
# Todo: learn how to write simple and effective makefiles
#
CC = clang
LIBS = -lGL -lglut -lSDL
CFLAGS = -Weverything

BINDIR=./build/

all: camera collada-viewer main

camera: camera.cpp
	$(CC) -c -o camera.o camera.cpp $(LIBS) $(CFLAGS)

collada-viewer:
	$(CC) -c -o viewer.o colladaViewer.cpp $(LIBS) $(CFLAGS)

main: camera collada-viewer
	$(CC) -o viewer viewer.o camera.o $(LIBS) $(CFLAGS)

debug: 
	$(MAKE) CFLAGS += -ggdb all