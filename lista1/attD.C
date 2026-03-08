#include <stdio.h>

int main() {
    int x, y, c;
    int dest_x, dest_y;
    int q_atual;

    if (scanf("%d %d %d", &x, &y, &c) != 3) return 0;

    // Determina quadrante atual e o ponto (1,1) do quadrante diagonal (destino)
    if (x > 0 && y > 0) {
        q_atual = 1; dest_x = -1; dest_y = -1;
    } else if (x < 0 && y > 0) {
        q_atual = 2; dest_x = 1; dest_y = -1;
    } else if (x < 0 && y < 0) {
        q_atual = 3; dest_x = 1; dest_y = 1;
    } else if (x > 0 && y < 0) {
        q_atual = 4; dest_x = -1; dest_y = 1;
    } else {
        printf("caminhada invalida\n");
        return 0;
    }

    // Distâncias absolutas sem usar funções externas
    int dx = (dest_x > x) ? (dest_x - x) : (x - dest_x);
    int dy = (dest_y > y) ? (dest_y - y) : (y - dest_y);

    // Lógica de decisão baseada no quadrante a evitar (c)
    // Se o quadrante a evitar compartilha o eixo X com o atual, move-se em Y primeiro para "subir/descer" e fugir dele.
    // Se compartilha o eixo Y, move-se em X primeiro para "ir pros lados" e fugir dele.
    
    if (q_atual == 1) { // Adjacentes: 2 (eixo Y) e 4 (eixo X)
        if (c == 2) printf("%d passos em y e %d passos em x\n", dy, dx);
        else if (c == 4) printf("%d passos em x e %d passos em y\n", dx, dy);
        else printf("caminhada invalida\n");
    } 
    else if (q_atual == 2) { // Adjacentes: 1 (eixo X) e 3 (eixo Y)
        if (c == 1) printf("%d passos em x e %d passos em y\n", dx, dy);
        else if (c == 3) printf("%d passos em y e %d passos em x\n", dy, dx);
        else printf("caminhada invalida\n");
    }
    else if (q_atual == 3) { // Adjacentes: 2 (eixo X) e 4 (eixo Y)
        if (c == 2) printf("%d passos em x e %d passos em y\n", dx, dy);
        else if (c == 4) printf("%d passos em y e %d passos em x\n", dy, dx);
        else printf("caminhada invalida\n");
    }
    else if (q_atual == 4) { // Adjacentes: 1 (eixo Y) e 3 (eixo X)
        if (c == 1) printf("%d passos em x e %d passos em y\n", dx, dy);
        else if (c == 3) printf("%d passos em y e %d passos em x\n", dy, dx);
        else printf("caminhada invalida\n");
    }

    return 0;
}
