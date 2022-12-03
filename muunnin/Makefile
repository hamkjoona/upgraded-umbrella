CC = gcc

CFLAGS = -std=gnu11 -Wall

SOURCES = muunnin.c

HEADERS = *.h


#muunnin: main.c muunnin.c
#	$(CC) $(CFLAGS) main.c -O3 -c -o lib/main.o
#	$(CC) $(CFLAGS) $(SOURCES) -O3 -c -o lib/muunnin.o
#	$(CC) $(CFLAGS) lib/main.o lib/muunnin.o -O3 -o muunnin


muunnin: lib/muunnin.o lib/main.o
	$(CC) $(CFLAGS) lib/main.o lib/muunnin.o -O3 -o muunnin

lib/muunnin.o: muunnin.c muunnin.h
	$(CC) $(CFLAGS) muunnin.c -c -O3 -o lib/muunnin.o

lib/main.o: main.c
	$(CC) $(CFLAGS) main.c -O3 -c -o lib/main.o

debug:
	$(CC) $(CFLAGS) $(SOURCES) -c -o lib/muunnin_debug.o
	$(CC) $(CFLAGS) lib/muunnin.o -shared -g -o lib/muunnin_debug.so
	$(CC) $(CFLAGS) main.c lib/muunnin.o -g -o muunnin_debug


#lib/muunnin.so: lib/muunnin.o
#	$(CC) $(CFLAGS) lib/muunnin.o -shared -O3 -o lib/muunnin.so


run:
	make
	./muunnin

debug_run:
	make debug
	valgrind --tool=memcheck --leak-check=full ./muunnin_debug 10


clean:
	rm -r muunnin
	rm -r muunnin_debug
	rm -r lib/*.a
	rm -r lib/*.so
