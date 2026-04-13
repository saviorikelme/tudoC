#include <stdio.h>
#include <stdlib.h>

//media
float calcular_media(float *p, int alunos) {

	int i = 0;
	float soma = 0;
	float media = 0;

	while(i < alunos) {
		soma += p[i];
		i++;
	}

	media = soma / alunos;

	return media;
}

//maior nota
float calcular_maior_nota(float *p, int alunos) {

	float maior_nota = 0;

	for(int i = 0; i < alunos; i++) {
		if(p[i] > maior_nota) {
			maior_nota = p[i];
		}
	}

	return maior_nota;
}

//aluno da maior nota
int descobrir_aluno_maior_nota(float *p, int alunos, float maior_nota) {

	for(int i = 0; i < alunos; i++) {
		if(p[i] == maior_nota) {
			return i + 1;
		}
	}
}

//menor nota
float calcular_menor_nota(float *p, int alunos) {

	float menor_nota = 10;

	for(int i = 0; i < alunos; i++) {
		if(p[i] < menor_nota) {
			menor_nota = p[i];
		}
	}

	return menor_nota;
}

//aluno da menor nota
int descobrir_aluno_menor_nota(float *p, int alunos, float menor_nota) {

	for(int i = 0; i < alunos; i++) {
		if(p[i] == menor_nota) {
			return i + 1;
		}
	}
}

// qtd de alunos acima da media
int qtd_alunos_acima_media(float *p, int alunos, float media) {
	int alunos_acima_media = 0;

	for(int i = 0; i < alunos; i++) {
		if(p[i] > media) {
			alunos_acima_media++;
		}
	}
	return alunos_acima_media;
}

//mediana
float calcular_mediana(float *p, int alunos) {

	float mediana = 0;

	float *copia = (float *) malloc(alunos * sizeof(float));

	for(int i = 0; i < alunos; i++) {
		copia[i] = p[i];
	}

	int crescente = 0;
	while(!crescente) {

		int trocas = 0;

		for(int i = 0; i < alunos - 1; i++) {
			if(copia[i] > copia[i+1]) {
				float temp = copia[i];
				copia[i] = copia[i+1];
				copia[i+1] = temp;
				trocas++;
			}
		}
		if(trocas == 0) {
			crescente = 1;
		}
	}

	if(alunos % 2 == 0) {
		mediana = (copia[(alunos-1)/2] + copia[((alunos-1)/2) + 1]) / 2;
	} else {
		mediana = copia[((alunos-1)/2)];
	}

	free(copia);

	return mediana;
}

//moda
float calcular_moda(float *p, int alunos) {

	float moda = 11;
	int max_repeticao = 0;

	for(int i = 0; i < alunos; i++) {
		int repeticao = 0;

		for(int j = i+1; j < alunos; j++) {
			if(p[i] == p[j]) {
				repeticao++;
			}
		}

		if(repeticao > max_repeticao) {
			moda = p[i];
			max_repeticao = repeticao;

		}else if(repeticao == max_repeticao && moda != 11){
		    moda = 11;
		}
	}
	return moda;
}


int main()
{
    //declaracoes iniciais
	int n, k;

	scanf("%d", &n);

	float *p = (float *) malloc(n * sizeof(float));

	for(int i = 0; i < n; i++) {
		scanf(" %f", &p[i]);
	}
    
    //chamada das funcoes
	float media = calcular_media(p, n);
	float maior_nota = calcular_maior_nota(p, n);
	int aluno_maior_nota = descobrir_aluno_maior_nota(p, n, maior_nota);
	float menor_nota = calcular_menor_nota(p, n);
	int aluno_menor_nota = descobrir_aluno_menor_nota(p, n, menor_nota);
	int alunos_acima_media = qtd_alunos_acima_media(p, n, media);
	float mediana = calcular_mediana(p, n);
	float moda = calcular_moda(p, n);
    
    //prints
	printf("Relatorio inicial\n");
	printf("Media: %.2f\n", media);
	printf("Maior nota: %.2f (aluno %d)\n", maior_nota, aluno_maior_nota);
	printf("Menor nota: %.2f (aluno %d)\n", menor_nota, aluno_menor_nota);
	printf("Acima da media: %d\n", alunos_acima_media);
	printf("Mediana: %.2f\n", mediana);
	
	if(moda != 11){
	    printf("Moda: %.2f\n\n", moda);
	}else{
	    printf("Moda: Nao ha moda unica\n\n");
	}
	
    //repeticao do processo para o relatorio atualizado
	scanf("%d", &k);

	p = (float *) realloc(p, (n+k) * sizeof(float));

	for(int i = n; i < n + k; i++) {
		scanf(" %f", &p[i]);
	}

	media = calcular_media(p, n + k);
	maior_nota = calcular_maior_nota(p, n + k);
	aluno_maior_nota = descobrir_aluno_maior_nota(p, n + k, maior_nota);
	menor_nota = calcular_menor_nota(p, n + k);
	aluno_menor_nota = descobrir_aluno_menor_nota(p, n + k, menor_nota);
	alunos_acima_media = qtd_alunos_acima_media(p, n + k, media);
	mediana = calcular_mediana(p, n + k);
	moda = calcular_moda(p, n + k);
	
	printf("Relatorio atualizado\n");
	printf("Media: %.2f\n", media);
	printf("Maior nota: %.2f (aluno %d)\n", maior_nota, aluno_maior_nota);
	printf("Menor nota: %.2f (aluno %d)\n", menor_nota, aluno_menor_nota);
	printf("Acima da media: %d\n", alunos_acima_media);
	printf("Mediana: %.2f\n", mediana);

    if(moda != 11){
	    printf("Moda: %.2f", moda);
	}else{
	    printf("Moda: Nao ha moda unica");
	}
	
	return 0;
}
