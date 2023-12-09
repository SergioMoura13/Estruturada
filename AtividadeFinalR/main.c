
#include <stdio.h>
#include "funcoes.h"

int main() {
    char arquivo1[] = "prod-2010-1.txt";
    char arquivo2[] = "prod-2010-2.txt";
    double matrizFinal[12][8];
    double valoresUnitarios[6];

    LerArquivoProducaoSemestral(arquivo1, (double *)matrizFinal);
    LerArquivoProducaoSemestral(arquivo2, (double *)matrizFinal);

    LerValoresUnitarios(valoresUnitarios);

    GerarMatrizFinal((double *)matrizFinal, valoresUnitarios);

    char arquivoSaida[] = "prod-2011-2010.txt";
    GerarArquivoDeSaida(arquivoSaida, (double *)matrizFinal);

    return 0;
}
