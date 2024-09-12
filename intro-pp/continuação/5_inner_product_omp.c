#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define VECLEN 100000

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
#pragma omp parallel for default(shared) private(i) schedule(dynamic, chunk)   \
    reduction(+ : sum)
  for (i = 0; i < VECLEN; i++) {
    sum += (a[i] * b[i]);
  }

  printf("Sum =  %f \n", sum);
  free(a);
  free(b);
}