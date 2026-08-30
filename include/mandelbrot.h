#ifndef MANDELBROT_H
#define MANDELBROT_H

/* Limites do plano complexo definidos no enunciado */
#define REAL_MIN -2.0
#define REAL_MAX  1.0
#define IMAG_MIN -1.5
#define IMAG_MAX  1.5

typedef struct {
    int largura;
    int altura;
    int max_iteracoes;
    int num_threads;
} Config;

/* Faz o parsing e a validacao dos argumentos de linha de comando.
 * Retorna 0 em sucesso, ou um codigo de erro != 0 em caso de falha,
 * ja imprimindo a mensagem de erro coerente em stderr. */
int parse_args(int argc, char *argv[], Config *cfg);

/* Calcula o numero de iteracoes ate a fuga (ou max_iteracoes, se nao fugir) */
int mandelbrot_ponto(double c_re, double c_im, int max_iteracoes);

/* Escreve a matriz de intensidades em formato PGM (P2, texto), sem cabecalho extra alem do padrao PGM */
int escrever_pgm(const char *nome_arquivo, unsigned char *pixels, int largura, int altura);

/* Registra "label: tempo_em_segundos" no arquivo de saida (times.txt), em modo append */
int registrar_tempo(const char *nome_arquivo, const char *label, double segundos);

#endif