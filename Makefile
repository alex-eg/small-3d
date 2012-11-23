CC = clang
LIBS = -lGL -lglut -lSDL
CFLAGS = -Weverything

BINDIR=./build/

all: collada-viewer

collada-viewer:
	$(CC) -o viewer colladaViewer.cpp $(LIBS) $(CFLAGS)

debug: 
	$(MAKE) CFLAGS += -ggdb all