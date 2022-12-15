CC = gcc
CFLAGS = -std=gnu11 -Wall -g
#CFLAGS = -std=gnu11 -Wall -O3

#SOURCES = muunnin.c
#HEADERS = *.h


muunnin: lib/muunnin.o lib/main.o
	$(CC) $(CFLAGS) lib/main.o lib/muunnin.o -o $@ 

lib/main.o: main.c
	$(CC) $(CFLAGS) $^  -c -o $@

lib/muunnin.o: muunnin.c muunnin.h 
	$(CC) $(CFLAGS) muunnin.c -c -o $@ 

lib/muunnin.so: lib/muunnin.o
	$(CC) $(CFLAGS) lib/muunnin.o -shared -o $@ 

debug: muunnin.c main.c
	$(CC) $(CFLAGS) muunnin.c -c -g -o lib/muunnin_debug.o
	$(CC) $(CFLAGS) main.c lib/muunnin_debug.o -g -o muunnin_debug
#	$(CC) $(CFLAGS) lib/muunnin.o -shared -g -o lib/muunnin_debug.so


shared: lib/muunnin.so lib/main.o
	$(CC) $(CFLAGS) lib/main.o -O3 -o $@ 


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
	rm -f shared 
	rm -f lib/*.a
	rm -f lib/*.so
	rm -f ~/.local/bin/muunnin
