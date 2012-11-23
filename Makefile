CC = clang
LIBS = -lSDL -lGL -lGLUT
CFLAGS = -Weverything

BINDIR=./build/

all: collada-viewer

collada-viewer:
	$(CC) -o viewer $(LIBS) $(CFLAGS) colladaViewer.cpp
