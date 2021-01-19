#include <stdio.h>
#include "matrixmul.h"

int main(int argc, char** argv)
{
    double* A, * B, * C, * Cor, alpha, beta, t1, t2;
    int m, n, p, b, bb, bbmin, bbmax;
    int row, col, numt;
    char status[100];

    alpha = (double)1.3;
    beta = (double)2.9;

    A = (double*)malloc(sizeof(double) * MAX_DIM * MAX_DIM);
    B = (double*)malloc(sizeof(double) * MAX_DIM * MAX_DIM);
    C = (double*)malloc(sizeof(double) * MAX_DIM * MAX_DIM);
    Cor = (double*)malloc(sizeof(double) * MAX_DIM * MAX_DIM);
    if ((A == NULL) || (B == NULL) || (C == NULL) || (Cor == NULL))
    {
        printf("Out of Memory\n");
        exit(1);
    }

    for (row = 0; row < MAX_DIM; row++)
        for (col = 0; col < MAX_DIM; col++)
            A[row * MAX_DIM + col] = rand();

    for (row = 0; row < MAX_DIM; row++)
        for (col = 0; col < MAX_DIM; col++)
            B[row * MAX_DIM + col] = rand();

    for (row = 0; row < MAX_DIM; row++)
        for (col = 0; col < MAX_DIM; col++)
            Cor[row * MAX_DIM + col] = rand();

    for (m = MIN_DIM; m <= MAX_DIM; m += 256)
    {
        n = p = m;
        for (numt = 1; numt <= 4; numt *= 2)
        {
            if (numt == 4)
            {
                bbmin = 4;
                bbmax = 64;
            }
            else
                bbmin = bbmax = 16;
            for (bb = bbmin; bb <= bbmax; bb *= 4)
            {
                for (row = 0; row < m; row++)
                    for (col = 0; col < p; col++)
                        C[row * p + col] = Cor[row * p + col];
                b = bb;
                if (b > m) b = m;
                if (b > n) b = n;
                if (b > p) b = p;

                omp_set_num_threads(numt);
                t1 = time(NULL);
                MatMul(m, n, p, b, alpha, beta, A, B, C);
                t2 = time(NULL);

               
                int success = 1, r;
                for (r = 0; r < NUM_V; r++)
                {
                    double min, max, err, ans;

                    row = (rand() % m);
                    col = (rand() % p);

                    int k;
                    ans = Cor[row * p + col] * beta;
                    for (k = 0; k < n; k++)
                        ans += alpha * A[row * n + k] * B[k * p + col];

                    if (ans > C[row * p + col])
                    {
                        min = C[row * p + col];
                        max = ans;
                    }
                    else
                    {
                        min = ans;
                        max = C[row * p + col];
                    }
                    err = (double)(max - min) / (double)max;

                    if ((min > (double)0.0001) && (err > (double)0.01))
                        success = 0;
                }

                if (success == 0)
                    strcpy(status, "Failed");
                else
                    strcpy(status, "Passed");

                printf("{m=%d,n=%d,p=%d,threads=%d,efftime=%g,status=%s},  ", m, n, p, numt, (double)difftime(t2, t1), status);
                fflush(stdout);
            }
        }
    }
    return 0;
}

