#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "cmplx.h"
#include "io.h"

#define _USE_MATH_DEFINES

void main() {
    int frek_o = 200;
    int frek_s = 50;
    int n = frek_o/frek_s;
    cmplx_t x_n[n];
    cmplx_t X_k[n];

    for (int i = 0; i < n; i++) {
        float t = i / frek_o;
        x_n[i][0] = sin(2 * M_PI * 50 * t);
        x_n[i][1] = 0;
    }

    cmplx_dft(x_n, X_k, n);

    int fd = open("./bin/X_k.bin", O_CREAT | O_WRONLY, 00700);
    for (int j = 0; j < n; j++) {
        void *r = (void *) &X_k[j][0];
        void *i = (void *) &X_k[j][1];
        int real = *((int *) r);
        int imag = *((int *) i);
        write_word(fd, (int) real);
        write_word(fd, (int) imag);
    }
    close(fd);

    return;
}