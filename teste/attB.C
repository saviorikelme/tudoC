#include <stdio.h>
 
int main() {
    double raio;
    scanf("%lf", &raio);
    double volume = (4.0/3)*3.14159*(raio*raio*raio);
    printf("VOLUME = %.3f", volume);

    return 0;
}
