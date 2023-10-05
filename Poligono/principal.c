#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float X;
    float Y;
} Ponto;

float calcularArea(Ponto *vertices, int numVertices) {
    float area = 0.0;

    for (int i = 0; i < numVertices; i++) {
        int j = (i + 1) % numVertices;
        area += (vertices[i].X * vertices[j].Y) - (vertices[j].X * vertices[i].Y);
    }

    area = 0.5 * fabs(area);

    return area;
}

int main() {
    FILE *file;
    file = fopen("poligono.txt", "r"); 

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int numVertices;
    fscanf(file, "%d", &numVertices);

    Ponto *vertices = (Ponto *)malloc(numVertices * sizeof(Ponto));

    if (vertices == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    for (int i = 0; i < numVertices; i++) {
        fscanf(file, "%f %f", &vertices[i].X, &vertices[i].Y);
    }

    fclose(file);

    float area = calcularArea(vertices, numVertices);

    printf("A área do polígono é %.2f\n", area);

    free(vertices);

    return 0;
}
