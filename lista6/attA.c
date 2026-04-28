#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int **alocar_matriz(int L, int C){
    int **matriz = (int**) malloc(L * sizeof(int*));
    
    for (int i = 0; i < L; i++) {
        matriz[i] = (int*) malloc(C * sizeof(int));
    }
    
    return matriz;
}

void ler_matriz(int **matriz, int L, int C){
    for(int i = 0; i < L; i++){
        for(int j = 0; j < C; j++){
            scanf("%d", &matriz[i][j]);
        }
    }
}

void printar_matriz(int **matriz, int L, int C){
    for(int i = 0; i < L; i++){
        for(int j = 0; j < C; j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void liberar_matriz(int **matriz, int L){
    for (int i = 0; i < L; i++){
        free(matriz[i]);
    }
    free(matriz);
}

void dobro(int **matriz, int L, int C){
    for(int i = 0; i < L; i++){
        for(int j = 0; j < C; j++){
            matriz[i][j] = matriz[i][j] * 2;
        }
    }
    printar_matriz(matriz, L, C);
}

void quadrado(int **matriz, int L, int C){
    for(int i = 0; i < L; i++){
        for(int j = 0; j < C; j++){
            matriz[i][j] = pow(matriz[i][j], 2);
        }
    }
    printar_matriz(matriz, L, C);
}

void absoluto(int **matriz, int L, int C){
    for(int i = 0; i < L; i++){
        for(int j = 0; j < C; j++){
            matriz[i][j] = abs(matriz[i][j]);
        }
    }
    printar_matriz(matriz, L, C);
}

int main()
{
    int L, C, op;
    
    scanf("%d %d", &L, &C);
    
    int **matriz = alocar_matriz(L, C);
    ler_matriz(matriz, L, C);
    
    scanf("%d", &op);
    
    switch(op){
        case 1:
            dobro(matriz, L, C);
            break;
        case 2:
            quadrado(matriz, L, C);
            break;
        case 3:
            absoluto(matriz, L, C);
            break;
    }
    
    liberar_matriz(matriz, L);
    return 0;
}
