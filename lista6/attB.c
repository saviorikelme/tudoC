#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Gerenciamento de Memória ---
int **criarMatriz(int linhas, int colunas) {
    int **matriz = (int**) malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int*) malloc(colunas * sizeof(int));
    }
    return matriz;
}

void liberarMatriz(int **matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

int **copiarMatriz(int **matriz, int linhas, int colunas) {
    int **novaMatriz = criarMatriz(linhas, colunas);
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            novaMatriz[i][j] = matriz[i][j];
        }
    }
    return novaMatriz;
}

void mostrarMatriz(int **matriz, int linhas, int colunas) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("%d%s", matriz[i][j], (j < colunas - 1 ? " " : ""));
        }
        printf("\n");
    }
}

// --- Lógica de Área de Efeito ---
void marcarArea(int x, int y, int linhas, int colunas, int area[100][100]) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) area[i][j] = 0;
    }

    int moverLinha[5] = {0, -1, 1, 0, 0};
    int moverColuna[5] = {0, 0, 0, -1, 1};

    for (int i = 0; i < 5; i++) {
        int nL = x + moverLinha[i];
        int nC = y + moverColuna[i];
        if (nL >= 0 && nL < linhas && nC >= 0 && nC < colunas) {
            area[nL][nC] = 1;
        }
    }

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (area[i][j] == 1) {
                for (int l = -1; l <= 1; l++) {
                    for (int c = -1; c <= 1; c++) {
                        int pL = i + l, pC = j + c;
                        if (pL >= 0 && pL < linhas && pC >= 0 && pC < colunas) {
                            if (area[pL][pC] == 0) area[pL][pC] = 2;
                        }
                    }
                }
            }
        }
    }
}

// --- Ataques ---
int **explosaoArcana(int **matriz, int linhas, int colunas, int x, int y) {
    int **resultado = copiarMatriz(matriz, linhas, colunas);
    int area[100][100];
    marcarArea(x, y, linhas, colunas, area);

    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            int dano = 0;
            if (area[i][j] == 1) dano = 50;
            else if (area[i][j] == 2) dano = 25;

            resultado[i][j] -= dano;
            if (resultado[i][j] < 0) resultado[i][j] = 0;
        }
    }
    return resultado;
}

void nuvemVenenosa(int **matriz, int linhas, int colunas, int x, int y) {
    int area[100][100];
    marcarArea(x, y, linhas, colunas, area);
    int **matrizAtual = copiarMatriz(matriz, linhas, colunas);

    for (int turno = 1; turno <= 3; turno++) {
        int **proximaMatriz = copiarMatriz(matrizAtual, linhas, colunas);
        int alguemVivoNaArea = 0;

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                if (area[i][j] > 0) {
                    int vizinhosVivos = 0;
                    for (int l = -1; l <= 1; l++) {
                        for (int c = -1; c <= 1; c++) {
                            if (l == 0 && c == 0) continue;
                            int vL = i + l, vC = j + c;
                            if (vL >= 0 && vL < linhas && vC >= 0 && vC < colunas) {
                                if (matrizAtual[vL][vC] > 0) vizinhosVivos++;
                            }
                        }
                    }
                    int dano = 5 + (8 * vizinhosVivos);
                    proximaMatriz[i][j] -= dano;
                    if (proximaMatriz[i][j] < 0) proximaMatriz[i][j] = 0;
                }
            }
        }

        // Verifica se sobrou alguém vivo na área após o dano
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                if (area[i][j] > 0 && proximaMatriz[i][j] > 0) alguemVivoNaArea = 1;
            }
        }

        printf("\n"); // Linha em branco antes de cada matriz de turno
        mostrarMatriz(proximaMatriz, linhas, colunas);
        
        liberarMatriz(matrizAtual, linhas);
        matrizAtual = proximaMatriz;

        if (!alguemVivoNaArea) break;
    }
    liberarMatriz(matrizAtual, linhas);
}

int main() {
    int m, n;
    if (scanf("%d %d", &m, &n) != 2) return 0;

    int **matriz = criarMatriz(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) scanf("%d", &matriz[i][j]);
    }

    int x, y;
    char tipo[50];
    scanf("%d %d", &x, &y);
    scanf("%s", tipo);

    printf("Estado inicial do mapa:\n");
    mostrarMatriz(matriz, m, n);

    if (strcmp(tipo, "EXPLOSAO_ARCANA") == 0) {
        printf("\nEstado do mapa após usar a Explosão Arcana:\n");
        int **(*ptrAtaque)(int**, int, int, int, int) = explosaoArcana;
        int **resultado = ptrAtaque(matriz, m, n, x, y);
        mostrarMatriz(resultado, m, n);
        liberarMatriz(resultado, m);
    } 
    else if (strcmp(tipo, "NUVEM_VENENOSA") == 0) {
        printf("\nEstado do mapa, por turno, após usar a Nuvem Venenosa:");
        nuvemVenenosa(matriz, m, n, x, y);
    }

    liberarMatriz(matriz, m);
    return 0;
}
