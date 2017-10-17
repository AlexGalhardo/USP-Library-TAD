/*
	Autores:
	Alex Galhardo
	Numero USP: 10408344

	Ian Castilho Caldeira Brant
	Numero USP: 10133967

	ICMC USP - São Carlos 2017
*/

#ifndef DINAMICO_H_INCLUDED
#define DINAMICO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX 101
#define TEL 14 
#define USP 9
#define MSG 200

/* dados e lista de alunos */
typedef struct noa{
	char nome[MAX];
	int numUSP;
	char telefone[TEL];
	char email[MAX];
	int emprestados;
	struct noa *prox;
}ALUNO;

typedef struct{
	ALUNO *inicio;
}LISTA_ALUNOS;

/* dados e lista de livros */
typedef struct nol{
	char titulo[MAX];
	char autor[MAX];
	int ISBN;
	char editora[MAX];
	int ano;
	int edicao;
	int copias;
	struct nol *prox;
}LIVRO;

typedef struct{
	LIVRO *inicio;
}LISTA_LIVROS;


/* dados que ira entrar na espera e na pilha de email */ 
typedef struct noe{
	int numUSP;
	char nome[MAX];
	int ISBN;
	char titulo[MAX];
	char mensagem[MSG];
	struct noe *prox;
}DADOS;

typedef struct{
	DADOS *inicio;
}LISTA_ESPERA;
 
typedef struct{
	DADOS *topo;
}PILHA_EMAIL;

/* STRUCT PRINCIPAL DO PROGRAMA */
typedef struct{
	LISTA_ALUNOS *alunos;
	LISTA_LIVROS *livros;
	LISTA_ESPERA *espera;
	PILHA_EMAIL *pilha;
	int livrosCadastrados;
	int alunosCadastrados;
	int qtdEspera;
	int qtdEmail;
}BIBLIOTECA;

/* cria a biblioteca */
void criaBiblioteca(BIBLIOTECA *b);

/* mostrar menu de escolhas para o usuário escolher*/
void mostrarMenu();

/* função responsável pelas realização das funções da biblioteca */
void menu(int op, BIBLIOTECA *b, int *erro);

/* verifica se os dados inseridos para o livro são válidos */
void verificaISBN(BIBLIOTECA *b, LIVRO *livro, int *ver);
void verificaTitulo(BIBLIOTECA *b, LIVRO *livro, int *ver);

void buscaISBN(BIBLIOTECA *b, LIVRO *livro, int ISBN, int *erro);
void buscaNumUSP(BIBLIOTECA *B, ALUNO *aluno, int numUSP, int *erro);

/* verifica se os dados inseridos para o aluno são válidos */
void verificaTelefone(BIBLIOTECA *b, ALUNO *aluno, int *ver);
void verificaEmail(BIBLIOTECA *b, ALUNO *aluno, int *ver);
void verificaNome(BIBLIOTECA *b, ALUNO *aluno, int *ver);
void verificaNumUSP(BIBLIOTECA *b, ALUNO *aluno, int *ver);

/* mostrar dados de algum aluno ou de algum livro especifico */
void mostrarDadosAluno(ALUNO *aluno);
void mostrarDadosLivro(LIVRO *livro);
void mostrarDadosEmail(DADOS *dados);

/* cadastrar livros e alunos na biblioteca */
void cadastrarLivro(BIBLIOTECA *b);
void insereLivro(BIBLIOTECA *b, LIVRO *livro, int *erro);
void cadastrarAluno(BIBLIOTECA *b);
void removeAluno(BIBLIOTECA *b, ALUNO *aluno, int *erro);
void insereAluno(BIBLIOTECA *b, ALUNO *aluno, int *erro);

/* descadastra livro ou aluno especifico da biblioteca */
void descadastrarLivro(BIBLIOTECA *b);
void descadastrarAluno(BIBLIOTECA *b);

/* funcões principais da biblioteca --> retirar ou devolver livro */
void retirarLivro(BIBLIOTECA *b);
void removeLivro(BIBLIOTECA *b, LIVRO *livro, int *erro);
void devolverLivro(BIBLIOTECA *b);

#endif
