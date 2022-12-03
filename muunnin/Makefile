CC = gcc

CFLAGS = -std=gnu11 -Wall

SOURCES = main.c muunnin.c
HEADERS = *.h

default:
	$(CC) $(CFLAGS) muunnin.c -c -o static/muunnin.o
	$(CC) $(CFLAGS) main.c static/muunnin.o -o muunnin

clean:
	rm muunnin
	rm static/muunnin.o
