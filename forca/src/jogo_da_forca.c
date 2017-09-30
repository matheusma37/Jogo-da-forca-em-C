#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<locale.h>
#include "forca.h"

int main(){
	setlocale(LC_ALL, "");
	jogador player1, player2;
	palavra p;
	int *vetor, tentativaP1, tentativaP2;
	FILE *entrada;
	char caminho[30], opc;

	printf("\t\tBEM VINDO AO JOGO DA FORCA\n\n");

	do{
		inicia_player(&player1);
		inicia_player(&player2);

		menu(caminho);
		if((entrada = fopen(caminho, "r")) == NULL){
			printf("Falha ao abrir o arquivo em %s!\n Verifique o arquivo e tente novamente...\n", caminho);
			exit(1);
		}

		tentativaP1 = 0;
		tentativaP2 = 0;

		escolhePalavra(entrada, &p);
		vetor = (int *)calloc(p.tamanho, sizeof(int));
	
		do{
			desenhaForca(player1.nome, player1.erros);
			desenhaForca(player2.nome, player2.erros);
			imprimePalavra(&p, vetor);

			tentativaP1 = tentativa(&player1, vetor, &p, caminho);
			if(tentativaP1 != 0){
				if(tentativaP1 = 1){
					printf("\t\tPARABÉNS %s VOCÊ VENCEU!!!\n\n", player1.nome);
					break;
				}else if(tentativaP1 = 2){
						printf("\t\tPARABÉNS %s VOCÊ VENCEU!!!\n\n", player2.nome);
						break;
					}
				imprimePalavra(&p, vetor);
			}

			tentativaP2 = tentativa(&player2, vetor, &p, caminho);
			if(tentativaP2 != 0){
				if(tentativaP2 = 1){
					printf("\t\tPARABÉNS %s VOCÊ VENCEU!!!\n\n", player2.nome);
					break;
				}else if(tentativaP2 = 2){
						printf("\t\tPARABÉNS %s VOCÊ VENCEU!!!\n\n", player1.nome);
						break;
					}
				imprimePalavra(&p, vetor);
			}
		}while(1);
		free(vetor);

		do{
			printf("Deseja jogar novamente?(S/N): ");
			scanf(" %c", &opc);
		}while((toupper(opc) != 'N') && (toupper(opc) != 'S'));
	}while(toupper(opc) != 'N');
	printf("\n\t\tGAME OVER\n");
	return 0;
}
