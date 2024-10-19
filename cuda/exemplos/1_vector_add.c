#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define N 10000000
#define MAX_ERR 1e-6

void vector_add(float *out, float *a, float *b, int n) {
    for(int i = 0; i < n; i++){
        out[i] = a[i] + b[i];
    }
}

int main(){
    float *a, *b, *out; 

    // Aloca memória
    a   = (float*)malloc(sizeof(float) * N);
    b   = (float*)malloc(sizeof(float) * N);
    out = (float*)malloc(sizeof(float) * N);

    // Inicializa os vetores
    for(int i = 0; i < N; i++){
        a[i] = 1.0f; 
        b[i] = 2.0f;
    }

    // Soma os vetores
    vector_add(out, a, b, N);

    // Checa erros
    // Verification
    for(int i = 0; i < N; i++){
        assert(fabs(out[i] - a[i] - b[i]) < MAX_ERR);
    }
    printf("out[0] = %f\n", out[0]);
    printf("PASSED\n");

    // Libera a memória alocada
    free(a);
    free(b);
    free(out);

    return 0;
}
