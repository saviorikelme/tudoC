#include <stdio.h>

int main() {
    long long n, a, b;

    scanf("%lld", &n);
    scanf("%lld %lld", &a, &b);

    long long soma_total = n * (n + 1) / 2;

    //soma a
    long long quant_multiplos_a = n / a;
    long long ultimo_mult_a = quant_multiplos_a * a;
    long long soma_mult_a = (a + ultimo_mult_a) * quant_multiplos_a / 2;

    //soma b
    long long quant_multiplos_b = n / b;
    long long ultimo_mult_b = quant_multiplos_b * b;
    long long soma_mult_b = (b + ultimo_mult_b) * quant_multiplos_b / 2;

    //soma ab
    long long ab = a * b;
    long long quant_mult_ab = n / ab;
    long long ultimo_mult_ab = quant_mult_ab * ab;
    long long soma_mult_ab = (ab + ultimo_mult_ab) * quant_mult_ab / 2;

    //resultado certo
    long long resultado = soma_total - (soma_mult_a + soma_mult_b - soma_mult_ab);

    printf("%lld\n", resultado);

    if (resultado % 2 == 0) {
        printf("Lá ele!!!\n");
    } else {
        printf("Opa xupenio AULAS...\n");
    }

    return 0;
}
