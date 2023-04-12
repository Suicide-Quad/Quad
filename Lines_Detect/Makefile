CC = gcc
CFLAGS = -Wall -Wextra `pkg-config --cflags sdl2 SDL2_image`
LDLIBS = `pkg-config --libs sdl2 SDL2_image` -lm

all: testa

debug: CFLAGS+=-g
debug: test

testa: CFLAGS+=-fsanitize=address
testa: test

test: binary.c Compute_Lines.c
	$(CC) $^ $(CFLAGS) $(LDLIBS) -o $@


.PHONY: clean

clean:
	rm -rf test
