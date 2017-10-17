/*
	Autores:
	Alex Galhardo
	Numero USP: 10408344

	Ian Castilho Caldeira Brant
	Numero USP: 10133967

	ICMC USP - São Carlos 2017
*/

#include "dinamico.h"

int main(){
	
	BIBLIOTECA b;
	criaBiblioteca(&b);

    printf("\n    ------------------       BIBLIOTECA USP      -------------------\n\n");
	printf("                             SEJA BEM VINDO       \n\n");

	int op, erro;

	do{
		mostrarMenu();
		scanf("%d", &op);
		menu(op, &b, &erro);
	}while(op); 

	return 0;
}

void mostrarMenu(){

	printf("\n                          -- Escolha uma opcao --   \n");
	printf("    Digite [1] para --> Cadastrar dados de algum livro na biblioteca.\n");
	printf("    Digite [2] para --> Cadastrar dados de algum aluno na biblioteca.\n");
	printf("    Digite [3] para --> Descadastrar dados de algum livro na biblioteca.\n");
	printf("    Digite [4] para --> Descadastrar dados de algum aluno na biblioteca.\n");
	printf("    Digite [5] para --> Retirar algum livro da biblioteca.\n");
	printf("    Digite [6] para --> Devolver algum livro para a biblioteca.\n");
	printf("    Digite [7] para --> Mostrar todos os livros cadastrados.\n");
	printf("    Digite [8] para --> Mostrar todos os alunos cadastrados.\n");
	printf("    Digite [9] para --> Mostrar todos os emails da biblioteca.\n");
	printf("\n    Digite [0] para --> SAIR\n\n");
	
	printf("    Opcao: ");
}

void menu(int op, BIBLIOTECA *b, int *erro){

	int i;
	LIVRO *livro;
	ALUNO *aluno;
	DADOS *dados;
	switch(op){

		case 1:
			cadastrarLivro(b);
			break;
	
		case 2:
			cadastrarAluno(b);
			break;

		case 3:
			descadastrarLivro(b);
			break;

		case 4:
			descadastrarAluno(b);
			break;

		case 5:
			retirarLivro(b);
			break;

		case 6:
			devolverLivro(b);
			break;

		case 7:
			printf("\n    ------ LIVROS CADASTRADOS NA BIBLIOTECA ------\n");
			livro = b->livros->inicio;
			int qtdLivros=0;
			while (livro != NULL){
				mostrarDadosLivro(livro);
				livro = livro->prox;
				qtdLivros++;
			}
			printf("\n    Total de livros cadastrados --> [%d]\n\n", qtdLivros);
			break;

		case 8:
			printf("\n    ------ ALUNOS CADASTRADOS NA BIBLIOTECA ------\n");
			aluno = b->alunos->inicio;
			int qtdAlunos = 0;
			while (aluno != NULL){	
				mostrarDadosAluno(aluno);
				aluno = aluno->prox;
				qtdAlunos++;
			}
			printf("\n    Total de alunos cadastrados --> [%d]\n\n", qtdAlunos);
			break;
		case 9:
			printf("\n    ------ TODOS OS EMAILS ------\n");
			dados = b->pilha->topo;
			int qtdEmail = 0;
			while (dados != NULL){	
				mostrarDadosEmail(dados);
				dados = dados->prox;
				qtdEmail++;
			}
			printf("\n    Total de emails --> [%d]\n\n", qtdEmail);
			break;

		case 0:
			printf("\n    [........Saindo da biblioteca........]\n\n");
			break;

		default:
			printf("\n\n    Por favor, digite um comando valido!\n");
	}
}

void mostrarDadosLivro(LIVRO *livro){

	printf ("\n    ISBN: %d\n", livro->ISBN);
	printf ("    Titulo: %s\n", livro->titulo);
	printf ("    Autor: %s\n", livro->autor);
	printf ("    Editora: %s\n", livro->editora);
	printf ("    Ano: %d\n", livro->ano);
	printf ("    Edicao: %d\n", livro->edicao);
	printf ("    Copias: %d\n", livro->copias);
}

