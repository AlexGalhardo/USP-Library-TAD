/*
	Autores:
	Alex Galhardo
	Numero USP: 10408344

	Ian Castilho Caldeira Brant
	Numero USP: 10133967

	ICMC USP - São Carlos 2017
*/

#include "dinamico.h"

void criaBiblioteca(BIBLIOTECA *b){

	b->alunosCadastrados = 0;
	b->livrosCadastrados = 0;
	b->qtdEspera = 0;
	b->qtdEmail = 0;

	b->alunos = (LISTA_ALUNOS*)malloc(sizeof(LISTA_ALUNOS));
	b->alunos->inicio = NULL;

	b->espera = (LISTA_ESPERA*)malloc(sizeof(LISTA_ESPERA));
	b->espera->inicio = NULL;

	b->livros = (LISTA_LIVROS*)malloc(sizeof(LISTA_LIVROS));
	b->livros->inicio = NULL;

	b->pilha = (PILHA_EMAIL*)malloc(sizeof(PILHA_EMAIL));
	b->pilha->topo = NULL;
}

/*  função para inserir o nó livro na lista de livros */
void insereLivro(BIBLIOTECA *b, LIVRO *livro, int *erro){

	if(b->livros->inicio == NULL){
		b->livros->inicio = livro;
		*erro = 0;
	}
	else{
		livro->prox = b->livros->inicio;
		b->livros->inicio = livro;
		*erro = 0;
	}
}

void removeLivro(BIBLIOTECA *b, LIVRO *livro, int *erro){ 
	
	LIVRO *aux, *anterior, *proximo;
	aux = b->livros->inicio; 
	anterior = aux;

	*erro = 1; 

	if(aux == NULL){
		*erro = 1;
		return;
	}
	else{
		while(aux != NULL){ 
			if(aux->ISBN == livro->ISBN){
				*erro = 0; 

				if(b->livros->inicio->prox == NULL){
					free(aux);
					b->livros->inicio = NULL;
				}
				else{
					proximo = aux->prox;
					free(aux);
					anterior->prox = proximo;
				}
			}
			anterior = aux; 
			aux = aux->prox;
		}
	}
}

void removeAluno(BIBLIOTECA *b, ALUNO *aluno, int *erro){

	ALUNO *aux, *anterior, *proximo;
	aux = b->alunos->inicio; 
	anterior = aux;

	*erro = 1; 

	if(aux == NULL){
		*erro = 1;
		return;
	}
	else{
		while(aux != NULL){ 
			if(aux->numUSP == aluno->numUSP){
				*erro = 0; 

				if(b->alunos->inicio->prox == NULL){
					free(aux);
					b->alunos->inicio = NULL;
				}
				else{
					proximo = aux->prox;
					free(aux);
					anterior->prox = proximo;
				}
			}
			anterior = aux; 
			aux = aux->prox;
		}
	}
}

void insereAluno(BIBLIOTECA *b, ALUNO *aluno, int *erro){

	if(b->alunos->inicio == NULL){
		b->alunos->inicio = aluno;
		*erro = 0;
	}
	else{
		aluno->prox = b->alunos->inicio;
		b->alunos->inicio = aluno;
		*erro = 0;
	}
}


void verificaISBN(BIBLIOTECA *b, LIVRO *livro, int *ver){
	
	LIVRO *aux;
	aux = b->livros->inicio;

	*ver = 1;

	while(aux != NULL){
		if(aux->ISBN == livro->ISBN){
			*ver = 2;
			break;
		}
		aux = aux->prox;
	}
	free(aux);

	if(livro->ISBN < 1000 || livro->ISBN > 9999){
		*ver = 3;
	}
}


void verificaTitulo(BIBLIOTECA *b, LIVRO *livro, int *ver){
	
	*ver = 1;

	LIVRO *aux;
	aux = b->livros->inicio;

	while(aux != NULL){
		if(strcmp(aux->titulo, livro->titulo)==0){
			*ver = 2;
			break;
		}
		aux = aux->prox;
	}
	free(aux);
}

void verificaNumUSP(BIBLIOTECA *b, ALUNO *aluno, int *ver){
	
	ALUNO *aux;
	aux = b->alunos->inicio;

	*ver = 1;

	while(aux != NULL){
		if(aux->numUSP == aluno->numUSP){
			*ver = 2;
			break;
		}
		aux = aux->prox;
	}
	free(aux);

	if(aluno->numUSP < 10000000 || aluno->numUSP > 99999999){
		*ver = 3;
	}
}

void verificaEmail(BIBLIOTECA *b, ALUNO *aluno, int *ver){
	
	ALUNO *aux;
	aux = b->alunos->inicio;

	*ver = 1;

	while(aux != NULL){
		if(strcmp(aux->email, aluno->email)==0){
			*ver = 2;
			break;
		}
		aux = aux->prox;
	}
	free(aux);

	char verifica [7];
	strcpy(verifica, "@usp.br");

	int tamanho = strlen(aluno->email);
	int k;
	for(k=0; k < 7; k++){
		if(aluno->email[tamanho-7+k] != verifica[k]){
			*ver = 3;
			break;
		}
	}
}

void verificaTelefone(BIBLIOTECA *b, ALUNO *aluno, int *ver){
	
	ALUNO *aux;
	aux = b->alunos->inicio;

	*ver = 1;

	while(aux != NULL){
		if(strcmp(aux->telefone, aluno->telefone)==0){
			*ver = 2;
			break;
		}
	}
	free(aux);

	char verifica[6];
	strcpy(verifica, "551899");

	if(strlen(aluno->telefone)<13 || strlen(aluno->telefone)>13){
		*ver = 3;
	}

	int k;
	for(k=0; k< 6; k++){
		if(aluno->telefone[k] != verifica[k]){
			*ver = 4;
			break;
		}
	}
}

void verificaNome(BIBLIOTECA *b, ALUNO *aluno, int *ver){
	
	*ver = 1;

	ALUNO *aux;
	aux = b->alunos->inicio;

	while(aux != NULL){
		if(strcmp(aux->nome, aluno->nome)==0){
			*ver = 2;
			break;
		}
		aux = aux->prox;
	}
	free(aux);
}
