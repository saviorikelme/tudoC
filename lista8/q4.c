#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Produto;

typedef struct {
    int codigo;
    char tipo;
    int qtd_mov;
} Movimento;

int main() {
    FILE *f_prod = fopen("produtos.txt", "r");
    FILE *f_mov = fopen("movimentos.txt", "r");

    if (f_prod == NULL || f_mov == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    // 1. Carregar produtos para um array (supondo um máximo de 100 produtos)
    Produto lista[100];
    int total_produtos = 0;
    while (fscanf(f_prod, "%d %s %d %f", &lista[total_produtos].codigo, 
                  lista[total_produtos].nome, &lista[total_produtos].quantidade, 
                  &lista[total_produtos].preco) != EOF) {
        total_produtos++;
    }
    fclose(f_prod);

    // 2. Variáveis para o relatório
    int mov_sucesso = 0, saidas_recusadas = 0, cod_inexistente = 0;
    char inconsistencias[2000] = ""; // Buffer para armazenar mensagens de erro
    char estoque_baixo[1000] = "";

    // 3. Processar movimentos
    Movimento m;
    while (fscanf(f_mov, "%d %c %d", &m.codigo, &m.tipo, &m.qtd_mov) != EOF) {
        int encontrado = -1;
        for (int i = 0; i < total_produtos; i++) {
            if (lista[i].codigo == m.codigo) {
                encontrado = i;
                break;
            }
        }

        if (encontrado == -1) {
            cod_inexistente++;
            sprintf(inconsistencias + strlen(inconsistencias), "%d %c %d PRODUTO_INEXISTENTE\n", m.codigo, m.tipo, m.qtd_mov);
        } else {
            if (m.tipo == 'E') {
                lista[encontrado].quantidade += m.qtd_mov;
                mov_sucesso++;
            } else if (m.tipo == 'S') {
                if (lista[encontrado].quantidade >= m.qtd_mov) {
                    lista[encontrado].quantidade -= m.qtd_mov;
                    mov_sucesso++;
                } else {
                    saidas_recusadas++;
                    sprintf(inconsistencias + strlen(inconsistencias), "%d %c %d ESTOQUE_INSUFICIENTE\n", m.codigo, m.tipo, m.qtd_mov);
                }
            }
        }
    }
    fclose(f_mov);

    // 4. Gerar estoque_atualizado.txt e coletar Estoque Baixo
    FILE *f_atualizado = fopen("estoque_atualizado.txt", "w");
    for (int i = 0; i < total_produtos; i++) {
        fprintf(f_atualizado, "%d %s %d %.2f\n", lista[i].codigo, lista[i].nome, lista[i].quantidade, lista[i].preco);
        
        if (lista[i].quantidade <= 5) {
            sprintf(estoque_baixo + strlen(estoque_baixo), "%d %s %d\n", lista[i].codigo, lista[i].nome, lista[i].quantidade);
        }
    }
    fclose(f_atualizado);

    // 5. Gerar relatorio.txt
    FILE *f_rel = fopen("relatorio.txt", "w");
    fprintf(f_rel, "PRODUTOS PROCESSADOS: %d\n", total_produtos);
    fprintf(f_rel, "MOVIMENTOS APLICADOS: %d\n", mov_sucesso);
    fprintf(f_rel, "SAIDAS RECUSADAS: %d\n", saidas_recusadas);
    fprintf(f_rel, "MOVIMENTOS SEM CADASTRO: %d\n", cod_inexistente);
    fprintf(f_rel, "\nESTOQUE BAIXO:\n%s", estoque_baixo);
    fprintf(f_rel, "\nINCONSISTENCIAS:\n%s", inconsistencias);
    fclose(f_rel);

    return 0;
}
