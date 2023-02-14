CC = gcc
CPFLAGS = -Wall -Wextra -fsanitize=address `pkg-config --cflags sdl2 SDL2_image SDL2_ttf` 
LDLIBS = `pkg-config --libs sdl2 SDL2_image SDL2_ttf` -lm

debugr: CPFLAGS+=-g
debugr: rot

debugm: CPFLAGS+=-g
debugm: mv

all: 

rot: asserv.c rotate/test_rotate.c
	$(CC) $^ $(CPFLAGS) $(LDLIBS) -o rot

mv: asserv.c move/test_move.c
	$(CC) $^ $(CPFLAGS) $(LDLIBS) -o mv

.PHONY:clean cleanr cleanm

clean:
	rm rot
	rm mv
cleanr:
	rm rot
cleanm:
	rm mv
