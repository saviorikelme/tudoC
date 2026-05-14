#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Protótipos e Estruturas ---
typedef struct Mecha Mecha;

typedef struct {
    char nome[30];
    int atrib1; 
    int atrib2;
    void (*subrotina)(Mecha *m, int slot, int input, int *output);
} SubSistema;

struct Mecha {
    int id;
    char modelo[50];
    int energia_atual;
    int num_sistemas;
    int valor_wintermute;
    SubSistema sistemas[]; // Flexible Array Member (FAM)
};

// --- Funções de Lógica (Subrotinas) ---

void logica_defesa(Mecha *m, int slot, int input, int *output) {
    int dano = input - m->sistemas[slot].atrib1 - (slot * m->sistemas[slot].atrib2);
    if (dano < 0) dano = 0;
    *output = dano;
}

void logica_utilidade(Mecha *m, int slot, int input, int *output) {
    int recuperado = m->sistemas[slot].atrib1 + (slot * m->sistemas[slot].atrib2);
    m->energia_atual += recuperado;
    *output = m->energia_atual;
}

void logica_ataque(Mecha *m, int slot, int input, int *output) {
    if (m->energia_atual < m->sistemas[slot].atrib2) {
        *output = -1; // Sinalizador de energia insuficiente
    } else {
        int dano = m->sistemas[slot].atrib1 + m->energia_atual + slot - input;
        m->energia_atual -= m->sistemas[slot].atrib2;
        *output = dano;
    }
}

// --- Programa Principal ---

int main() {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    // Vetor de ponteiros para armazenar o esquadrão
    Mecha **esquadrao = (Mecha **)malloc(N * sizeof(Mecha *));

    for (int i = 0; i < N; i++) {
        int id, energia, Q;
        char modelo[50];
        
        scanf("%d %s %d %d", &id, modelo, &energia, &Q);

        // Alocação ÚNICA (Chassi + Sistemas) usando FAM
        size_t tamanho_total = sizeof(Mecha) + (Q * sizeof(SubSistema));
        Mecha *novo = (Mecha *)malloc(tamanho_total);

        novo->id = id;
        strcpy(novo->modelo, modelo);
        novo->energia_atual = energia;
        novo->num_sistemas = Q;

        // Leitura dos subsistemas e atribuição dos ponteiros de função
        for (int j = 0; j < Q; j++) {
            char tipo;
            scanf(" %c %s %d %d", &tipo, novo->sistemas[j].nome, 
                  &novo->sistemas[j].atrib1, &novo->sistemas[j].atrib2);

            if (tipo == 'D') novo->sistemas[j].subrotina = logica_defesa;
            else if (tipo == 'U') novo->sistemas[j].subrotina = logica_utilidade;
            else if (tipo == 'A') novo->sistemas[j].subrotina = logica_ataque;
        }
        
        scanf("%d", &novo->valor_wintermute);
        esquadrao[id] = novo; // Armazena na posição do ID para facilitar ordenação
    }

    // --- Relatório de Missão ---
    printf("[RELATORIO DE MISSÃO: OPERAÇÃO LANÇA DE NETUNO]\n");

    for (int i = 0; i < N; i++) {
        Mecha *m = esquadrao[i];
        printf("ID: %d | MECHA: %s | ENERGIA: %d\n", m->id, m->modelo, m->energia_atual);

        int output_val;

        // Fase de Combate: Prioridade D -> U -> A
        // Execução via comparação de ponteiros de função
        
        // 1. Defesa
        for (int j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == logica_defesa) {
                m->sistemas[j].subrotina(m, j, m->valor_wintermute, &output_val);
                printf("-> [DEFESA] %s | Dano final sofrido: %d\n", m->sistemas[j].nome, output_val);
            }
        }

        // 2. Utilidade
        for (int j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == logica_utilidade) {
                m->sistemas[j].subrotina(m, j, m->valor_wintermute, &output_val);
                printf("-> [UTILIDADE] %s | Energia atual: %d\n", m->sistemas[j].nome, output_val);
            }
        }

        // 3. Ataque
        for (int j = 0; j < m->num_sistemas; j++) {
            if (m->sistemas[j].subrotina == logica_ataque) {
                m->sistemas[j].subrotina(m, j, m->valor_wintermute, &output_val);
                if (output_val == -1) {
                    printf("-> [ATAQUE] %s | Energia insuficiente!\n", m->sistemas[j].nome);
                } else {
                    printf("-> [ATAQUE] %s | Dano causado: %d | Energia restante: %d\n", 
                           m->sistemas[j].nome, output_val, m->energia_atual);
                }
            }
        }

        printf("ENERGIA FINAL: %d\n", m->energia_atual);
        printf("-----------------------------------------\n");
    }

    printf("Esquadrao pronto para o combate.\n");

    // Limpeza de memória
    for (int i = 0; i < N; i++) free(esquadrao[i]);
    free(esquadrao);

    return 0;
}
