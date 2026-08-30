CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
LDFLAGS_PTHREAD = -lpthread
LDFLAGS_OPENMP = -fopenmp

OBJ_DIR = obj
BIN_DIR = bin

COMUM_SRC = src/args.c src/mandelbrot.c src/io.c

all: serial openmp

serial: $(BIN_DIR)/mandelbrot_serial

$(BIN_DIR)/mandelbrot_serial: $(COMUM_SRC) src/serial.c
	$(CC) $(CFLAGS) $(COMUM_SRC) src/serial.c -o $(BIN_DIR)/mandelbrot_serial

openmp: $(BIN_DIR)/mandelbrot_openmp

$(BIN_DIR)/mandelbrot_openmp: $(COMUM_SRC) src/openmp.c
	$(CC) $(CFLAGS) $(LDFLAGS_OPENMP) $(COMUM_SRC) src/openmp.c -o $(BIN_DIR)/mandelbrot_openmp

clean:
	rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/mandelbrot_serial $(BIN_DIR)/mandelbrot_openmp $(BIN_DIR)/mandelbrot_pthreads1 $(BIN_DIR)/mandelbrot_pthreads2
	rm -f *.pgm times.txt

.PHONY: all serial clean