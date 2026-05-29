#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef union {
    uint32_t raw_data; 
    struct {
        uint32_t id : 10;
        uint32_t status : 3; 
        uint32_t bateria : 1; 
        int32_t  temperatura : 12;
        uint32_t paridade : 6; 
    } bitfield;
} pacote;

int main() {
    int capacidade = 2;
    int contador = 0;
    
    pacote *pacotes = (pacote *) malloc(capacidade * sizeof(contador));

    uint32_t input;

    while (scanf("%x", &input) == 1 && input != 0) {
        
        if (contador >= capacidade) {
            capacidade *= 2;
            pacote *temp = (pacote *) realloc(pacotes, capacidade * sizeof(pacote));
            pacotes = temp;
        }

        pacotes[contador].raw_data = input;
        contador++;
    }
    for (int i = 0; i < contador; i++) {
        printf("Pacote [%d] - Dado Bruto: 0x%08X\n", i + 1, pacotes[i].raw_data);
        printf("ID do Sensor : %u\n", pacotes[i].bitfield.id);
        printf("Status : %u\n", pacotes[i].bitfield.status);
        printf("Bateria Baixa: %s\n", pacotes[i].bitfield.bateria ? "SIM (ALERTA)" : "Nao");
        printf("Temperatura : %d graus\n", pacotes[i].bitfield.temperatura);
        printf("------------------------------------\n");
    }

    free(pacotes);

    return 0;
}
