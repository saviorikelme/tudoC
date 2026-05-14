#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct catalogo {
    char nome[50];
    char genero[50];
    char estudio[50];
    char console[50];
    int nota;
    int ano;
} catalogo;

void funcaoAno(catalogo *cat, int n, int anoBusca) {
    int cont = 0;
    for(int i = 0; i < n; i++) {
        if(cat[i].ano == anoBusca) {
            printf("%s\n", cat[i].nome);
            cont++;
        }
    }
    if(cont > 0) printf("Tenho %d jogos || %d.\n", cont, anoBusca);
    else printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
}

void funcaoLetra(catalogo *cat, int n, char letra) {
    int cont = 0;
    for(int i = 0; i < n; i++) {
        if(cat[i].nome[0] == letra) {
            printf("%s\n", cat[i].nome);
            cont++;
        }
    }
    if(cont > 0) printf("Tenho %d jogos || %c.\n", cont, letra);
    else printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
}

void funcaoStudio(catalogo *cat, int n, char *estudioBusca) {
    int cont = 0;
    for(int i = 0; i < n; i++) {
        if(strcmp(cat[i].estudio, estudioBusca) == 0) {
            printf("%s\n", cat[i].nome);
            cont++;
        }
    }
    if(cont > 0) printf("Tenho %d jogos || %s.\n", cont, estudioBusca);
    else printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
}

void funcaoConsole(catalogo *cat, int n, char *consoleBusca) {
    int cont = 0;
    for(int i = 0; i < n; i++) {
        if(strcmp(cat[i].console, consoleBusca) == 0) {
            printf("%s\n", cat[i].nome);
            cont++;
        }
    }
    if(cont > 0) printf("Tenho %d jogos || %s.\n", cont, consoleBusca);
    else printf("Nenhum jogo tem esse parâmetro Sr Sr Wilson.\n");
}

void funcaoColecao(catalogo *cat, int n) {
    for(int i = 0; i < n; i++) {
        printf("%s %d\n", cat[i].nome, cat[i].nota);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    catalogo *cat = (catalogo *) malloc(n * sizeof(catalogo));
    
    for(int i = 0; i < n; i++) {
        scanf("%s %s %s %s %d %d", 
              cat[i].nome, cat[i].genero, cat[i].estudio, 
              cat[i].console, &cat[i].nota, &cat[i].ano);
        
        if(cat[i].nota > 7) {
            printf("AWESOME! Mais um GOTY pra minha coleção!\n");
        } else if(cat[i].nota < 4) {
            printf("Era melhor jogar mais um jogo de Mahjong.\n");
        }
    }
    
    char chamada[30];
    while(scanf("%s", chamada) != EOF) {
        if(strcmp(chamada, "printAno") == 0) {
            int ano;
            scanf("%d", &ano);
            funcaoAno(cat, n, ano);
        } else if(strcmp(chamada, "printLetra") == 0) {
            char l;
            scanf(" %c", &l);
            funcaoLetra(cat, n, l);
        } else if(strcmp(chamada, "printStudio") == 0) {
            char st[50];
            scanf("%s", st);
            funcaoStudio(cat, n, st);
        } else if(strcmp(chamada, "printConsole") == 0) {
            char cons[50];
            scanf("%s", cons);
            funcaoConsole(cat, n, cons);
        } else if(strcmp(chamada, "printColecao") == 0) {
            funcaoColecao(cat, n);
        }
    }
    
    printf("Enjoei de jogar, agora vou ver TV.\n");

    free(cat);
    return 0;
}
