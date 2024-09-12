#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double *a;
  double *b;
  double sum;
  int veclen;
} DOTDATA;

#define VECLEN 100000
DOTDATA dotstr;

void dotprod() {

  /* Define and use local variables for convenience */

  int start, end, i;
  double mysum, *x, *y;

  start = 0;
  end = dotstr.veclen;
  x = dotstr.a;
  y = dotstr.b;

  /*
  Perform the dot product and assign result
  to the appropriate variable in the structure.
  */

  mysum = 0;
  for (i = start; i < end; i++) {
    mysum += (x[i] * y[i]);
  }
  dotstr.sum = mysum;
}

int main(int argc, char *argv[]) {
  int i, len;
  double *a, *b;

  /* Assign storage and initialize values */
  len = VECLEN;
  a = (double *)malloc(len * sizeof(double));
  b = (double *)malloc(len * sizeof(double));

  for (i = 0; i < len; i++) {
    a[i] = 1;
    b[i] = a[i];
  }

  dotstr.veclen = len;
  dotstr.a = a;
  dotstr.b = b;
  dotstr.sum = 0;

  /* Perform the  dotproduct */
  dotprod();

  /* Print result and release storage */
  printf("Sum =  %f \n", dotstr.sum);
  free(a);
  free(b);
}
