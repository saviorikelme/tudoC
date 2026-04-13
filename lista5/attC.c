#include <stdio.h>
#include <stdlib.h>

int main()
{
    long long int n;
    int *p = (int *) malloc(1 * sizeof(long long int));
    int entradas = 0;
    
    while(scanf("%d", &n) != EOF){
        entradas++;
        
        p = (int *) realloc(p, entradas * sizeof(long long int));
        
        p[entradas - 1] = n;
    }
    
    printf("Mais um bom dia de trabalho!\n");
    
    for(int i = 0; i < entradas; i++){
        if(p[i] % 2 == 1){
            printf("%d\n", p[i]);
        }
    }
    
    for(int i = 0; i < entradas; i++){
        if(p[i] % 2 == 0){
            printf("%d\n", p[i]);
        }
    }
    
    printf("Vou visitar esses lugares de novo... algum dia.\n");
    
    return 0;
}
