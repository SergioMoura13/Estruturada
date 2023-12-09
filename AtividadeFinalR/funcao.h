
#ifndef FUNCOES_H
#define FUNCOES_H

void LerArquivoProducaoSemestral(char* arquivo, double M[12][6]);
void LerValoresUnitarios(double *V);
void GerarMatrizFinal(double *M, double *V);
void GerarArquivoDeSaida(char *nome_arquivo, double *M);
double MaiorValorDaLinha(double *M, int nlin);
double MenorValorDaLinha(double *M, int nlin);
double MaiorValorDaColuna(double *M, int ncol);
double MenorValorDaColuna(double *M, int ncol);

#endif
