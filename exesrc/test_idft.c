#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include "cmplx.h"
#include "io.h"

#define _USE_MATH_DEFINES

void main() {
    int frek_o = 200;
    int frek_s = 50;
    int n = frek_o/frek_s;
    cmplx_t x_n[n];
    cmplx_t xn[n];
    cmplx_t X_k[n];

    int fd = open("./bin/X_k.bin", O_RDONLY, 00700);
    for (int j = 0; j < n; j++) {
        int real = read_word(fd);
        int imag = read_word(fd);
        void *r = (void *) &real;
        void *i = (void *) &imag;
        X_k[j][0] = *((float *) r);
        X_k[j][1] = *((float *) i);
    }
    close(fd);

    cmplx_idft(X_k, xn, n);

    for (int i = 0; i < n; i++) {
        float t = i / frek_o;
        x_n[i][0] = sin(2 * M_PI * 50 * t);
        x_n[i][1] = 0;
    }

    bool isti = true;
    for (int i = 0; i < n; i++) {
        if (x_n[i][0] != xn[i][0] || x_n[i][1] != xn[i][1]) isti = false;
    }

    if (isti) printf("Signali su isti.\n");
    else printf("Signali nisu isti.\n");

    return;
}