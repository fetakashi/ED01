#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/* -e testes/e/ev001.ev -si testes/i/ing002.si -b1 boletospg1.bp -b2 boletospg2.bp -o saida -rsi 0 10 -rgi 0 10
 run this program using the console pauser or add your own getch, system("pause") or input loop */
struct Eventos{
	char evento[15];
	int qtd;
};
struct Pessoas
{
	char nome[128];
	char cpf[30];
	char endereco[256];
	struct Eventos eventos[100];
};

int main(int argc, char *argv[]) {
	char *eventos = NULL, *solicitacoes = NULL, *boletos1 = NULL, *boletos2 = NULL, *saida = NULL; //parametros iniciais
	char *boletos = NULL, *ingressos = NULL, *carta = NULL, *caminho = NULL; //baseados nos parametros -si e -o
	char bol[] = "bol";
	char ing[] = "ing";
	char car[] = "ci";
	
	parametros(argc, argv, &eventos, &solicitacoes, &boletos1, &boletos2, &saida);
	printf("Arquivo eventos: %s\n", eventos); printf("Arquivo solicitacoes de ingresso: %s\n", solicitacoes); printf("Arquivo boletos pagos no primeiro prazo: %s\n", boletos1); printf("Arquivo boletos pagos no segundo prazo: %s\n", boletos2); printf("Diretorio saida: %s\n", saida);
	
	prepara_saida(&caminho, &solicitacoes, &saida);
	prepara_saida(&caminho, &boletos1, &saida);
	prepara_saida(&caminho, &boletos2, &saida);
	troca_extensao(&caminho, &boletos, bol);
	troca_extensao(&caminho, &ingressos, ing);
	troca_extensao(&caminho, &carta, car);
	printf("Diretorio saida arquivo boletos: %s\n", boletos); printf("Diretorio saida arquivo ingressos: %s\n", ingressos); printf("Diretorio saida arquivo carta: %s\n", carta);
	
	FILE *arq_eventos, *arq_solicitacoes, *arq_boletos, *arq_carta, *arq_pagos1, *arq_pagos2;
	arq_eventos = fopen(eventos, "r"); arq_solicitacoes = fopen(solicitacoes, "r"); arq_boletos = fopen(boletos, "w"); arq_carta = fopen(carta, "w"); arq_pagos1 = fopen(boletos1, "w+"); arq_pagos1 = fopen(boletos2, "w+");
	if (arq_eventos == NULL) {
		printf("Erro de leitura no arquivo eventos.\n");
	} else{
		printf("Arquivo eventos aberto em modo leitura.\n");
	}
	if (arq_solicitacoes == NULL) {
		printf("Erro de leitura no arquivo solicitacoes de ingresso.\n");
	} else{
		printf("Arquivo solicitacoes de ingresso aberto em modo leitura.\n");
	}
	if (arq_boletos == NULL) {
		printf("Erro de leitura no arquivo boletos.\n");
	} else{
		printf("Arquivo boletos aberto em modo escrita.\n");
	}
	if (arq_carta == NULL) {
		printf("Erro de leitura no arquivo cartas de indeferimento.\n");
	} else{
		printf("Arquivo cartas de indeferimento aberto em modo escrita.\n");
	}
	if (arq_pagos1 == NULL) {
		printf("Erro de leitura no arquivo boletos pagos no primeiro prazo.\n");
	} else{
		printf("Arquivo boletos pagos no primeiro prazo aberto em modo leitura e escrita.\n");
	}
	if (arq_pagos2 == NULL) {
		printf("Erro de leitura no arquivo boletos pagos no segundo prazo.\n");
	} else{
		printf("Arquivo boletos pagos no segundo prazo aberto em modo leitura e escrita.\n");
	}
	
	char linha[256], qtd[10];
	int quantidade = 0, contador = 0, iterador = 0, posicao;
	struct Pessoas pessoa;
	while(fgets(linha, 256, arq_solicitacoes) != NULL)
	{
		if (contador == 0){
			quantidade = atoi(linha);
			contador++;
		} else if (contador == 1){
			strcpy(pessoa.nome, linha);
			contador++;
		} else if (contador == 2){
			strcpy(pessoa.cpf, linha);
			contador++;
		} else if (contador == 3){
			strcpy(pessoa.endereco, linha);
			contador++;
		} else if (contador > 3){
			if (strcmp("=\n",linha)==0){
				contador = 1;
				iterador = 0;
				printf("%s\n", pessoa.nome);
				printf("%s\n", pessoa.cpf);
				printf("%s\n", pessoa.endereco);
				printf("%s\n", pessoa.eventos[0].evento);
				printf("%d\n", pessoa.eventos[0].qtd);
				printf("===============================================\n");
			} else if (strcmp("#\n",linha)==0){
				break;
			} else if (strcmp("#",linha)==0){
				break;
			} else {
				posicao = verifica_caractere(linha);
				memset(pessoa.eventos[iterador].evento,0,strlen(pessoa.eventos[iterador].evento));
				memset(qtd,0,strlen(qtd));
				strncpy(pessoa.eventos[iterador].evento, linha, posicao);
				strncpy(qtd, linha+posicao+1, strlen(linha));
				pessoa.eventos[iterador].qtd=atoi(qtd);
				iterador++;
				contador++;
			}
			
		}
		
	}
	printf("%d\n", contador);
	
	return 0;
}