void cadastrarLivro(BIBLIOTECA *b){
	
	int erro;

	erro = 0;

	LIVRO *livro;
	livro = (LIVRO*)malloc(sizeof(LIVRO));
	if(livro == NULL){
		erro = 1;
		printf(" ERRO na alocacao para o nó auxiliar livro!\n");
		return;
	}

	printf ("    Digite o ISBN do Livro [Deve conter 4 numeros inteiros]: ");
	scanf ("%d", &livro->ISBN);
	getchar();
	int verISBN = 1;
	verificaISBN(b, livro, &verISBN);
	while(verISBN != 1){
		if(verISBN == 2){
			printf("    [ERRO]   --> Livro já cadastrado no sistema!\n    Digite outro ISBN:");
			scanf("%d", &livro->ISBN);
			getchar();
		}else{
			printf("    [ERRO]  --> ISBN deve conter 4 numeros inteiros!\n    Digite outro ISBN: ");
			scanf("%d", &livro->ISBN);
			getchar();
		}
		verificaISBN(b, livro, &verISBN);
	}

	printf ("    Digite o Titulo do Livro: ");
	scanf ("%[^\n]s", livro->titulo);
	getchar();
	int verTitulo=1;
	verificaTitulo(b, livro, &verTitulo);
	while(verTitulo != 1){
		if(verTitulo != 1){
			printf("    [ERRO]  --> Titulo ja cadastrado na biblioteca!\n    Digite outro titulo: ");
			scanf("%[^\n]s", livro->titulo);
			getchar();
		}
		verificaTitulo(b, livro, &verTitulo);
	}

	printf ("    Digite o Autor do Livro: ");
	scanf ("%[^\n]s", livro->autor);
	getchar();
	printf ("    Digite a Editora do Livro: ");
	scanf ("%[^\n]s", livro->editora);
	getchar();

	printf ("    Digite o Ano do Livro: ");
	int ano;
	scanf ("%d", &ano);
	while(ano < 1800 || ano > 2017){
		printf("    [ERRO]  -> Digite um ano valido para o livro: ");
		scanf("%d", &ano);
	}
	livro->ano = ano;

	printf ("    Digite a Edicao do Livro: ");
	int edicao;
	scanf ("%d", &edicao);
	while(edicao < 1 || edicao > 99){
		printf("    [ERRO]  -> Digite uma edicao valida para o livro: ");
		scanf("%d", &edicao);
	}
	livro->edicao = edicao;
	
	printf("    Digite a Quantidade de Copias do Livro [Maximo 5 copias]: ");
	int copias;
	scanf ("%d",&copias);
	while(copias < 1 || copias > 5){
		printf("    Digite uma quantidade de copias valida: ");
		scanf("%d", &copias);
	}
	livro->copias = copias;
	livro->prox = NULL;
	
	
	insereLivro(b, livro, &erro);

	if(erro != 1){
		printf("\n    LIVRO CADASTRADO COM SUCESSO!\n");
	}
	else{
		printf ("    LIVRO JÁ ESTA CADASTRADO NA BIBLIOTECA!\n\n");
	}
}

void descadastrarLivro(BIBLIOTECA *b){
	
	int erro = 1, conf, ISBN, achouLivro;

	printf("    Digite o ISBN do Livro a ser descadastrado: ");
	scanf ("%d", &ISBN);
			
	LIVRO *aux;
	aux = b->livros->inicio;
	while(aux != NULL){
		if(aux->ISBN == ISBN){
			achouLivro = 1;
			break;
		}
		aux = aux->prox;
	}

	if(achouLivro == 1){
		mostrarDadosLivro(aux);
		printf("\n    Tem certeza que deseja descadastrar esse livro?\n");

		printf("    Digite [1] --> SIM\n");
		printf("    Digite [2] --> NAO\n");
		printf("    Opcao: ");
		scanf ("%d", &conf);
		if (conf == 1){
			removeLivro(b, aux, &erro);
			printf("\n    LIVRO DESCADASTRADO COM SUCESSO!\n\n");
		}
		else {
			printf("    DESCADASTRO CANCELADO!\n");
		}
	}
	else{
		printf("    LIVRO NAO ENCONTRADO NA BIBLIOTECA!\n\n");
	}
}

void mostrarDadosAluno(ALUNO *aluno){

	printf("\n\n    Numero USP: %d\n", aluno->numUSP);
	printf("    Nome: %s\n", aluno->nome);
	printf("    Telefone: %s\n", aluno->telefone);
	printf("    Email: %s\n", aluno->email);
	printf("    Emprestados: %d\n\n", aluno->emprestados);
}

void mostrarDadosEmail(DADOS *dados){

	printf("\n\n    Nome: %s\n", dados->nome);
	printf("    Numero USP: %d\n", dados->numUSP);
	printf("    Titulo: %s\n", dados->titulo);
	printf("    ISBN: %d\n", dados->ISBN);
	printf("    Mensagem: %s\n\n", dados->mensagem);
}



