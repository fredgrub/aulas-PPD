#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <assert.h>

#include <cilk/cilk.h>

#define N 2048
#define THRESHOLD 64
double A[N][N], B[N][N], C[N][N];

float tdiff(struct timeval *start, struct timeval *end)
{
  return (end->tv_sec-start->tv_sec) + 1.0e-6*(end->tv_usec-start->tv_usec);
}

void mm_base(double *restrict C, int n_C,
             double *restrict A, int n_A,
             double *restrict B, int n_B,
             int n)
{
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i*n_C + j] += A[i*n_A + k] * B[k*n_B + j];
            }
        }
    }
}

void mm_dac(double *restrict C, int n_C,
            double *restrict A, int n_A,
            double *restrict B, int n_B,
            int n)
{
    assert((n & -n) == n); // n is a power of 2
    if (n <= THRESHOLD) {
        mm_base(C, n_C, A, n_A, B, n_B, n);
    } else {
#define X(M, r, c) (M + (r*(n_ ## M) + c)*(n/2)) // M[r][c]
        cilk_spawn mm_dac(X(C, 0, 0), n_C, X(A, 0, 0), n_A, X(B, 0, 0), n_B, n/2);
        cilk_spawn mm_dac(X(C, 0, 1), n_C, X(A, 0, 0), n_A, X(B, 0, 1), n_B, n/2);
        cilk_spawn mm_dac(X(C, 1, 0), n_C, X(A, 1, 0), n_A, X(B, 0, 0), n_B, n/2);
        mm_dac(X(C, 1, 1), n_C, X(A, 1, 0), n_A, X(B, 0, 1), n_B, n/2);
        cilk_sync;
        cilk_spawn mm_dac(X(C, 0, 0), n_C, X(A, 0, 1), n_A, X(B, 1, 0), n_B, n/2);
        cilk_spawn mm_dac(X(C, 0, 1), n_C, X(A, 0, 1), n_A, X(B, 1, 1), n_B, n/2);
        cilk_spawn mm_dac(X(C, 1, 0), n_C, X(A, 1, 1), n_A, X(B, 1, 0), n_B, n/2);
        mm_dac(X(C, 1, 1), n_C, X(A, 1, 1), n_A, X(B, 1, 1), n_B, n/2);
        cilk_sync;
    }
}

int main(int argc, const char *argv[]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = (double)rand() / (double)RAND_MAX;
            B[i][j] = (double)rand() / (double)RAND_MAX;
            C[i][j] = 0;
        }
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    mm_dac(&C[0][0], N, &A[0][0], N, &B[0][0], N, N);
    
    gettimeofday(&end, NULL);
    printf("Time: %f sec\n", tdiff(&start, &end));
    return 0;
}
