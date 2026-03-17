#include <stdio.h>
#include <stdlib.h>

int main() {
    int xupenio_num, n_canais;
    
    if (scanf("%d %d", &xupenio_num, &n_canais) != 2) return 0;

    int melhor_canal = -1;
    int melhor_minuto = -1;
    long long melhor_distancia = -1;
    int melhor_soma_vip = 0;
    long long melhor_termo = -1;

    for (int i = 1; i <= n_canais; i++) {
        long long f_ant = 0; // f(i-2)
        long long f_atual = 0; // f(i-1)
        long long f1, f2;
        scanf("%lld %lld", &f1, &f2);

        for (int minuto = 1; ; minuto++) {
            long long termo_agora;
            
            // Define o termo do minuto atual
            if (minuto == 1) termo_agora = f1;
            else if (minuto == 2) {
                termo_agora = f2;
                f_ant = f1;
                f_atual = f2;
            } else {
                termo_agora = f_ant + f_atual;
                f_ant = f_atual;
                f_atual = termo_agora;
            }

            long long dist_agora = llabs(termo_agora - xupenio_num);

            // Lógica de atualização com as regras de desempate:
            int atualiza = 0;
            if (melhor_canal == -1) {
                atualiza = 1;
            } else if (dist_agora < melhor_distancia) {
                atualiza = 1;
            } else if (dist_agora == melhor_distancia) {
                // Se no mesmo canal (i == melhor_canal), o 'minuto' atual é maior,
                // e a regra diz: se distâncias iguais no mesmo canal, pegue o menor termo.
                // Como a sequência é crescente, o menor termo sempre apareceu antes (minuto menor).
                // Portanto, se i == melhor_canal, NÃO atualizamos (mantemos o anterior).
                
                // Se canais diferentes: pegue o canal de índice maior.
                if (i > melhor_canal) {
                    atualiza = 1;
                }
            }

            if (atualiza) {
                melhor_distancia = dist_agora;
                melhor_canal = i;
                melhor_minuto = minuto;
                melhor_termo = termo_agora;
                
                // Calcula VIP apenas do vencedor atual
                int soma = 0;
                long long temp = termo_agora;
                while (temp > 0) {
                    soma += temp % 10;
                    temp /= 10;
                }
                melhor_soma_vip = soma;
            }

            // Condição de parada: se o termo já passou muito o alvo, paramos o canal.
            if (termo_agora > xupenio_num && dist_agora > melhor_distancia) {
                break;
            }
            // Segurança para evitar loops infinitos em sequências nulas
            if (minuto > 1000) break;
        }
    }

    if (melhor_soma_vip > 10) {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d e com o VIP garantido!!!\n", melhor_canal, melhor_minuto);
    } else {
        printf("Xupenio, para ir ao lulupalooza vc deve entrar no canal %d e sera chamado mais ou menos no minuto %d, mas o ingresso VIP não vai rolar :(\n", melhor_canal, melhor_minuto);
    }

    return 0;
}
