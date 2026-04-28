#include <stdio.h>
#include <stdlib.h>

// Definição do tipo para o ponteiro de função do filtro
typedef int (*FiltroFunc)(int);

// --- Filtros Disponíveis ---

int calibracao(int valor) {
    return valor + 5;
}

int saturacao(int valor) {
    return (valor > 80) ? 80 : valor;
}

int amplificador(int valor) {
    return valor * 2;
}

// --- Funções de Matriz ---

int **alocarMatriz(int n, int m) {
    int **matriz = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        matriz[i] = (int *)malloc(m * sizeof(int));
    }
    return matriz;
}

void liberarMatriz(int **matriz, int n) {
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// --- Função Central de Processamento ---

/**
 * A função modificar recebe a matriz, dimensões e um pipeline 
 * (vetor de ponteiros para função) com o número de filtros a aplicar.
 */
void modificar(int **matriz, int n, int m, FiltroFunc *pipeline, int k) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Aplica cada filtro do pipeline sequencialmente no valor do sensor
            for (int f = 0; f < k; f++) {
                matriz[i][j] = pipeline[f](matriz[i][j]);
            }
        }
    }
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    int **matriz = alocarMatriz(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }

    int comando;
    while (scanf("%d", &comando) && comando != 0) {
        FiltroFunc *pipeline = NULL;
        int k = 0;

        if (comando >= 1 && comando <= 3) {
            // Comandos simples: pipeline de 1 única função
            k = 1;
            pipeline = (FiltroFunc *)malloc(sizeof(FiltroFunc));
            if (comando == 1) pipeline[0] = calibracao;
            else if (comando == 2) pipeline[0] = saturacao;
            else if (comando == 3) pipeline[0] = amplificador;
        } 
        else if (comando == 4) {
            // Comando pipeline: lê k filtros
            scanf("%d", &k);
            pipeline = (FiltroFunc *)malloc(k * sizeof(FiltroFunc));
            for (int i = 0; i < k; i++) {
                int idFiltro;
                scanf("%d", &idFiltro);
                if (idFiltro == 1) pipeline[i] = calibracao;
                else if (idFiltro == 2) pipeline[i] = saturacao;
                else if (idFiltro == 3) pipeline[i] = amplificador;
            }
        }

        if (pipeline != NULL) {
            modificar(matriz, n, m, pipeline, k);
            free(pipeline);
        }
    }

    // --- Resultados Finais ---
    int maior = matriz[0][0];
    int lin = 0, col = 0;

    printf("Matriz processada:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d%s", matriz[i][j], (j == m - 1 ? "" : " "));
            if (matriz[i][j] > maior) {
                maior = matriz[i][j];
                lin = i;
                col = j;
            }
        }
        printf("\n");
    }
    
    printf("\nSensor critico: %d\n", maior);
    printf("Posicao: (%d,%d)\n", lin, col);

    liberarMatriz(matriz, n);
    return 0;
}
