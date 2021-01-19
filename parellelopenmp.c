#include <stdio.h>
#include "matrixmul.h"

void MatMul(int m, int n, int p, int b, double alpha, double beta, double* A, double* B, double* C)
{
    int i, j, k, ii, jj, kk;
    double* tempc = (double*)malloc(b * b * sizeof(double));
    for (i = 0; i < m; i += b)
    {
        for (j = 0; j < p; j += b)
        {
            for (ii = i; ii < i + b; ii++)
            {
                for (jj = j; jj < j + b; jj++)
                {
                    tempc[(ii - i) * b + (jj - j)] = C[ii * p + jj];
                    C[ii * p + jj] = 0;
                }
            }
            for (k = 0; k < n; k += b)
            {
                //block multiplication
                for (ii = i; ii < i + b; ii++)
                {
                    for (jj = j; jj < j + b; jj++)
                    {
                        for (kk = k; kk < k + b; kk++)
                        {
                            C[ii * p + jj] += A[ii * n + kk] * B[kk * p + jj];
                        }
                    }
                }
            }
            for (ii = i; ii < i + b; ii++)
            {
                for (jj = j; jj < j + b; jj++)
                {
                    C[ii * p + jj] = alpha * C[ii * p + jj] + beta * tempc[(ii - i) * b + (jj - j)];
                }
            }
        }
    }
}
