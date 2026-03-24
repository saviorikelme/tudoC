#include <stdio.h>
#include <string.h>

int main()
{ 
    // declaracao de variaveis e input inicial
    char s[101];
    int inicios[100];
    int fins[100];
    int palavras = 0;
    int pares = 0;
    
    fgets(s, 101, stdin);
    
    //retirando a leitura do enter(\n) do input
    
    int tam_string = 0;
    while (s[tam_string] != '\0') {
        if (s[tam_string] == '\n') {
            s[tam_string] = '\0';
            break;
        }
        tam_string++;
    }
    
    int i = 0;
    while (i < tam_string) {
        // pulando o que nao for letra
        while (i < tam_string && !((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))) {
            i++;
        }
        
        if (i < tam_string) {
            inicios[palavras] = i;
            // definindo inicios, fins e qtd de palavras
            while (i < tam_string && ((s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))) {
                i++;
            }
            fins[palavras] = i;
            palavras++;
        }
    }
    
    // criando a l�gica de comparar uma palavra com as proximas
    int tem_par = 0;

    for (int i = 0; i < palavras; i++) {
        for (int j = i + 1; j < palavras; j++) {
            
            int tam1 = fins[i] - inicios[i];
            int tam2 = fins[j] - inicios[j];

            if (tam1 == tam2) {
                int alfabeto[26];
                for(int k = 0; k < 26; k++) {
                    alfabeto[k] = 0;
                }
                                
                int e_anagrama = 1;

                // tranformando na primeira palavra maiuscula em minuscula e somando no vetor alfabeto
                for (int k = inicios[i]; k < fins[i]; k++) {
                    char c = s[k];
                    if (c >= 65 && c <= 90) c += 32;
                    alfabeto[c - 97]++; // 97 � 'a'
                }

                // a mesma coisa para segunda palavra, so que diminuindo no vetor alfabeto
                for (int k = inicios[j]; k < fins[j]; k++) {
                    char c = s[k];
                    if (c >= 65 && c <= 90) c += 32;
                    alfabeto[c - 97]--;
                }
                // se qualquer posicao do vetor tiver diferente de 0 nao e anagrama
                for (int k = 0; k < 26; k++) {
                    if (alfabeto[k] != 0) {
                        e_anagrama = 0;
                        break;
                    }
                }
                //  printando os possiveis anagramas
                if (e_anagrama) {
                    if (!tem_par) {
                        printf("Pares de anagramas encontrados:\n");
                        tem_par = 1;
                    }
                    for (int k = inicios[i]; k < fins[i]; k++){
                        printf("%c", s[k]);
                    }
                    printf(" e ");
                    for (int k = inicios[j]; k < fins[j]; k++){
                        printf("%c", s[k]);
                    } 
                    printf("\n");
                    pares++;
                }
            }
        }
    }
    // prints se tiver pares ou nao tiver pares
    if (tem_par) {
        printf("\nTotal de pares: %d\n", pares);
    } else {
        printf("Nao existem anagramas na frase.\n");
    }

    return 0;
}
