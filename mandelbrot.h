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
    int max_iter;
    int num_threads;
} Params;

/* Parsing e validacao dos argumentos de linha de comando.
 * Retorna 0 em sucesso, ou valor != 0 em caso de erro,
 * ja imprimindo mensagem coerente em stderr. */
int parse_args(int argc, char *argv[], Params *p);

/* Calcula o numero de iteracoes ate a fuga (ou max_iter, se nao fugir) */
int mandelbrot_ponto(double cr, double ci, int max_iter);

/* Converte indice de pixel para coordenada no plano complexo */
double coord_real(int x, const Params *p);
double coord_imag(int y, const Params *p);

/* Calcula uma linha inteira da imagem */
void calcular_linha(unsigned char *imagem, int y, const Params *p);

/* As quatro implementacoes - mesma assinatura, mesma imagem de saida */
int calcular_serial(unsigned char *imagem, const Params *p);
int calcular_openmp(unsigned char *imagem, const Params *p);
int calcular_pthreads1(unsigned char *imagem, const Params *p);
int calcular_pthreads2(unsigned char *imagem, const Params *p);

/* Escreve a matriz de intensidades em formato PGM (sem cabecalho), uma linha por linha da imagem */
int escrever_pgm(const char *nome_arquivo, const unsigned char *imagem, const Params *p);

#endif
