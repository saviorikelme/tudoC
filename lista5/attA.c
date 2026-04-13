#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fazer_uma_rodada(char* str) {
    int len = strlen(str);
    char* nova = (char*)malloc(len + 1);

    int i = 0, j = 0;
    int mudou = 0;

    while (i < len) {
        if (i + 1 < len && str[i] == str[i + 1]) {
            // fusão
            if (str[i] == 'z') {
                nova[j++] = 'a';
            } else {
                nova[j++] = str[i] + 1;
            }
            i += 2; // pula o par
            mudou = 1;
        } else {
            nova[j++] = str[i];
            i++;
        }
    }

    nova[j] = '\0';
    strcpy(str, nova);
    free(nova);

    return mudou;
}

void algoritmo_fusao_total(char* str) {
    while (fazer_uma_rodada(str));
}

int main() {
    int n;
    scanf("%d", &n);

    char** entrada = malloc(n * sizeof(char*));
    int* comp = malloc(n * sizeof(int));

    int total = 0, max_len = 0;

    for (int i = 0; i < n; i++) {
        entrada[i] = malloc(1005);
        scanf("%s", entrada[i]);

        comp[i] = strlen(entrada[i]);
        total += comp[i];

        if (comp[i] > max_len)
            max_len = comp[i];
    }

    char* merged = malloc(total + 1);
    int pos = 0;

    // Mesclagem
    for (int c = 0; c < max_len; c++) {
        for (int l = 0; l < n; l++) {
            if (c < comp[l]) {
                merged[pos++] = entrada[l][c];
            }
        }
    }

    merged[pos] = '\0';

    printf("%s\n", merged);

    // Fusão por rodadas
    algoritmo_fusao_total(merged);

    printf("%s\n", merged);

    // Free
    for (int i = 0; i < n; i++) free(entrada[i]);
    free(entrada);
    free(comp);
    free(merged);

    return 0;
}
