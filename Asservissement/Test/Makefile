CC = gcc
CPFLAGS = -Wall -Wextra -fsanitize=address `pkg-config --cflags sdl2 SDL2_image SDL2_ttf` 
LDLIBS = `pkg-config --libs sdl2 SDL2_image SDL2_ttf` -lm


all: rot mv
	@echo "Make finish"

debugr: CPFLAGS+=-g
debugr: rot

debugm: CPFLAGS+=-g
debugm: mv


rot: asserv.c rotate/test_rotate.c
	$(CC) $^ $(CPFLAGS) $(LDLIBS) -o rot

mv: asserv.c move/test_move.c
	$(CC) $^ $(CPFLAGS) $(LDLIBS) -o mv

.PHONY:clean

clean:
	rm rot
	rm mv
