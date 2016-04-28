#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct No{
	char nome[16];
	char matricula[12];
	char UID[12];
	char presente;
	struct No *proximo;
};

void inserir(struct No **ultimo, struct No **inicio, struct No *novo){

	if((*ultimo) != NULL){
		novo->proximo = (*ultimo)->proximo;
		(*ultimo)->proximo = novo;
		(*ultimo) = novo;
		return;
	}

	novo->proximo = NULL;
	(*ultimo) = novo;
	(*inicio) = novo;
}

void imprimir(struct No *lista){

	FILE *arq = fopen("saida.txt", "w");

	fprintf(arq, "UID\tNOME\tMATRICULA\tFREQ\n");

	while(lista != NULL){
		
		fprintf(arq, "%s\t%s\t%s\t", lista->UID, lista->nome, lista->matricula);

		if(lista->presente == '1'){
			fprintf(arq, "P\n");
		}
		else{
			fprintf(arq, "F\n");
		}

		printf("%s  %s  %s\n", lista->UID, lista->nome, lista->matricula);

		lista = lista->proximo;

	}

	fclose(arq);
}

void buscar(struct No **lista, char *uid){
	
	struct No *temp = (struct No *) malloc(sizeof(struct No));
	temp = *lista;
	
	while(lista != NULL){
		
		if(!strcmp(temp->UID, uid)){
			printf("\nExiste!\nNome: %s\nMatricula: %s\n\n", temp->nome, temp->matricula);
			temp->presente = '1';
			return;
		}

		temp = temp->proximo;

	}

	printf("\nNao Existe!\n");
	temp->presente = '0';
}

int main(int argc, char **argv){

	FILE *entrada;
	struct No *inicio = NULL, *ultimo = NULL;
	struct No *novo = (struct No *) malloc(sizeof(struct No));

	char uid[12] = "12 BB AB CC";

	if(argc != 2){
		printf("\nPasse como parametro o arquivo de entrada\n");
		return 1;
	}

	entrada =  fopen (argv[1], "r");

	if(!entrada){
		printf("\nArquivo nao existe!\n");
		return 2;
	}

	while(!feof(entrada)){
		novo = (struct No *) malloc(sizeof(struct No));
		fgets(novo->UID, 12, entrada);
		fscanf(entrada, "\n%s", novo->nome);
		fscanf(entrada, "\n%s\n\n", novo->matricula);
		inserir(&ultimo, &inicio, novo);
	}

	buscar(&inicio, uid); //dayvid
	strcpy(uid, "AA A1 42 FF");//luan
	buscar(&inicio, uid);
	strcpy(uid, "B2 11 14 FA");//sostenes
	buscar(&inicio, uid);
	strcpy(uid, "12 AA BB CC");//wed
	buscar(&inicio, uid);
	
	imprimir(inicio);
	
	/*
	strcpy(uid, "AA 2F 4B FF");
	buscar(inicio, uid);
	strcpy(uid, "12 AA BB CC");
	buscar(inicio, uid);
	*/
	fclose(entrada);

	return 0;
}
