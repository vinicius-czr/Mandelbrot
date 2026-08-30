#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mandelbrot.h"

int main(int argc, char *argv[]) {
    Config cfg;
    int status_args = parse_args(argc, argv, &cfg);
    if (status_args != 0) {
        return status_args;
    }

    unsigned char *pixels = malloc((size_t)cfg.largura * (size_t)cfg.altura * sizeof(unsigned char));
    if (pixels == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para a imagem.\n");
        return 3;
    }

    struct timespec inicio, fim;
    clock_gettime(CLOCK_MONOTONIC, &inicio);

    for (int y = 0; y < cfg.altura; y++) {
        double c_im = IMAG_MIN + (IMAG_MAX - IMAG_MIN) * ((double)y / (cfg.altura - 1));

        for (int x = 0; x < cfg.largura; x++) {
            double c_re = REAL_MIN + (REAL_MAX - REAL_MIN) * ((double)x / (cfg.largura - 1));

            int iteracoes = mandelbrot_ponto(c_re, c_im, cfg.max_iteracoes);

            /* Normaliza a intensidade entre 0 e 255, proporcional as iteracoes realizadas */
            pixels[y * cfg.largura + x] = (unsigned char)(255.0 * iteracoes / cfg.max_iteracoes);
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &fim);
    double tempo_decorrido = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1e9;

    if (escrever_pgm("mandelbrot_vcrc_serial.pgm", pixels, cfg.largura, cfg.altura) != 0) {
        free(pixels);
        return 3;
    }

    if (registrar_tempo("times.txt", "Serial", tempo_decorrido) != 0) {
        free(pixels);
        return 3;
    }

    free(pixels);
    return 0;
}