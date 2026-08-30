CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11
LIBS = -fopenmp -lpthread

FONTES = main.c args.c mandelbrot.c io.c pthreads1.c pthreads2.c
BINARIO = mandelbrot

all: $(BINARIO)

$(BINARIO): $(FONTES) mandelbrot.h
	$(CC) $(CFLAGS) $(FONTES) -o $(BINARIO) $(LIBS)

clean:
	rm -f $(BINARIO)
	rm -f *.pgm times.txt

.PHONY: all clean