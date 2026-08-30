#include "mandelbrot.h"

int mandelbrot_ponto(double c_re, double c_im, int max_iteracoes) {
    double z_re = 0.0;
    double z_im = 0.0;
    int iteracao = 0;

    while (iteracao < max_iteracoes) {
        double z_re2 = z_re * z_re;
        double z_im2 = z_im * z_im;

        /* Criterio de fuga: |z| > 2, ou seja, |z|^2 > 4 */
        if (z_re2 + z_im2 > 4.0) {
            break;
        }
        double novo_re = z_re2 - z_im2 + c_re;
        double novo_im = 2.0 * z_re * z_im + c_im;
        z_re = novo_re;
        z_im = novo_im;

        iteracao++;
    }

    return iteracao;
}