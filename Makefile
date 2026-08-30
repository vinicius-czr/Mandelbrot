CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
LDFLAGS_PTHREAD = -lpthread
LDFLAGS_OPENMP = -fopenmp

OBJ_DIR = obj
BIN_DIR = bin

COMUM_SRC = src/args.c src/mandelbrot.c src/io.c

all: serial

serial: $(BIN_DIR)/mandelbrot_serial

$(BIN_DIR)/mandelbrot_serial: $(COMUM_SRC) src/serial.c
	$(CC) $(CFLAGS) $(COMUM_SRC) src/serial.c -o $(BIN_DIR)/mandelbrot_serial

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/mandelbrot_serial $(BIN_DIR)/mandelbrot_openmp $(BIN_DIR)/mandelbrot_pthreads1 $(BIN_DIR)/mandelbrot_pthreads2
	rm -f *.pgm times.txt

.PHONY: all serial clean