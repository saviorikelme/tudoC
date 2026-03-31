#include <stdio.h>

// Função para verificar se a posição é válida
int eh_valido(int x, int y, int l, int c, char mapa[l][c], int visitado[l][c]) {
    if (x >= 0 && x < l && y >= 0 && y < c && mapa[x][y] != '#' && !visitado[x][y]) {
        return 1;
    }
    return 0;
}

// Função para gerenciar a inserção na fila
void enfileirar(int x, int y, int d, int *fim, int filaX[], int filaY[], int filaDist[]) {
    filaX[*fim] = x;
    filaY[*fim] = y;
    filaDist[*fim] = d;
    (*fim)++; // Incrementa o contador do fim da fila usando ponteiro
}

int main() {
    int linhas, colunas;

    // Leitura do formato "3x4"
    if (scanf("%dx%d", &linhas, &colunas) != 2) return 0;

    // Declaração local das matrizes
    char mapa[linhas][colunas];
    int visitado[linhas][colunas];
    int startX, startY;

    // Leitura do mapa
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            scanf(" %c", &mapa[i][j]);
            visitado[i][j] = 0;
            if (mapa[i][j] == 'o') {
                startX = i;
                startY = j;
            }
        }
    }

    // Fila local (tamanho baseado na área total do mapa)
    int tam_max = linhas * colunas;
    int filaX[tam_max], filaY[tam_max], filaDist[tam_max];
    int inicio = 0, fim = 0;

    // Início da busca
    enfileirar(startX, startY, 0, &fim, filaX, filaY, filaDist);
    visitado[startX][startY] = 1;

    int menorDistancia = -1;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while (inicio < fim) {
        int xAtual = filaX[inicio];
        int yAtual = filaY[inicio];
        int dAtual = filaDist[inicio];
        inicio++;

        if (mapa[xAtual][yAtual] == 'd') {
            menorDistancia = dAtual;
            break;
        }

        for (int i = 0; i < 4; i++) {
            int px = xAtual + dx[i];
            int py = yAtual + dy[i];

            if (eh_valido(px, py, linhas, colunas, mapa, visitado)) {
                visitado[px][py] = 1;
                enfileirar(px, py, dAtual + 1, &fim, filaX, filaY, filaDist);
            }
        }
    }

    if (menorDistancia != -1) {
        printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", menorDistancia);
    } else {
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }

    return 0;
}
