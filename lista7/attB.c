#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    char nome[100];
    int populacao;
    int perigo;
    char funcao[100];
} Cidadela;

// Função para deixar primeira maiúscula e resto minúsculo
void formatar(char *texto) {
    if (strlen(texto) == 0) return;

    texto[0] = toupper(texto[0]);
    for (int i = 1; texto[i]; i++) {
        texto[i] = tolower(texto[i]);
    }
}

// Comparação para ordenação
int comparar(const void *a, const void *b) {
    Cidadela *c1 = (Cidadela *)a;
    Cidadela *c2 = (Cidadela *)b;

    if (c1->populacao != c2->populacao)
        return c2->populacao - c1->populacao;

    if (c1->perigo != c2->perigo)
        return c2->perigo - c1->perigo;

    return strcmp(c1->nome, c2->nome);
}

int main() {
    Cidadela lista[100];
    int total = 0;

    char linha[201];
    int chave = -1;

    while (fgets(linha, 200, stdin)) {
        linha[strcspn(linha, "\n")] = 0;

        Cidadela atual;
        atual.populacao = 0;
        atual.perigo = 0;
        atual.nome[0] = '\0';
        atual.funcao[0] = '\0';

        int tem_exclamacao = 0;

        // Nome (letras maiúsculas)
        for (int i = 0; linha[i]; i++) {
            if (isupper(linha[i])) {
                int len = strlen(atual.nome);
                atual.nome[len] = linha[i];
                atual.nome[len + 1] = '\0';
            }
        }

        // População (números)
        for (int i = 0; linha[i]; i++) {
            if (isdigit(linha[i])) {
                atual.populacao = atual.populacao * 10 + (linha[i] - '0');
            }
        }

        // Periculosidade (*)
        for (int i = 0; linha[i]; i++) {
            if (linha[i] == '*') {
                atual.perigo++;
            }
        }

        // Verificar mensagem especial
        if (strchr(linha, '!')) {
            tem_exclamacao = 1;
            chave = atual.populacao;
        }

        // Função (duplo espaço)
        for (int i = 0; linha[i]; i++) {
            if (linha[i] == ' ' && linha[i+1] == ' ') {
                i += 2;

                int nova_palavra = 1;

                while (linha[i]) {
                    if (linha[i] == ' ') {
                        nova_palavra = 1;
                    } else {
                        if (nova_palavra && isalpha(linha[i])) {
                            int len = strlen(atual.funcao);
                            atual.funcao[len] = linha[i];
                            atual.funcao[len + 1] = '\0';
                            nova_palavra = 0;
                        }
                    }
                    i++;
                }
                break;
            }
        }

        // Só adiciona se não for mensagem especial
        if (!tem_exclamacao) {
            formatar(atual.nome);
            formatar(atual.funcao);

            lista[total++] = atual;
        }
    }

    if (chave == -1) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
        return 0;
    }

    // Ordena
    qsort(lista, total, sizeof(Cidadela), comparar);

    if (chave > total || chave <= 0) {
        printf("Gingrey ainda não foi achada, vamos esperar mais um pouco.\n");
        return 0;
    }

    Cidadela alvo = lista[chave - 1];

    printf("Gingrey foi encontrada em %s, uma cidadela com %d mil habitantes cuja função é %s e periculosidade ",
           alvo.nome, alvo.populacao, alvo.funcao);

    for (int i = 0; i < alvo.perigo; i++) {
        printf("*");
    }
    printf(".");

    int denso = alvo.populacao >= 1000;
    int perigoso = alvo.perigo > 3;

    if (denso && perigoso) {
        printf(" Talvez seja melhor desistir...\n");
    } else if (denso) {
        printf(" Um lugar denso, vai ser difícil achar ela.\n");
    } else if (perigoso) {
        printf(" Vai ser complicado entrar lá.\n");
    }

    return 0;
}
