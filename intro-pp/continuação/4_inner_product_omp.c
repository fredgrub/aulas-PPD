#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define VECLEN 100000

double global_sum = 0;

int main(int argc, char *argv[]) {
  int i, chunk;
  double *a, *b, sum;

  chunk = 1000;

  a = (double *)malloc(VECLEN * sizeof(double));
  b = (double *)malloc(VECLEN * sizeof(double));

  for (i = 0; i < VECLEN; i++) {
    a[i] = 1;
    b[i] = a[i];
  }
  sum = 0;
#pragma omp parallel default(shared) private(i, sum)
  {
#pragma omp for schedule(dynamic, chunk)
    for (i = 0; i < VECLEN; i++) {
      sum += (a[i] * b[i]);
    }
#pragma omp critical
    { global_sum += sum; }
  }

  printf("Sum =  %f \n", global_sum);
  free(a);
  free(b);
}