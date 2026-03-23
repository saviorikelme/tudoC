#include <stdio.h>

int main()
{
    //declaração de algumas variaveis e scanf's iniciais
    int N, X, Y, Z;
    int W[2] = {07, 00};
    int latas_compradas = 0;
    int printou = 0;
    int comprador_especial = 0;
    
    scanf("%d", &N);
    scanf("%d", &X);
    scanf("%d", &Y);
    
    int horas_mais_latas[Y];
    int minutos_mais_latas[Y];
    int qtd_latas[Y];
    
    //para caso de compradores com mais de uma lata
    if(Y != 0){
        for(int i = 0; i < Y; i++){
        scanf("%d:%d %d", &horas_mais_latas[i], &minutos_mais_latas[i], &qtd_latas[i]);
        }
    }
    // logica principal
    for(int i = 1; i <= N; i++){
        // aumentando os minutos passados
        W[1] += 3;
        if(W[1] >= 60){
            W[0] += 1;
            W[1] = W[1] % 60;
        }
        // para caso ser a hora de um comprador com mais de 1 lata
        for(int j = 0; j < Y; j++){
            int guarda_hora = horas_mais_latas[j];
            int guarda_minuto = minutos_mais_latas[j];
            
            if(guarda_hora == W[0] && guarda_minuto == W[1]){
                comprador_especial = 1;
                break;
            }
        }
        // comprador normal ou comprador especial
        if(X > 0 && i % X == 0 && comprador_especial == 0){
            latas_compradas += 1;
        }else{
            for(int j = 0; j < Y; j++){
                int guarda_hora = horas_mais_latas[j];
                int guarda_minuto = minutos_mais_latas[j];
                
                if(guarda_hora == W[0] && guarda_minuto == W[1]){
                    latas_compradas += qtd_latas[j];
                    if(latas_compradas >= 50 && printou == 0){
                        printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou %d latas.", i, W[0], W[1], qtd_latas[j]);
                        printou = 1;
                        return 0;
                    }
                }
            }
        }
        // se bater a meta comprando apenas uma lata
        if(latas_compradas >= 50 && printou == 0){
            printf("Quem levou a cesta basica foi o %d* cliente atendido por coragem, as %02d:%02d. Que comprou 1 lata.", i, W[0], W[1]);
            printou = 1;
            return 0;
        }
        comprador_especial = 0;
    }
    // casos de falta de latas
    if(latas_compradas < 50){
        int faltas = 50 - latas_compradas;
        if(faltas == 1){
            printf("Ainda nao foram vendidas latas suficientes. Falta %d lata.", faltas);
        }else{
        printf("Ainda nao foram vendidas latas suficientes. Faltam %d latas.", faltas);
        }
    }
    return 0;
}
