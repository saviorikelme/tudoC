#include <stdio.h>
#include <stdlib.h>

int main() {
    int q;
    scanf("%d", &q);

    int pos = 0;
    int primeiro = 1;
    int veioDeB = 0; // NOVO

    for (int i = 0; i < q; i++) {
        int X;
        char C;
        scanf("%d %c", &X, &C);

        if (C == 'D') {

            for (int j = 0; j < pos; j++) {
                printf(" ");
            }

            int pontos;

            if (primeiro) {
                if (veioDeB) {
                    pontos = X + 1;
                    pos += X;
                } else {
                    pontos = X;
                    pos = X - 1;
                }
                primeiro = 0;
            } else {
                // ALTERA��O AQUI
                if (veioDeB) {
                    pontos = X + 1;
                } else {
                    pontos = X + 1;
                }
                pos += X;
            }

            for (int j = 0; j < pontos; j++) {
                printf(".");
            }

            printf("\n");

            veioDeB = 0; // reset

        } else if (C == 'E') {

            if (pos - X < 0) {
                printf("Informacao invalida\n");
                return 0;
            }

            pos -= X;

            for (int j = 0; j < pos; j++) {
                printf(" ");
            }

            for (int j = 0; j < X + 1; j++) {
                printf(".");
            }

            printf("\n");

            veioDeB = 0; // reset

        } else if (C == 'B') {

            int linhas;

            if (i == q - 1) {
                linhas = X;
            } else {
                linhas = X - 1;
            }

            for (int k = 0; k < linhas; k++) {
                for (int j = 0; j < pos; j++) {
                    printf(" ");
                }
                printf(".\n");
            }

            veioDeB = 1; // ? MARCA que veio de B
        }
    }

    return 0;
}
