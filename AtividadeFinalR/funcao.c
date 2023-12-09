
#include <stdio.h>
#include "funcoes.h"

void LerArquivoProducaoSemestral(char* arquivo, double M[12][6]) {
    FILE *fp;
    fp = fopen(arquivo, "r");

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", arquivo);
        return;
    }

   
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 6; j++) {
            fscanf(fp, "%lf", &M[i][j]);
        }
    }

    fclose(fp);
}

void LerValoresUnitarios(double *V) {
    printf("Informe os valores unitarios para cada produto:\n");

    for (int i = 0; i < 6; i++) {
        printf("Produto %d: ", i + 1);
        scanf("%lf", &V[i]);
    }
}

void GerarMatrizFinal(double *M, double *V) {
    
    for (int i = 0; i < 12; i++) {
        double totalUnidades = 0.0;
        double totalReais = 0.0;

        for (int j = 0; j < 6; j++) {
            totalUnidades += M[i * 6 + j];
            totalReais += M[i * 6 + j] * V[j]; 
        }

        M[i * 8 + 6] = totalUnidades;
        M[i * 8 + 7] = totalReais;
    }

    for (int j = 0; j < 6; j++) {
        double totalAnualUnidades = 0.0;
        double totalAnualReais = 0.0;

        for (int i = 0; i < 12; i++) {
            totalAnualUnidades += M[i * 6 + j];
            totalAnualReais += M[i * 6 + j] * V[j]; /
        }

        M[10 * 8 + j] = totalAnualUnidades;
        M[11 * 8 + j] = totalAnualReais;
    }
}

void GerarArquivoDeSaida(char *nome_arquivo, double *M) {
    FILE *fp;
    fp = fopen(nome_arquivo, "w");

    if (fp == NULL) {
        printf("Erro ao criar o arquivo de saída %s.\n", nome_arquivo);
        return;
    }

    fprintf(fp, "−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n");
    fprintf(fp, "Produção anual total em unidades por produto\n");
    fprintf(fp, "−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−\n");

    // Escrita no arquivo com base na matriz M
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 8; j++) {
            fprintf(fp, "%.2lf\t", M[i * 8 + j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

double MaiorValorDaLinha(double *M, int nlin) {
    double maior = M[nlin * 8];

    for (int j = 1; j < 8; j++) {
        if (M[nlin * 8 + j] > maior) {
            maior = M[nlin * 8 + j];
        }
    }

    return maior;
}

double MenorValorDaLinha(double *M, int nlin) {
    double menor = M[nlin * 8];

    for (int j = 1; j < 8; j++) {
        if (M[nlin * 8 + j] < menor) {
            menor = M[nlin * 8 + j];
        }
    }

    return menor;
}

double MaiorValorDaColuna(double *M, int ncol) {
    double maior = M[ncol];

    for (int i = 1; i < 12; i++) {
        if (M[i * 8 + ncol] > maior) {
            maior = M[i * 8 + ncol];
        }
    }

    return maior;
}

double MenorValorDaColuna(double *M, int ncol) {
    double menor = M[ncol];

    for (int i = 1; i < 12; i++) {
        if (M[i * 8 + ncol] < menor) {
            menor = M[i * 8 + ncol];
        }
    }

    return menor;
}
