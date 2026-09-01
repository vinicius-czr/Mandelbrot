#include <stddef.h>
#include <omp.h>
#include "mandelbrot.h"

int mandelbrot_ponto(double cr, double ci, int max_iter) {
    double z_re = 0.0;
    double z_im = 0.0;
    int n;

    for (n = 0; n < max_iter; n++) {
        double re2 = z_re * z_re;
        double im2 = z_im * z_im;

        if (re2 + im2 > 4.0) {
            break;
        }

        double novo_im = 2.0 * z_re * z_im + ci;
        z_re = re2 - im2 + cr;
        z_im = novo_im;
    }

    return n;
}

double coord_real(int x, const Params *p) {
    if (p->largura <= 1) {
        return REAL_MIN;
    }
    double passo = (REAL_MAX - REAL_MIN) / (double)(p->largura - 1);
    return REAL_MIN + (double)x * passo;
}

double coord_imag(int y, const Params *p) {
    if (p->altura <= 1) {
        return IMAG_MIN;
    }
    double passo = (IMAG_MAX - IMAG_MIN) / (double)(p->altura - 1);
    return IMAG_MIN + (double)y * passo;
}

void calcular_linha(unsigned char *imagem, int y, const Params *p) {
    double ci = coord_imag(y, p);
    int largura = p->largura;
    int x;

    for (x = 0; x < largura; x++) {
        double cr = coord_real(x, p);
        int iteracoes = mandelbrot_ponto(cr, ci, p->max_iter);

        imagem[(size_t)y * (size_t)largura + (size_t)x] =
            (unsigned char)(255.0 * (double)iteracoes / (double)p->max_iter);
    }
}

int calcular_serial(unsigned char *imagem, const Params *p) {
    int y;

    for (y = 0; y < p->altura; y++) {
        calcular_linha(imagem, y, p);
    }

    return 0;
}

int calcular_openmp(unsigned char *imagem, const Params *p) {
    int y;

    #pragma omp parallel for num_threads(p->num_threads) schedule(dynamic, 1)
    for (y = 0; y < p->altura; y++) {
        calcular_linha(imagem, y, p);
    }

    return 0;
}
