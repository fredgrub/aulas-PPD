#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double *a;
  double *b;
  double sum;
  int veclen;
} DOTDATA;

#define BLOCKLEN 100000
DOTDATA dotstr;

#define NUM_THREADS 8

pthread_t threads[NUM_THREADS];
pthread_mutex_t mutex;
int next_block_to_process = 0;

void *dotprod(void *arg) {

  /* Define and use local variables for convenience */

  int start, end, i, blocklen;
  double mysum, *x, *y;
  long threadid = (long)arg;

  blocklen = BLOCKLEN;

  while (1) {
    pthread_mutex_lock(&mutex);
    start = next_block_to_process * blocklen;
    if (start >= dotstr.veclen) {
      pthread_mutex_unlock(&mutex);
      break;
    }
    next_block_to_process++;
    end = (start + blocklen < dotstr.veclen) ? start + blocklen : dotstr.veclen;
    pthread_mutex_unlock(&mutex);

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
    pthread_mutex_lock(&mutex);
    dotstr.sum += mysum;
    printf("Thread %ld did %d to %d:  mysum=%f global sum=%f\n", threadid,
           start, end, mysum, dotstr.sum);
    pthread_mutex_unlock(&mutex);
    mysum = 0;
  }

  pthread_exit((void *)0);
}

int main(int argc, char *argv[]) {
  long i;
  double *a, *b;
  void *status;
  pthread_attr_t attr;

  /* Assign storage and initialize values */
  a = (double *)malloc(NUM_THREADS * BLOCKLEN * 4 * sizeof(double));
  b = (double *)malloc(NUM_THREADS * BLOCKLEN * 4 * sizeof(double));

  pthread_mutex_init(&mutex, NULL);

  /* Create threads to perform the dotproduct  */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for (i = 0; i < NUM_THREADS * BLOCKLEN * 4; i++) {
    a[i] = 1;
    b[i] = a[i];
  }

  dotstr.veclen = BLOCKLEN * NUM_THREADS * 4;
  dotstr.a = a;
  dotstr.b = b;
  dotstr.sum = 0;

  for (i = 0; i < NUM_THREADS; i++) {
    pthread_create(&threads[i], &attr, dotprod, (void *)i);
  }

  pthread_attr_destroy(&attr);

  for (i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], &status);
  }

  /* Print result and release storage */
  printf("Sum =  %f \n", dotstr.sum);
  free(a);
  free(b);
  pthread_mutex_destroy(&mutex);
  pthread_exit(NULL);
}
