CC=clang-9
PNAME=project
LDFLAGS=-O0 -g -Wall --std=c99 -Wno-initializer-overrides -DLinuxBuild -DDebugBuild -I./Kore/Include
LDLIBS=-lSDL2 -lGL -lGLEW -lm
SRCS=Kore/Source/Graphics/*.c \
	 Kore/Source/Math/*.c     \
	 Kore/Source/Memory/*.c   \
	 Kore/Source/System/*.c   \
	 Kore/Source/IO/*.c       \
	 Kore/Source/Loader/*.c

all:
	$(CC) $(LDFLAGS) $(LDLIBS) -o $(PNAME) main.c $(SRCS)