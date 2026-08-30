#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mandelbrot.h"

#define QTD_IMPLEMENTACOES 4

typedef struct {
    const char *rotulo;
    const char *arquivo_saida;
    int (*calcular)(unsigned char *, const Params *);
} Implementacao;

static double medir_segundos(struct timespec inicio, struct timespec fim) {
    return (double)(fim.tv_sec - inicio.tv_sec) +
           (double)(fim.tv_nsec - inicio.tv_nsec) / 1e9;
}

static int rodar_implementacao(const Implementacao *impl, unsigned char *imagem,
                                const Params *p, double *tempo_saida) {
    struct timespec t_inicio, t_fim;

    clock_gettime(CLOCK_MONOTONIC, &t_inicio);

    if (impl->calcular(imagem, p) != 0) {
        fprintf(stderr, "Erro: a implementacao '%s' falhou durante o calculo.\n", impl->rotulo);
        return -1;
    }

    clock_gettime(CLOCK_MONOTONIC, &t_fim);
    *tempo_saida = medir_segundos(t_inicio, t_fim);

    if (escrever_pgm(impl->arquivo_saida, imagem, p) != 0) {
        return -1;
    }

    return 0;
}

static int salvar_tempos(const char *nome_arquivo, const Implementacao *lista,
                          const double *tempos, int quantidade) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    int i;

    if (arquivo == NULL) {
        fprintf(stderr, "Erro: nao foi possivel criar o arquivo '%s'.\n", nome_arquivo);
        return -1;
    }

    for (i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%s: %.6f segundos\n", lista[i].rotulo, tempos[i]);
    }

    if (ferror(arquivo) || fclose(arquivo) != 0) {
        fprintf(stderr, "Erro: falha ao gravar o arquivo '%s'.\n", nome_arquivo);
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    Params p;
    unsigned char *imagem;
    double tempos[QTD_IMPLEMENTACOES];
    size_t total_pixels;
    int i;

    const Implementacao implementacoes[QTD_IMPLEMENTACOES] = {
        { "Serial",    "mandelbrot_vcrc_serial.pgm",    calcular_serial },
        { "OpenMP",    "mandelbrot_vcrc_openmp.pgm",    calcular_openmp },
        { "Pthreads1", "mandelbrot_vcrc_pthreads1.pgm", calcular_pthreads1 },
        { "Pthreads2", "mandelbrot_vcrc_pthreads2.pgm", calcular_pthreads2 },
    };

    if (parse_args(argc, argv, &p) != 0) {
        return EXIT_FAILURE;
    }

    total_pixels = (size_t)p.largura * (size_t)p.altura;
    imagem = malloc(total_pixels * sizeof(unsigned char));
    if (imagem == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para a imagem (%zu pixels).\n", total_pixels);
        return EXIT_FAILURE;
    }

    for (i = 0; i < QTD_IMPLEMENTACOES; i++) {
        if (rodar_implementacao(&implementacoes[i], imagem, &p, &tempos[i]) != 0) {
            free(imagem);
            return EXIT_FAILURE;
        }
    }

    if (salvar_tempos("times.txt", implementacoes, tempos, QTD_IMPLEMENTACOES) != 0) {
        free(imagem);
        return EXIT_FAILURE;
    }

    free(imagem);
    return EXIT_SUCCESS;
}
    