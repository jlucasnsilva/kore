CC=clang-9
LDFLAGS=-O0 -g -Wall --std=c99 -Wno-initializer-overrides -DLinuxBuild
LDLIBS=-lSDL2 -lGL -lGLEW -lm
SRCS=kore/*.c kore/memory/*.c

all:
	$(CC) $(LDFLAGS) $(LDLIBS) -o game main.c $(SRCS)