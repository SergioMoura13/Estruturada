#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

void inicializaMatriz(Matriz *matriz, int nlin, int ncol) {
    matriz->nlin = nlin;
    matriz->ncol = ncol;

    matriz->cabeca = (Celula *)malloc(sizeof(Celula));
    matriz->cabeca->linha = -1;
    matriz->cabeca->coluna = -1;
    matriz->cabeca->direita = matriz->cabeca;
    matriz->cabeca->abaixo = matriz->cabeca;
}

void insere(Matriz *matriz, int linha, int coluna, float valor) {
    Celula *nova = (Celula *)malloc(sizeof(Celula));
    nova->linha = linha;
    nova->coluna = coluna;
    nova->valor = valor;

    Celula *atual = matriz->cabeca;

    while (atual->direita != matriz->cabeca && atual->direita->coluna < coluna) {
        atual = atual->direita;
    }

    nova->direita = atual->direita;
    atual->direita = nova;

    atual = matriz->cabeca;

    while (atual->abaixo != matriz->cabeca && atual->abaixo->linha < linha) {
        atual = atual->abaixo;
    }

    nova->abaixo = atual->abaixo;
    atual->abaixo = nova;
}

void imprimeMatriz(Matriz matriz) {
    for (int i = 0; i < matriz.nlin; i++) {
        Celula *atual = matriz.cabeca->direita;

        while (atual != matriz.cabeca) {
            if (atual->linha == i) {
                printf("%.2f ", atual->valor);
                atual = atual->direita;
            } else {
                printf("0.00 ");
            }
        }

        printf("\n");
    }
}

Matriz leMatriz(FILE *arquivo) {
    Matriz matriz;
    int nlin, ncol;
    int linha, coluna;
    float valor;

    fscanf(arquivo, "%d %d", &nlin, &ncol);
    inicializaMatriz(&matriz, nlin, ncol);

    while (fscanf(arquivo, "%d %d %f", &linha, &coluna, &valor) == 3) {
        insere(&matriz, linha, coluna, valor);
    }

    return matriz;
}

Matriz somaMatrizes(Matriz A, Matriz B) {
    Matriz C;
    inicializaMatriz(&C, A.nlin, A.ncol);

    Celula *atualA = A.cabeca->direita;
    Celula *atualB = B.cabeca->direita;

    while (atualA != A.cabeca || atualB != B.cabeca) {
        if ((atualA->linha < atualB->linha) ||
            (atualA->linha == atualB->linha && atualA->coluna < atualB->coluna)) {
            insere(&C, atualA->linha, atualA->coluna, atualA->valor);
            atualA = atualA->direita;
        } else if ((atualB->linha < atualA->linha) ||
                   (atualB->linha == atualA->linha && atualB->coluna < atualA->coluna)) {
            insere(&C, atualB->linha, atualB->coluna, atualB->valor);
            atualB = atualB->direita;
        } else {
            float soma = atualA->valor + atualB->valor;
            if (soma != 0.0) {
                insere(&C, atualA->linha, atualA->coluna, soma);
            }
            atualA = atualA->direita;
            atualB = atualB->direita;
        }
    }

    return C;
}

Matriz multiplicaMatrizes(Matriz A, Matriz B) {
    Matriz C;
    inicializaMatriz(&C, A.nlin, B.ncol);

    for (int i = 0; i < A.nlin; i++) {
        for (int j = 0; j < B.ncol; j++) {
            float soma = 0.0;
            Celula *atualA = A.cabeca->direita;
            Celula *atualB = B.cabeca->direita;

            while (atualA != A.cabeca && atualB != B.cabeca) {
                if (atualA->coluna < atualB->linha) {
                    atualA = atualA->direita;
                } else if (atualB->linha < atualA->coluna) {
                    atualB = atualB->abaixo;
                } else {
                    soma += atualA->valor * atualB->valor;
                    atualA = atualA->direita;
                    atualB = atualB->abaixo;
                }
            }

            if (soma != 0.0) {
                insere(&C, i, j, soma);
            }
        }
    }

    return C;
}
