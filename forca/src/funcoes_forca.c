#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
		char nome[15];
		int tamanho;
	}palavra;

	typedef struct {
		char nome[21];
		int erros;
	}jogador;

void menu(char *caminho){
	int opc;
	do{
		printf("\n\tMenu\n");
		printf("1 - Animal\n");
		printf("2 - Profissão\n");
		printf("3 - Esporte\n");
		scanf(" %d", &opc);
		printf("\n");
	}while((opc > 3)||(opc < 1));
	switch(opc){
		case 1:
				strcpy(caminho, "../palavras/animais.txt");
			break;
		case 2:
				strcpy(caminho, "../palavras/profissoes.txt");
			break;
		case 3:
				strcpy(caminho, "../palavras/esportes.txt");
			break;
	}
}

void inicia_player(jogador *p){
	printf("Entre com o nome do jogador: ");
	scanf(" %20[^\n]s", p->nome);
	printf("\n");
	p->erros = 0;
}

void escolhePalavra(FILE *entrada, palavra *p){
	int cont1 = 0, cont2 = 1, tamanho;

	fscanf(entrada," %*s");
	cont1++;
	while(!feof(entrada)){
		fscanf(entrada," %*s");
		cont1++;
	}

	srand(time(NULL));
	rewind (entrada);
	tamanho = rand()%cont1+1;
	fscanf(entrada, " %20[^\n]s", p->nome);
	while(cont2<tamanho){
		fscanf(entrada, " %20[^\n]s", p->nome);
		cont2++;
	}
	p->tamanho = strlen(p->nome);

	fclose(entrada);
}

void desenhaForca(char *nome, int erros){
	printf("Jogador: %s\n", nome);
	switch(erros){
		case 0:
			printf("\t\t*****\n");
			printf("\t\t|   |\n");
			printf("\t\t|\n");
			printf("\t\t|\n");
			printf("\t\t|\n");
			printf("\t\t|\n");
			printf("\t__M_____Z____M____\n");
			break;
		case 1:
			printf("\t\t*****\n");
			printf("\t\t|   |\n");
			printf("\t\t|   O\n");
			printf("\t\t|\n");
			printf("\t\t|\n");
			printf("\t\t|\n");
			printf("\t__M_____Z____M____\n");
			break;
		case 2:
			printf("\t\t*****\n");
			printf("\t\t|   |\n");
			printf("\t\t|   O\n");
			printf("\t\t|   |\n");
			printf("\t\t|\n");
			printf("\t\t|\n");
			printf("\t__M_____Z____M____\n");
			break;
		case 3:
			printf("\t\t*****\n");
			printf("\t\t|   |\n");
			printf("\t\t|   O\n");
			printf("\t\t|  /|\n");
			printf("\t\t|\n");
			printf("\t\t|\n");
			printf("\t__M_____Z____M____\n");
			break;
		case 4:
			printf("\t\t*****\n");
			printf("\t\t|   |\n");
			printf("\t\t|   O\n");
			printf("\t\t|  /|\\\n");
			printf("\t\t|\n");
			printf("\t\t|\n");
			printf("\t__M_____Z____M____\n");
			break;
		case 5:
			printf("\t\t*****\n");
			printf("\t\t|   |\n");
			printf("\t\t|   O\n");
			printf("\t\t|  /|\\\n");
			printf("\t\t|  /\n");
			printf("\t\t|\n");
			printf("\t__M_____Z____M____\n");
			break;
		case 6:
			printf("\t\t*****\n");
			printf("\t\t|   |\n");
			printf("\t\t|   O\n");
			printf("\t\t|  /|\\\n");
			printf("\t\t|  / \\\n");
			printf("\t\t|\n");
			printf("\t__M_____Z____M____\n");
			break;
	}
}

void imprimePalavra(palavra *p, int *vetor){
	int cont;
	printf("\n\t\tPALAVRA\n\t\t");
	for(cont = 0; cont < p->tamanho; cont++){
		if(vetor[cont] == 0){
			printf("_ ");
		}
		else{
			printf("%c ", p->nome[cont]);
		}
	}
	printf("\n");
}

void adicionaPalavra(char *palavra, char *caminho){
	char palavraLida[15];
	FILE *entrada;
	entrada = fopen(caminho, "a+");

	fscanf(entrada, " %s", palavraLida);
	if(!strcmp(palavra, palavraLida)){
		fclose(entrada);	
		return;
	}
	while(!feof(entrada)){
		fscanf(entrada, " %s", palavraLida);
		if(!strcmp(palavra, palavraLida)){
			fclose(entrada);
			return;
		}
	}

	rewind(entrada);
	fprintf(entrada, "%s\n", palavra);
	fclose(entrada);
}

int testaPalavra(int *vetor, int tam){
	int cont;
	for(cont = 0; cont < tam; cont++){
		if(vetor[cont] == 0){
			return 0;
		}
	}
	return 1;
}

int tentativa(jogador *player, int *vetor, palavra *p, char *caminho){
	char palavra[15], letra, opc;
	int cont;
	FILE *entrada;

	printf("%s entre com uma letra: ", player->nome);
	scanf(" %c", &letra);

	if(strchr(p->nome, tolower(letra))){
		for(cont = 0; cont < p->tamanho; cont++){
			if(p->nome[cont] == tolower(letra)){
				vetor[cont] = 1;
			}
		}
		if(testaPalavra(vetor, p->tamanho)){
			return 1;
		}
	}
	else{
		printf("A letra \"%c\" não pertence à palavra!\n", tolower(letra));
		player->erros++;
		if(player->erros == 6){
			return 2;
		}
	}
	imprimePalavra(p, vetor);

	do{
		printf("Deseja chutar a palavra?(S/N): ");
		scanf(" %c", &opc);
		printf("\n");
		if(toupper(opc) == 'S'){
			printf("Entre com a palavra: ");
			scanf(" %s", palavra);
			printf("\n");

			int cont;
			for(cont = 0; cont < strlen(palavra); cont++){
				palavra[cont] = tolower(palavra[cont]);
			}

			if(!strcmp(p->nome, palavra)){
				return 1;
			}
			else{
				printf("\t\tPalavra errada\n");
				player->erros++;
				adicionaPalavra(palavra, caminho);
				if(player->erros == 6){
					return 2;
				}
			}
		}
	}while((toupper(opc) != 'N') && (toupper(opc) != 'S'));
	return 0;
}
