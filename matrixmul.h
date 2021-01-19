
#ifndef MISC_H
#define MISC_H

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define MIN_DIM  1024
#define MAX_DIM  1536
#define NUM_V 10

void MatMul(int m, int n, int p, int b, double alpha, double beta, double* A, double* B, double* C);

#endif
