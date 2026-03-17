#include <stdio.h>

int main() {
    int N, K, P;
    scanf("%d %d %d", &N, &K, &P);

    int primeiro = -1, Q = 0;

    for (int i = N; i < K; i++) {
        if (i == 0 || i == 1) {
            if (P == 0) { // 0 e 1 tecnicamente têm 0 fatores primos ímpares
                if (primeiro == -1) primeiro = i;
                else Q++;
            }
            continue;
        }

        int temp = i;
        int contP = 0;
        int valido = 1; // Flag: 1 para válido, 0 para inválido

        // Ignora o fator par 2
        while (temp % 2 == 0) temp /= 2;

        // Testa divisores ímpares
        for (int d = 3; d * d <= temp; d += 2) {
            if (temp % d == 0) {
                temp /= d;
                if (temp % d == 0) { // Se ainda for divisível, há repetição!
                    valido = 0;
                    break;
                }
                contP++;
            }
        }
        
        // Se sobrou algo no temp > 1, esse resto é um primo ímpar
        if (temp > 1) contP++;

        // Verifica se atende aos critérios
        if (valido && contP == P) {
            if (primeiro == -1) {
                primeiro = i;
            } else {
                Q++;
            }
        }
    }

    if (primeiro != -1) {
        printf("%d %d\n", primeiro, Q);
    } else {
        printf("Poxa dudinha, me desculpa, nao achei os numeros mas vou te mandar uma foto de um gatinho fofo.\n");
    }

    return 0;
}
