#include <stdio.h>
#include <stdlib.h>

#define VECLEN 100000

int main(int argc, char *argv[]) {
  int i;
  double *a, *b, sum;

  a = (double *)malloc(VECLEN * sizeof(double));
  b = (double *)malloc(VECLEN * sizeof(double));

  for (i = 0; i < VECLEN; i++) {
    a[i] = 1;
    b[i] = a[i];
  }

  sum = 0;
  for (i = 0; i < VECLEN; i++) {
    sum += (a[i] * b[i]);
  }

  printf("Sum =  %f \n", sum);
  free(a);
  free(b);
}