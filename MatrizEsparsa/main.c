#include "matriz.h"
#include <stdio.h>

int main(void) {
    Matriz A, B, C;

    // Leitura da matriz A
    FILE *arquivoA = fopen("matrizA.txt", "r");
    if (arquivoA == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo matrizA.txt\n");
        return 1;
    }
    A = leMatriz(arquivoA);
    fclose(arquivoA);

    printf("Matriz A:\n");
    imprimeMatriz(A);

    // Leitura da matriz B
    FILE *arquivoB = fopen("matrizB.txt", "r");
    if (arquivoB == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo matrizB.txt\n");
        return 1;
    }
    B = leMatriz(arquivoB);
    fclose(arquivoB);

    printf("\nMatriz B:\n");
    imprimeMatriz(B);

    // Soma das matrizes A e B
    C = somaMatrizes(A, B);
    printf("\nSoma de A e B:\n");
    imprimeMatriz(C);

    // Multiplicação das matrizes A e B
    C = multiplicaMatrizes(A, B);
    printf("\nProduto de A e B:\n");
    imprimeMatriz(C);

    return 0;
}
