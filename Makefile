CC=clang-9
PNAME=hexproject
LDFLAGS=-O0 -g -Wall --std=c99 -Wno-initializer-overrides -DLinuxBuild -DDebugBuild
LDLIBS=-lSDL2 -lGL -lGLEW -lm
SRCS=kore/graphics/*.c              \
	 kore/math/*.c                  \
	 kore/memory/*.c                \
	 kore/memory/datastructures/*.c \
	 kore/system/*.c                \
	 kore/io/*.c                    \
	 kore/loader/*.c                \
	 hexapod/world/*.c

all:
	$(CC) $(LDFLAGS) $(LDLIBS) -o $(PNAME) main.c $(SRCS)