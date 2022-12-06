CC = gcc
CFLAGS = -std=gnu11 -Wall

#SOURCES = muunnin.c
#HEADERS = *.h


muunnin: lib/muunnin.o lib/main.o
	$(CC) $(CFLAGS) lib/main.o lib/muunnin.o -O3 -o muunnin

lib/main.o: main.c
	$(CC) $(CFLAGS) main.c -g -c -o lib/main.o

lib/muunnin.o: muunnin.c muunnin.h
	$(CC) $(CFLAGS) muunnin.c -c -O3 -o lib/muunnin.o

lib/muunnin.so: lib/muunnin.o
	$(CC) $(CFLAGS) lib/muunnin.o -shared -O3 -o lib/muunnin.so

debug:
	$(CC) $(CFLAGS) muunnin.c -c -g -o lib/muunnin_debug.o
	$(CC) $(CFLAGS) main.c lib/muunnin.o -g -o muunnin_debug
#	$(CC) $(CFLAGS) lib/muunnin.o -shared -g -o lib/muunnin_debug.so


test: lib/muunnin.so lib/main.o
	$(CC) $(CFLAGS) lib/main.o -O3 -o test


run:
	make
	./muunnin

debug_run:
	make debugl
	valgrind --tool=memcheck --leak-check=full ./muunnin_debug 10

install: muunnin
	ln -sf $(shell pwd)/muunnin ~/.local/bin/

clean:
	rm -f muunnin
	rm -f muunnin_debug
	rm -f test
	rm -f lib/*.a
	rm -f lib/*.so
	rm -f ~/.local/bin/muunnin
