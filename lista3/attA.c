#include <stdio.h>

int main() {
    int T, N;

    // Lendo a quantidade de casos de teste
    if (scanf("%d", &T) != 1) return 0;

    for (int i = 1; i <= T; i++) {
        if (scanf("%d", &N) != 1) break;

        int vetor[N];
        for (int j = 0; j < N; j++) {
            scanf("%d", &vetor[j]);
        }

        int maior_seq = 0;
        int maior_inicio = 0;
        
        int atual_seq = 1; 
        int atual_inicio = 0;

        for (int j = 1; j < N; j++) {
            if (vetor[j] < vetor[j - 1]) {
                atual_seq++;
            } else {
                if (atual_seq >= 2 && atual_seq > maior_seq) {
                    maior_seq = atual_seq;
                    maior_inicio = atual_inicio;
                }
                atual_seq = 1;
                atual_inicio = j;
            }
        }

        // verifica sequência que termina no final
        if (atual_seq >= 2 && atual_seq > maior_seq) {
            maior_seq = atual_seq;
            maior_inicio = atual_inicio;
        }

        if (maior_seq < 2) {
            printf("0\n");
        } else {
            printf("%d\n", maior_seq);
            for (int k = maior_inicio; k < maior_inicio + maior_seq; k++) {
                printf("%d", vetor[k]);
                if (k < maior_inicio + maior_seq) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }

    return 0;
}
