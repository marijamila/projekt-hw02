#include <stdio.h>
#include <math.h>
#include "cmplx.h"

#define _USE_MATH_DEFINES

void cmplx_div(cmplx_t a, cmplx_t b, cmplx_t c) {
    c[0] = (a[0]*b[0] + a[1]*b[1]) / (b[0]*b[0] + b[1]*b[1]);
    c[1] = (a[1]*b[0] - a[0]*b[1]) / (b[0]*b[0] + b[1]*b[1]);
    return;
}

void cmplx_mul(cmplx_t a, cmplx_t b, cmplx_t c) {
    c[0] = a[0]*b[0] - a[1]*b[1];
    c[1] = a[0]*b[1] + a[1]*b[0];
    return;
}

double cmplx_mag(cmplx_t a) {
    double A = sqrt(a[0]*a[0] + a[1]*a[1]);
    return A;
}

double cmplx_phs(cmplx_t a) {
    if (a[0] == 0) {
        if (a[1] > 0) return M_PI/2;
        if (a[1] < 0) return 3*M_PI/2;
    }
    if (a[1] == 0) {
        if (a[0] > 0) return 0;
        if (a[0] < 0) return M_PI;
    }
    if (a[1] > 0) return atan(a[1]/a[0]);
    if (a[1] < 0) return atan(a[1]/a[0]) + M_PI;
}

double cmplx_real(double mag, double phs) {
    double R = mag * cos(phs);
    return R; 
}

double complx_imag(double mag, double phs) {
    double I = mag * sin(phs);
    return I;
}

// Xk = sum(x[n]*W^k*n), n=[0, N-1], k=[0, N-1]
// x[n] = 1/N * sum(Xk*W^-k*n)
// W = exp(i*2*pi/N)

void cmplx_dft(cmplx_t *input, cmplx_t *output, int N) {
    for (int k = 0; k <= N - 1; k++) {
        (*output + k)[0] = 0.0;
        (*output + k)[1] = 0.0;
        for (int n = 0; n <= N-1; n++) {
            cmplx_t W;
            cmplx_t rez;
            W[0] = cos(2 * M_PI * k * n / N);
            W[1] = -sin(2 * M_PI * k * n / N);
            cmplx_mul(*input + 2*n, W, rez);
            (*output + k)[0] += rez[0];
            (*output + k)[1] += rez[1];
        }
    }

    return;
}

void cmplx_idft(cmplx_t *input, cmplx_t *output, int N) {
    for (int k = 0; k <= N - 1; k++) {
        (*output + k)[0] = 0.0;
        (*output + k)[1] = 0.0;
        for (int n = 0; n <= N-1; n++) {
            cmplx_t W;
            cmplx_t rez;
            W[0] = cos(2 * M_PI * k * n / N);
            W[1] = sin(2 * M_PI * k * n / N);
            cmplx_mul(*input + 2*n, W, rez);
            (*output + k)[0] += rez[0]/N;
            (*output + k)[1] += rez[1]/N;
        }
    }

    return;
}