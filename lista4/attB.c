#include <stdio.h>

int main()
{
	int m, n;

	scanf("%d %d", &m, &n);

	char parede[m][n];

	for(int i = 0; i < m; i++) {
		for(int j = 0; j < n; j++) {
			scanf(" %c", &parede[i][j]);
		}
	}
	for(int linha_atual = 0; linha_atual < m; linha_atual++) {
		int prox_linha = linha_atual+1;
		for(int coluna_atual = 0; coluna_atual < n; coluna_atual++) {
			char simbolo_atual = parede[linha_atual][coluna_atual];
            
			if(simbolo_atual == 'o') {
				if(parede[prox_linha][coluna_atual] == '#') {
					for (int i = coluna_atual; i > 0; i--) {

                        if (parede[prox_linha][i] == '#') {
                            parede[linha_atual][i-1] = 'o';
                            if (parede[prox_linha][i-1] == '.' && prox_linha < m) {
                                parede[prox_linha][i-1] = 'o';
                            }
                        } else {
                            break; 
                        }
                    }
					for (int i = coluna_atual; i < n - 1; i++) {
                        if (parede[prox_linha][i] == '#') {
                            parede[linha_atual][i+1] = 'o';
                        } else {
                            break; 
                        }
                    }
				} else {
					if(prox_linha < m) {
						parede[prox_linha][coluna_atual] = 'o';
					}
				}
			}

		}
		for(int i = 0; i < n; i++) {
			printf("%c", parede[linha_atual][i]);
		}
		printf("\n");
	}
	return 0;
}
