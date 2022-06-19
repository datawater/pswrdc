PKGS=sdl2
CFLAGS_COMMON=-Wall -Wextra -std=c99 -pedantic
CFLAGS=$(CFLAGS_COMMON) `pkg-config --cflags $(PKGS)`
LIBS=`pkg-config --libs $(PKGS)` -lm

pswrdc: src/main.c
	$(CC) $(CFLAGS) -o out/main src/main.c $(LIBS)

run: out/main
	./out/main