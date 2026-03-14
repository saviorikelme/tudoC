#include <stdio.h>

int main() {
    char letra;
    
    scanf("%c", &letra);

    int n = letra - 'A';

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < n - i; j++) {
            printf(".");
        }

        for (int j = 0; j <= i; j++) {
            printf("%c", 'A' + j);
        }

        for (int j = i - 1; j >= 0; j--) {
            printf("%c", 'A' + j);
        }

        for (int j = 0; j < n - i; j++) {
            printf(".");
        }

        printf("\n");
    }
    return 0;
}
