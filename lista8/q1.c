#include <stdio.h>

//union
typedef union {
    unsigned char rawByte; //bit bruto

    //acesso da struct
    struct {
        unsigned char erro    : 1;
        unsigned char modo    : 3;
        unsigned char leitura : 4;
    } campos;
} SensorStatus;

int main() {
    int n;
    scanf("%d", &n); //entrada

    //declaracao de uma union e atribuicao no bitbruto
    SensorStatus status;
    
    status.rawByte = (unsigned char)n;

    printf("Byte bruto: %d | Erro: %d | Modo: %d | Leitura: %d\n",
           status.rawByte,
           status.campos.erro,
           status.campos.modo,
           status.campos.leitura);
           
    return 0;
}
