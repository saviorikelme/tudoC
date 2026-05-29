#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 256
#define SPECIE_LEN 50

// Estrutura para armazenar cada registro do arquivo Iris
typedef struct {
    double sepal_length;
    double sepal_width;
    double petal_length;
    double petal_width;
    char species[SPECIE_LEN];
} IrisRecord;

// Estrutura auxiliar para contar a frequência das espécies (Moda)
typedef struct {
    char name[SPECIE_LEN];
    int count;
} SpeciesCount;

// Função para processar um único arquivo CSV
void processarArquivo(const char *filename) {
    FILE *file = fopen(filename, "r+"); // Abre para leitura e escrita (append posterior)
    if (file == NULL) {
        printf("Erro ao abrir o arquivo: %s\n", filename);
        return;
    }

    printf("\n==================================================\n");
    printf("Conteudo do arquivo: %s\n", filename);
    printf("==================================================\n");

    char line[MAX_LINE_LEN];
    
    // Ignora e exibe o cabeçalho
    if (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    } else {
        printf("Arquivo vazio ou formato invalido.\n");
        fclose(file);
        return;
    }

    IrisRecord *records = NULL;
    int capacity = 0;
    int count = 0;

    // Leitura dinâmica linha por linha
    while (fgets(line, sizeof(line), file) != NULL) {
        // Exibe a linha lida no terminal conforme solicitado
        printf("%s", line);

        // Remove a quebra de linha se houver
        line[strcspn(line, "\n")] = '\0';

        // Expande o vetor dinamicamente usando realloc
        if (count >= capacity) {
            capacity = (capacity == 0) ? 4 : capacity * 2;
            IrisRecord *temp = realloc(records, capacity * sizeof(IrisRecord));
            if (temp == NULL) {
                printf("Erro de alocacao de memoria.\n");
                free(records);
                fclose(file);
                return;
            }
            records = temp;
        }

        // Faz o parsing dos dados separados por vírgula (CSV)
        int parsed = sscanf(line, "%lf,%lf,%lf,%lf,%49s",
                            &records[count].sepal_length,
                            &records[count].sepal_width,
                            &records[count].petal_length,
                            &records[count].petal_width,
                            records[count].species);

        if (parsed == 5) {
            count++;
        }
    }

    if (count == 0) {
        printf("\nNenhum dado valido encontrado em %s.\n", filename);
        free(records);
        fclose(file);
        return;
    }

    // --- CÁLCULOS ESTATÍSTICOS ---

    // 1. Médias
    double sum_sl = 0, sum_sw = 0, sum_pl = 0, sum_pw = 0;
    for (int i = 0; i < count; i++) {
        sum_sl += records[i].sepal_length;
        sum_sw += records[i].sepal_width;
        sum_pl += records[i].petal_length;
        sum_pw += records[i].petal_width;
    }
    double mean_sl = sum_sl / count;
    double mean_sw = sum_sw / count;
    double mean_pl = sum_pl / count;
    double mean_pw = sum_pw / count;

    // 2. Moda (Espécie mais frequente com desempate lexicográfico)
    SpeciesCount *s_counts = NULL;
    int unique_species = 0;

    for (int i = 0; i < count; i++) {
        int found = 0;
        for (int j = 0; j < unique_species; j++) {
            if (strcmp(records[i].species, s_counts[j].name) == 0) {
                s_counts[j].count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            unique_species++;
            s_counts = realloc(s_counts, unique_species * sizeof(SpeciesCount));
            strcpy(s_counts[unique_species - 1].name, records[i].species);
            s_counts[unique_species - 1].count = 1;
        }
    }

    // Encontrar a moda respeitando os critérios de desempate
    int max_idx = 0;
    for (int j = 1; j < unique_species; j++) {
        if (s_counts[j].count > s_counts[max_idx].count) {
            max_idx = j;
        } else if (s_counts[j].count == s_counts[max_idx].count) {
            // Em caso de empate, priorizar menor ordem lexicográfica (strcmp < 0)
            if (strcmp(s_counts[j].name, s_counts[max_idx].name) < 0) {
                max_idx = j;
            }
        }
    }
    char moda_especie[SPECIE_LEN];
    strcpy(moda_especie, s_counts[max_idx].name);

    // --- GRAVAÇÃO DOS RESULTADOS NO FINAL DO ARQUIVO ---
    
    // Move o ponteiro do arquivo para o fim para garantir a anexação correta
    fseek(file, 0, SEEK_END);

    fprintf(file, "\n--- Estatisticas ---\n");
    fprintf(file, "Media sepal_length: %.2f\n", mean_sl);
    fprintf(file, "Media sepal_width: %.2f\n", mean_sw);
    fprintf(file, "Media petal_length: %.2f\n", mean_pl);
    fprintf(file, "Media petal_width: %.2f\n", mean_pw);
    fprintf(file, "Moda especie: %s\n", moda_especie);

    printf("\nEstatisticas gravadas com sucesso no arquivo %s!\n", filename);

    // Liberação de memória e fechamento do arquivo atual
    free(records);
    free(s_counts);
    fclose(file); 
}

int main() {
    int total_arquivos;

    printf("Digite a quantidade total de arquivos CSV a processar: ");
    if (scanf("%d", &total_arquivos) != 1 || total_arquivos <= 0) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    // Processa os arquivos sequencialmente (um por vez)
    for (int i = 1; i <= total_arquivos; i++) {
        char filename[30];
        // Gera dinamicamente o nome como iris1.csv, iris2.csv, etc.
        sprintf(filename, "iris%d.csv", i); 
        processarArquivo(filename);
    }

    printf("\nProcessamento concluido para todos os arquivos.\n");
    return 0;
}
