#include <stdio.h>
#include <string.h>

int main() {
    int R;
    scanf("%d", &R);

    // Buffer para a string gigante (1000 casos * 60 leds + 1000 ornamentos)
    char gigante[70000];
    gigante[0] = '\0';

    for (int i = 0; i < R; i++) {
        char leds[65];
        int F;
        scanf("%s %d", leds, &F);

        // --- L�gica de Clocks (Ripple Counter) ---
        int n = 0;
        while (leds[n] != '\0') n++; // Mede o tamanho sem strlen

        for (int f = 0; f < F; f++) {
            for (int j = 0; j < n; j++) {
                char estado_anterior = leds[j];
                
                // Inverte o estado atual
                leds[j] = (leds[j] == 'O') ? 'X' : 'O';

                // S� propaga a mudan�a se o LED atual foi DESLIGADO (O -> X)
                // Se ele ligou (X -> O), a "onda" de choque para aqui.
                if (!(estado_anterior == 'O' && leds[j] == 'X')) {
                    break;
                }
            }
        }

        // Imprime o resultado individual conforme o formato de sa�da
        printf("%s\n", leds);

        // --- L�gica da Luz Gigante ---
        if (i == 0) {
            // Primeiro caso: apenas copia para a gigante
            int k = 0;
            while (leds[k] != '\0') {
                gigante[k] = leds[k];
                k++;
            }
            gigante[k] = '\0';
        } else {
            // Casos subsequentes: calcula ornamento e anexa
            int tam_g = 0;
            while (gigante[tam_g] != '\0') tam_g++;

            char ultimo_g = gigante[tam_g - 1];
            char primeiro_novo = leds[0];
            char ornamento;

            // Decis�o do ornamento baseada nas regras de Soneca
            if (tam_g % 2 == 0) { // Tamanho Par
                ornamento = (ultimo_g == primeiro_novo) ? '@' : '$';
            } else { // Tamanho �mpar
                ornamento = (ultimo_g == primeiro_novo) ? '#' : '%';
            }

            // Adiciona o ornamento
            gigante[tam_g] = ornamento;
            
            // Adiciona o novo fio de LEDs ap�s o ornamento
            int k = 0;
            while (leds[k] != '\0') {
                gigante[tam_g + 1 + k] = leds[k];
                k++;
            }
            gigante[tam_g + 1 + k] = '\0';
        }
    }

    // Imprime a jun��o final de todos os testes
    printf("%s\n", gigante);

    return 0;
}
