#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parametros(int argc, char *argv[], char **eventos, char **solicitacoes, char **boletos1, char **boletos2, char **saida){
	int x = 0;
	
	while(x<argc){
		if (strcmp("-e",argv[x])==0){
			x++;
			*eventos = (char *)malloc((strlen(argv[x])+1)*sizeof(char));
			strcpy(*eventos,argv[x]);
		}
		else if (strcmp("-si",argv[x])==0){
			x++;
			*solicitacoes = (char *)malloc((strlen(argv[x])+1)*sizeof(char));
			strcpy(*solicitacoes,argv[x]);
		}
		else if (strcmp("-b1",argv[x])==0){
			x++;
			*boletos1 = (char *)malloc((strlen(argv[x])+1)*sizeof(char));
			strcpy(*boletos1,argv[x]);
		}
		else if (strcmp("-b2",argv[x])==0){
			x++;
			*boletos2 = (char *)malloc((strlen(argv[x])+1)*sizeof(char));
			strcpy(*boletos2,argv[x]);
		}
		else if (strcmp("-o",argv[x])==0){
			x++;
			*saida = (char *)malloc((strlen(argv[x])+1)*sizeof(char));
			strcpy(*saida,argv[x]);
		}
		x++;
	}
}

void prepara_string(char ** caminho){
	int tamanho = strlen(*caminho), x = 0, posicao = 0;
	char temp[256], letra[2];
	
	strcpy(temp, *caminho);
	
	for (x = 0; x < tamanho; x++){
		strncpy(letra, temp + x, 1);
		if (strcmp("\\", letra)==0)
			posicao = x;
		if (strcmp("/", letra)==0)
			posicao = x;
	}
	
	if (posicao > 0){
		posicao++;
		strncpy(temp, *caminho+posicao, tamanho);
	}
		
	strcpy(*caminho, temp);
}

void prepara_saida(char ** caminho, char ** solicitacoes, char **saida){
	char *temp = NULL;
	
	*caminho = (char *)malloc((strlen(*solicitacoes)+1)*sizeof(char)); 
	strcpy(*caminho, *solicitacoes); //caminho recebe valor recebido no parametro -si
	
	prepara_string(caminho); //funcao remove diretorios informados no parametro -si deixando apenas o nome do arquivo com sua extensao
	
	temp = (char *)malloc((strlen(*caminho)+1)*sizeof(char));
	strcpy(temp, *caminho);
	*caminho = (char *)malloc((strlen(temp)+strlen(*saida)+2)*sizeof(char));
	sprintf(*caminho,"%s/%s",*saida,temp);
}

void troca_extensao(char ** antigo, char ** novo, char *extensao){
	char *temp = NULL;
	int tamanho;
	temp = (char *)malloc((strlen(*antigo)+2)*sizeof(char));
	tamanho = strlen(*antigo);
	strncpy(temp, *antigo, tamanho);
	temp[tamanho-2] = '\0';	
	strcat(temp, extensao);
	*novo = temp;
}

int verifica_caractere(char *linha){
	int tamanho = strlen(linha), x = 0, posicao = 0;
	char letra[2];
	
	for (x = 0; x < tamanho; x++){
		strncpy(letra, linha + x, 1);
		if (strcmp(":", letra)==0)
			posicao = x;
	}
	
	if (posicao > 0){
		return posicao;
	}
	else 	
		return 0;
}