void cadastrarAluno(BIBLIOTECA *b){
	
	int erro = 0;

	ALUNO *aluno;
	aluno = (ALUNO*)malloc(sizeof(ALUNO));
	if(aluno == NULL){
		erro = 1;
		printf(" ERRO na alocacao de memoria para o no aluno!\n");
		return;
	}

	printf ("    Digite o Numero USP do Aluno: ");
	int numUSP;
	scanf ("%d", &aluno->numUSP);
	getchar();
	int verUSP = 1;
	verificaNumUSP(b, aluno, &verUSP);
	while(verUSP != 1){
		if(verUSP == 2){
			printf("    [ERRO]  -> Numero USP já cadastrado no sistema!\n");
			printf("    Digite outro numero USP: ");
			scanf("%d", &numUSP);
			getchar();
		}else{
			printf("    [ERRO]  -> Numero USP deve conter exatamente 8 digitos inteiros!\n");
			printf("    Digite outro numero USP: ");
			scanf("%d", &numUSP);
			getchar();
		}
		verificaNumUSP(b, aluno, &verUSP);
	}
	
	printf ("    Digite o Nome do Aluno: ");
	char nome[MAX];
	scanf ("%[^\n]s", aluno->nome);
	getchar();
	int verNome = 1;
	verificaNome(b, aluno, &verNome);
	while(verNome != 1){
		if(verNome != 1){
			printf("    [ERRO]  --> Nome já cadastrado no sistema!\n");
			printf("    Digite outro nome: ");
			scanf("%[^\n]s", nome);
			getchar();
		}
		verificaNome(b, aluno, &verNome);
	}

	printf ("    Digite o Telefone do Aluno: ");
	scanf ("%[^\n]s", aluno->telefone);
	getchar();
	int verTel = 1;
	verificaTelefone(b, aluno, &verTel);
	while(1){
		if(verTel == 2){
			printf("    [ERRO]  -> Telefone já cadastrado no sistema!\n");
			printf("    Digite um telefone valido: ");
			scanf("%[^\n]s", aluno->telefone);
			getchar();
		}
		else if(verTel == 3){
			printf("    [ERRO]  -> Telefone deve ter exatamente 13 digitos!\n");
			printf("    Digite um telefone valido: ");
			scanf("%[^\n]s", aluno->telefone);
			getchar();
		}
		else if(verTel == 4){
			printf("    [ERRO]  -> Telefone deve começar com '551899' !\n");
			printf("    Digite um telefone valido: ");
			scanf("%[^\n]s", aluno->telefone);
			getchar();
		}
		else{
			break;
		}
		verificaTelefone(b, aluno, &verTel);
	}

	printf ("    Digite o Email do Aluno [Deve terminar com '@usp.br']: ");
	scanf ("%[^\n]s", aluno->email);
	getchar();
	int verEmail = 1;
	verificaEmail(b, aluno, &verEmail);
	while(verEmail != 1){
		if(verEmail == 2){
			printf("    [ERRO]  -> Email invalido ou ja cadastrado na biblioteca!\n");
			printf("    Digite um email evalido: ");
			scanf("%[^\n]s", aluno->email);
			getchar();
		}
		else{
			printf("    [ERRO]  -> Email deve terminar com '@usp.br'!\n");
			printf("    Digite um email evalido: ");
			scanf("%[^\n]s", aluno->email);
			getchar();
		}
		verificaEmail(b, aluno, &verEmail);
	}
	aluno->emprestados = 0;
	aluno->prox = NULL;
	
	insereAluno(b, aluno, &erro);

	if (erro != 1){
		printf("\n\n\n    ALUNO CADASTRADO!\n\n\n");
	}
	else{
		printf ("    [ERRO] --> ALUNO JA CADASTRADO NA BIBLIOTECA!\n");
	}
}



void descadastrarAluno(BIBLIOTECA *b){

	int erro = 1, conf, numUSP, achouAluno;

	printf("    Digite o numero USP do aluno a ser descadastrado: ");
	scanf ("%d", &numUSP);
			
	ALUNO *aux;
	aux = b->alunos->inicio;
	while(aux != NULL){
		if(aux->numUSP == numUSP){
			achouAluno = 1;
			break;
		}
		aux = aux->prox;
	}

	if(achouAluno == 1){
		mostrarDadosAluno(aux);
		printf("\n    Tem certeza que deseja descadastrar esse aluno?\n");

		printf("    Digite [1] --> SIM\n");
		printf("    Digite [2] --> NAO\n");
		printf("    Opcao: ");
		scanf ("%d", &conf);
		if (conf == 1){
			removeAluno(b, aux, &erro);
			printf("\n    ALUNO DESCADASTRADO COM SUCESSO!\n\n");
		}
		else {
			printf("    DESCADASTRO CANCELADO!\n");
		}
	}
	else{
		printf("    ALUNO NAO ENCONTRADO NA BIBLIOTECA!\n\n");
	}
}

