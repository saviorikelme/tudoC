#include <stdio.h>

int verifica_pos(char letra, int posicao[2]) {
	if(letra == 'c') {
		if(posicao[0] -1 >= 0) {
			return 1;
		} else {
			return 0;
		}
	} else if(letra == 'b') {
		if(posicao[0] +1 <= 3) {
			return 1;
		} else {
			return 0;
		}
	} else if(letra == 'e') {
		if(posicao[1] -1 >= 0) {
			return 1;
		} else {
			return 0;
		}
	} else if(letra == 'd') {
		if(posicao[1] +1 <= 3) {
			return 1;
		} else {
			return 0;
		}
	}
	return 0;
}

int andadas(int cidade[4][4], char direcao[19], int posicao[2]) {
	for(int i = 0; i <= 19; i++) {

		if(direcao[i] == 'c') {
			if(verifica_pos(direcao[i], posicao) == 1) {
				cidade[posicao[0]-1][posicao[1]] += 1;
				posicao[0] -= 1;
			}


		}else if(direcao[i] == 'b') {
            if(verifica_pos(direcao[i], posicao) == 1){
                cidade[posicao[0]+1][posicao[1]] += 1;
			    posicao[0] += 1;
            }
		}else if(direcao[i] == 'd') {
		    if(verifica_pos(direcao[i], posicao) == 1){
		        cidade[posicao[0]][posicao[1]+1] += 1;
			    posicao[1] += 1;
		    }
			
		}else if(direcao[i] == 'e') {
		    if(verifica_pos(direcao[i], posicao) == 1){
    			cidade[posicao[0]][posicao[1]-1] += 1;
    			posicao[1] -= 1;
		    }
		}
	}
	
	int maior_num = 0;
	int coordenada[2] = {0};
	for(int i = 0; i <= 3; i++){
	    for(int j = 0; j <= 3; j++){
	        if(cidade[i][j] > maior_num){
	            maior_num = cidade[i][j];
	            coordenada[0] = i;
	            coordenada[1] = j;
	        }
	    }
	}
	int m = coordenada[0];
	int n = coordenada[1];
    
    printf("Coordenada X:%d, Y:%d", n, m);
    
	return 0;
}

int main()
{
	int matriz[4][4] = {0};
	char letra[20];
	int pos_atual[2] = {0};
	int m, n;
    
    for(int i = 0; i < 20; i++){
        scanf(" %c", &letra[i]);
    }

	andadas(matriz, letra, pos_atual);
	
    
	return 0;
}
