#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include <cilk/cilk.h>

#define n 2048
#define s 64
double A[n][n], B[n][n], C[n][n];

float tdiff(struct timeval *start, struct timeval *end)
{
  return (end->tv_sec-start->tv_sec) + 1.0e-6*(end->tv_usec-start->tv_usec);
}

int main(int argc, const char *argv[]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = (double)rand() / (double)RAND_MAX;
            B[i][j] = (double)rand() / (double)RAND_MAX;
            C[i][j] = 0;
        }
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    cilk_for (int ih = 0; ih < n; ih += s) {
        cilk_for (int jh = 0; jh < n; jh += s) {
            for (int kh = 0; kh < n; kh += s) {
                for (int il = 0; il < s; il++) {
                    for (int kl = 0; kl < s; kl++) {
                        for (int jl = 0; jl < s; jl++) {
                            C[ih + il][jh + jl] += A[ih + il][kh + kl] * B[kh + kl][jh + jl];
                        }
                    }
                }
            }
        }
    }

    gettimeofday(&end, NULL);
    printf("Time: %f sec\n", tdiff(&start, &end));
    return 0;
}