void retirarLivro(BIBLIOTECA *b){

	int erro;

	DADOS *dados;
	dados = (DADOS*)malloc(sizeof(DADOS));
	if(dados==NULL){
		erro = 1;
		return;
	}
	printf("    Digite o numero USP do aluno que ira retirar o livro: ");
	scanf("%d", &dados->numUSP);
	printf("    Digite o ISBN do livro que sera retirado: ");
	scanf("%d", &dados->ISBN);
	dados->prox = NULL;
	
	ALUNO *noa;
	erro = 0;
	noa = b->alunos->inicio;
	
	int achouAluno=0, achouLivro=0, emprestados=0;
	
	while(noa != NULL){
		if(noa->numUSP == dados->numUSP){
			achouAluno = 1;
			strcpy(dados->nome, noa->nome);
			
			if(noa->emprestados > 2){
				printf("    O aluno não pode retirar mais 1 livro no momento,\npor que já possui 2 livros em posse!\n");
				emprestados = 1;
				break;
			}
			break;
		}
		noa = noa->prox;
	}
	if(achouAluno !=1){
		printf("    Aluno não encontrado ou não cadastrado na biblioteca!\n");
		erro = 1;
		return;
	}
	if(emprestados==1){
		printf("    O aluno nao pode mais retirar livro da biblioteca no momento!\n");
		erro = 1;
		return;
	}
	
	 LIVRO *nol;
	 nol = b->livros->inicio;
	 
	while(nol != NULL){
		 if(nol->ISBN == dados->ISBN){

			 achouLivro = 1;
			 strcpy(dados->titulo, nol->titulo);
		
			 if(nol->copias < 1){
				 printf("\n    Nao há copias do livro disponiveis no momento!\n");
				 
				 printf("    Gostaria de adicionar o aluno na lista de espera?\n");
				 printf("    Digite [1] --> SIM\n");
				 printf("    Digite [2] --> NAO\n");
				 int opcao;
				 printf("    Opcao: ");
				 scanf("%d", &opcao);
				 while(opcao != 1 || opcao != 2){
					if(opcao == 1){
						if(b->espera->inicio == NULL){
							b->espera->inicio = dados;
							b->qtdEspera++;
							printf("\n    O aluno [%s] foi adicionado na lista de espera!\n", dados->nome);
							break;
						}
						else{
							b->espera->inicio->prox = dados;
							b->qtdEspera++;
							printf("\n   O aluno [%s] foi adicionado na lista de espera!\n", dados->nome);
							break;
						}
						b->espera->inicio = dados;
					}
					else if(opcao == 2){
						break;
					}
					else{
						printf("    Digite [1] --> SIM\n");
						printf("    Digite [2] --> NAO\n");
					}
					scanf("%d", &opcao);
				 }
			 }
			 
			 else{
				 noa->emprestados++;
				 nol->copias--;
				 
				 if(b->pilha->topo == NULL){
					 b->pilha->topo = dados;
					 strcpy(b->pilha->topo->mensagem, "    LIVRO RETIRADO COM SUCESSO!\n");
					 
					 
					 printf("\n    ------ EMAIL ------\n");
					 printf("    Nome: %s\n", dados->nome);
					 printf("    Numero USP: %d\n", dados->numUSP);
					 printf("    Titulo: %s\n", dados->titulo);
					 printf("    ISBN: %d\n", dados->ISBN);
					 printf("    LIVRO RETIRADO COM SUCESSO!\n\n");
					 
				}
				else{
					dados->prox = b->pilha->topo;
					b->pilha->topo = dados;
					strcpy(b->pilha->topo->mensagem, "    LIVRO RETIRADO COM SUCESSO!\n");
					
					printf("\n    ------ EMAIL ------\n");
					printf("    Nome: %s\n", dados->nome);
					printf("    Numero USP: %d\n", dados->numUSP);
					printf("    Titulo: %s\n", dados->titulo);
					printf("    ISBN: %d\n", dados->ISBN);
					printf("    LIVRO RETIRADO COM SUCESSO!\n\n");
				 }
				b->pilha->topo = dados;
				break;
			 }
		 }
		nol = nol->prox;
	 }
	
	if(achouLivro != 1){
		printf("    Livro não encontrado ou nao cadastrado na biblioteca!\n");
		erro = 1;
		return;
	}

	free(nol);
}



