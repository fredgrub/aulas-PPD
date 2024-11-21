/*
    Hello World usando MPI
    
    Para compilar:
        mpicc -o helloWorld helloWorld.c
    
    Para executar:
        mpirun -np 2 ./helloWorld
*/
#include <stdio.h>
#include <string.h>
#include <mpi.h> // Inclui a biblioteca MPI (Message Passing Interface)

int main(int argc, char *argv[]) {
    char message[14];   // Declara um array de caracteres para armazenar a mensagem
    int myRank;         // Declara uma variável para armazenar o rank do processo

    MPI_Init(&argc, &argv);  // Inicializa o ambiente MPI

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);  // Obtém o rank do processo atual

    if (myRank == 0) {
        int size;

        MPI_Comm_size(MPI_COMM_WORLD, &size);  // Obtém o número de processos no comunicador

        printf("Existem %d processos\n", size);

        strcpy(message, "Hello, world!");  // Copia a mensagem "Hello, world!" para o array 'message'
        MPI_Send(message, strlen(message), MPI_CHAR, 1, 99, MPI_COMM_WORLD);  // Envia a mensagem para o processo com rank 1
    }
    else {
        MPI_Recv(message, 14, MPI_CHAR, 0, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);  // Recebe a mensagem do processo com rank 1
        printf("Recebi: %s\n", message);
    }

    MPI_Finalize();  // Finaliza o ambiente MPI
}