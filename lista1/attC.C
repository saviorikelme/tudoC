#include <stdio.h>

int main() {
    int total, px, py, pz;
    int investido = 0;
    int lucro_rebeka = 0;
    int possivel = 0;
    int a, b, c, sobra;

    // Entrada: total e porcentagens
    if (scanf("%d %d %d %d", &total, &px, &py, &pz) != 4) return 0;

    // 1. TENTATIVA 0: Divisão original (Rebeka investe 0)
    if ((total * px) % 100 == 0 && (total * py) % 100 == 0 && (total * pz) % 100 == 0) {
        a = (total * px) / 100;
        b = (total * py) / 100;
        c = (total * pz) / 100;
        lucro_rebeka = total - (a + b + c);
        printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
        possivel = 1;
    } 
    // 2. TENTATIVA 1: Investir 1 real
    else if (((total + 1) * px) % 100 == 0 && ((total + 1) * py) % 100 == 0 && ((total + 1) * pz) % 100 == 0) {
        a = ((total + 1) * px) / 100;
        b = ((total + 1) * py) / 100;
        c = ((total + 1) * pz) / 100;
        sobra = (total + 1) - (a + b + c);
        if (sobra >= 1 + 1) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
            investido = 1;
            lucro_rebeka = sobra - 1;
            possivel = 1;
        }
    }

    // Se ainda não for possível, tenta investir 2 reais
    if (!possivel && ((total + 2) * px) % 100 == 0 && ((total + 2) * py) % 100 == 0 && ((total + 2) * pz) % 100 == 0) {
        a = ((total + 2) * px) / 100;
        b = ((total + 2) * py) / 100;
        c = ((total + 2) * pz) / 100;
        sobra = (total + 2) - (a + b + c);
        if (sobra >= 2 + 1) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
            investido = 2;
            lucro_rebeka = sobra - 2;
            possivel = 1;
        }
    }

    // Se ainda não for possível, tenta investir 3 reais
    if (!possivel && ((total + 3) * px) % 100 == 0 && ((total + 3) * py) % 100 == 0 && ((total + 3) * pz) % 100 == 0) {
        a = ((total + 3) * px) / 100;
        b = ((total + 3) * py) / 100;
        c = ((total + 3) * pz) / 100;
        sobra = (total + 3) - (a + b + c);
        if (sobra >= 3 + 1) {
            printf("Cada homem ficou com %d, %d e %d reais, respectivamente\n", a, b, c);
            investido = 3;
            lucro_rebeka = sobra - 3;
            possivel = 1;
        }
    }

    // RESULTADO FINAL
    if (!possivel) {
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
        printf("E parece que Rebeka vai ter que voltar andando...\n");
    } else {
        // Desafios dos homens
        if (investido == 2) {
            char l1, l2, l3;
            scanf(" %c %c %c", &l1, &l2, &l3);
            printf("%d\n", (l1 - 'a' + 1) + (l2 - 'a' + 1) + (l3 - 'a' + 1));
        } 
        else if (investido == 3) {
            int i1, i2, i3;
            scanf("%d %d %d", &i1, &i2, &i3);
            if (i1 % 3 == 0 || i2 % 3 == 0 || i3 % 3 == 0) {
                printf("%d\n", (i1 / 3) + (i2 / 3) + (i3 / 3));
            }
        }

        // Verificação do transporte (3 reais iniciais + lucro obtido)
        if (3 + lucro_rebeka >= 7) {
            printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
        } else {
            printf("E parece que Rebeka vai ter que voltar andando...\n");
        }
    }

    return 0;
}
