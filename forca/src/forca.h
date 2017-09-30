#ifndef _forca_h
#define _forca_h

	typedef struct {
		char nome[15];
		int tamanho;
	}palavra;

	typedef struct {
		char nome[21];
		int erros;
	}jogador;

	void inicia_player(jogador *);
	void menu(char *);
	void escolhePalavra(FILE *, palavra *);
	void desenhaForca(char *, int);
	void adicionaPalavra(char *, char *);
	void imprimePalavra(palavra *, int *);
	int tentativa(jogador *, int *, palavra *, char *);
	int testaPalavra(int *, int);

#endif
