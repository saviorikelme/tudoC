#include <stdio.h>

// Função para validar se a posição é segura para a Rebeka
// Em C, matrizes passadas para funções precisam das dimensões (l e c)
int eh_valido(int x, int y, int l, int c, char mapa[l][c], int visitado[l][c]) {
    if (x >= 0 && x < l && y >= 0 && y < c && mapa[x][y] != '#' && visitado[x][y] == 0) {
        return 1;
    }
    return 0;
}

int main() {
    int linhas, colunas;

    // Leitura do formato "linhasxcolunas" (ex: 3x4)
    if (scanf("%dx%d", &linhas, &colunas) != 2) return 0;

    char mapa[linhas][colunas];
    int visitado[linhas][colunas];
    int startX, startY;

    // Lendo o mapa e limpando a matriz de visitados
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

    // Fila manual usando vetores paralelos
    int tam_max = linhas * colunas;
    int filaX[tam_max], filaY[tam_max], filaDist[tam_max];
    int inicio = 0, fim = 0;

    // Adiciona a origem na fila (Enfileirar manual para evitar ponteiros)
    filaX[fim] = startX;
    filaY[fim] = startY;
    filaDist[fim] = 0;
    fim++;
    visitado[startX][startY] = 1;

    int menorDistancia = -1;
    
    // Vetores de direção: Cima, Baixo, Esquerda, Direita
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // BFS - Busca em Largura
    while (inicio < fim) {
        int xAtual = filaX[inicio];
        int yAtual = filaY[inicio];
        int dAtual = filaDist[inicio];
        inicio++;

        // Se achou a saída 'd'
        if (mapa[xAtual][yAtual] == 'd') {
            menorDistancia = dAtual;
            break;
        }

        // Tenta os 4 movimentos usando a função auxiliar
        for (int i = 0; i < 4; i++) {
            int nx = xAtual + dx[i];
            int ny = yAtual + dy[i];

            if (eh_valido(nx, ny, linhas, colunas, mapa, visitado)) {
                visitado[nx][ny] = 1;
                
                // Enfileirar manual
                filaX[fim] = nx;
                filaY[fim] = ny;
                filaDist[fim] = dAtual + 1;
                fim++;
            }
        }
    }

    // Resultado final
    if (menorDistancia != -1) {
        printf("Apos correr %d metros e quase desistir por causa da distância, Rebeka conseguiu escapar!\n", menorDistancia);
    } else {
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }

    return 0;
}
