#include <stdio.h>

// Função para aplicar os enfeites ao redor de um poste específico
void aplicar_enfeites(int m, int n, char matriz[m][n], char resultado[m][n], int linha, int coluna) {
    // Percorre a vizinhança 3x3 ao redor do poste (linha, coluna)
    for (int di = -1; di <= 1; di++) {
        for (int dj = -1; dj <= 1; dj++) {
            
            int ni = linha + di;  // Nova linha vizinha
            int nj = coluna + dj; // Nova coluna vizinha

            // 1. Verifica se a posição está dentro dos limites da matriz
            // 2. Garante que não estamos tentando alterar a própria posição do poste (di=0, dj=0)
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && (di != 0 || dj != 0)) {
                
                // Só altera se a posição original era um espaço vazio '-'
                if (matriz[ni][nj] == '-') {
                    
                    // Se for vizinho direto (cima, baixo, esquerda ou direita)
                    if (di == 0 || dj == 0) {
                        resultado[ni][nj] = '+';
                    } 
                    // Se for diagonal (e ainda não tiver um '+' lá)
                    else if (resultado[ni][nj] != '+') {
                        resultado[ni][nj] = 'x';
                    }
                }
            }
        }
    }
}

int main() {
    int m, n;

    if (scanf("%d %d", &m, &n) != 2) return 0;

    char matriz[m][n];
    char resultado[m][n];

    // Leitura e inicialização
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf(" %c", &matriz[i][j]);
            resultado[i][j] = matriz[i][j];
        }
    }

    // Varre a matriz em busca de postes 'P'
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] == 'P') {
                aplicar_enfeites(m, n, matriz, resultado, i, j);
            }
        }
    }

    // Impressão da matriz resultante
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c", resultado[i][j]);
        }
        printf("\n");
    }

    return 0;
}