void devolverLivro(BIBLIOTECA *b){

	int erro;

	DADOS *dados;
	dados = (DADOS*)malloc(sizeof(DADOS));
	if(dados == NULL){
		erro = 1;
		return;
	}
	
	printf("    Digite o ISBN do livro que vai ser devolvido: ");
	scanf("%d", &dados->ISBN);
	printf("    Digite o numero USP do aluno que esta devolvendo o livro: ");
	scanf("%d", &dados->numUSP);
	dados->prox = NULL;
	
	int achouLivro=0, achouAluno=0;
	
	ALUNO *noa;
	noa = b->alunos->inicio;
	
	while(noa != NULL){
		if(noa->numUSP == dados->numUSP){
			strcpy(dados->nome, noa->nome);
			achouAluno = 1;
			break;
		}
		noa = noa->prox;
	}
	if(achouAluno != 1){
		printf("    Aluno nao encontrado ou cadastrado na biblioteca!\n");
		erro = 1;
		return;
	}
	
	
	LIVRO *nol;
	nol = b->livros->inicio;
	
	while(nol != NULL){
		if(nol->ISBN == dados->ISBN){
			strcpy(dados->titulo, nol->titulo);
			achouLivro = 1;
			
			nol->copias++;
			noa->emprestados--;
			
			if(b->pilha->topo == NULL){
				b->pilha->topo = dados;
				strcpy(b->pilha->topo->mensagem, "    LIVRO DEVOLVIDO COM SUCESSO!\n");
					 
				printf("\n    ------ EMAIL ------\n");
				printf("    Nome: %s\n", dados->nome);
				printf("    Numero USP: %d\n", dados->numUSP);
				printf("    Titulo: %s\n", dados->titulo);
				printf("    ISBN: %d\n", dados->ISBN);
				printf("    LIVRO DEVOLVIDO COM SUCESSO!\n\n");
			}
			else{
				dados->prox = b->pilha->topo;
				b->pilha->topo = dados;
				strcpy(b->pilha->topo->prox->mensagem, "    LIVRO DEVOLVIDO COM SUCESSO!\n");
					 
				printf("\n    ------ EMAIL ------\n");
				printf("    Nome: %s\n", dados->nome);
				printf("    Numero USP: %d\n", dados->numUSP);
				printf("    Titulo: %s\n", dados->titulo);
				printf("    ISBN: %d\n", dados->ISBN);
				printf("    LIVRO DEVOLVIDO COM SUCESSO!\n\n");
			}
			break;
		}
		nol = nol->prox;
	}
	
	if(achouLivro != 1){
		printf("    Livro nao encontrado ou cadastrado na biblioteca!\n");
		erro = 1;
		return;
	}
	
	if(b->qtdEspera > 0){

		DADOS *noe;
		noe = b->espera->inicio;
		
		DADOS *deletar;
		
		while(noe != NULL){
			if(noe->ISBN == dados->ISBN){
				b->qtdEspera--;
				
				if(b->pilha->topo == NULL){
					b->qtdEmail++;
					b->pilha->topo = noe;
					strcpy(b->pilha->topo->mensagem, "    O ALUNO JÁ PODE RETIRAR O LIVRO QUE ESTAVA ESPERANDO!\n");
						 
					printf("\n    ------ EMAIL ------\n");
					printf("    Nome: %s\n", noe->nome);
					printf("    Numero USP: %d\n", noe->numUSP);
					printf("    Titulo: %s\n", noe->titulo);
					printf("    ISBN: %d\n", noe->ISBN);
					printf("    O ALUNO JÁ PODE RETIRAR O LIVRO QUE ESTAVA ESPERANDO!\n\n");
					break;
				}
				else{
					b->qtdEmail++;
					b->pilha->topo->prox = noe;
					strcpy(b->pilha->topo->prox->mensagem, "    O ALUNO JÁ PODE RETIRAR O LIVRO QUE ESTAVA ESPERANDO!\n");
						 
					printf("    ------ EMAIL ------\n");
					printf("    Nome: %s\n", noe->nome);
					printf("    Numero USP: %d\n", noe->numUSP);
					printf("    Titulo: %s\n", noe->titulo);
					printf("    ISBN: %d\n", noe->ISBN);
					printf("    O ALUNO JÁ PODE RETIRAR O LIVRO QUE ESTAVA ESPERANDO!\n\n");
				}
				b->pilha->topo = noe;
				break;
			}
			noe = noe->prox;
		}
		
		deletar = noe;
	    noe = noe->prox;
		free(deletar);
	}
}



