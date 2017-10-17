/*
	Autores:
	Alex Galhardo
	Numero USP: 10408344

	Ian Castilho Caldeira Brant
	Numero USP: 10133967

	ICMC USP - São Carlos 2017
*/

#include "estatico.h"

int main(){
	
	BIBLIOTECA b;
	criaBiblioteca(&b);

	printf("\n    ------------------       BIBLIOTECA USP      -------------------\n\n");
	printf("                             SEJA BEM VINDO       \n\n");

	int erro, op;

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
	DADOS dados;
	int qtdLivros = 0;
	int qtdEmail = 0;
	int qtdAlunos = 0;
	
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
			i = b->livros.inicio;
			
			while (i != -1){
				mostrarDadosLivro(b->livros.info[i].info);
				i = b->livros.info[i].prox;
				qtdLivros++;
			}
			printf("    Total de livros cadastrados --> [%d]\n\n", qtdLivros);
			break;	
			
		case 8:
			printf("\n    ------ ALUNOS CADASTRADOS NA BIBLIOTECA ------\n");
			i = b->alunos.inicio;
			
			while (i != -1){	
				mostrarDadosAluno(b->alunos.info[i].info);
				i = b->alunos.info[i].prox;
				qtdAlunos++;
			}
			printf("    Total de alunos cadastrados --> [%d]\n\n", qtdAlunos);
			break;
		
		case 9:
			printf("\n    ------ TODOS OS EMAILS ------\n");
			dados = b->pilha.info[b->pilha.topo];
			i = b->pilha.topo;
			
			while (i != -1){	
				mostrarDadosEmail(dados);
				i = b->pilha.info[i].prox;
				dados = b->pilha.info[i];
				qtdEmail++;
			}
			printf("\n    Total de emails --> [%d]\n\n", qtdEmail);
			break;
		
		case 0:
			printf("\n    [........Saindo da biblioteca........]\n\n");
			break;

		default:
			printf("\n\n    Por favor, digite um comando valido!\n");
			break;
	}	
}	

void mostrarDadosLivro(LIVRO livro){

	printf ("\n    ISBN: %d\n", livro.ISBN);
	printf ("    Titulo: %s\n", livro.titulo);
	printf ("    Autor: %s\n", livro.autor);
	printf ("    Editora: %s\n", livro.editora);
	printf ("    Ano: %d\n", livro.ano);
	printf ("    Edicao: %d\n", livro.edicao);
	printf ("    Copias: %d\n", livro.copias);
	printf ("    Quantidade emprestada: %d\n", livro.emprestados);
	printf ("    Lista de Espera: %d\n\n", livro.espera);
}

void cadastrarLivro(BIBLIOTECA *b){
	
	LIVRO livro;
	int erro;
	
	printf("    Digite o ISBN do Livro[Deve conter 4 numeros inteiros]: ");
	scanf("%d", &livro.ISBN);
	getchar();
	int verISBN = 1;
	verificaISBN(b, &livro, &verISBN);
	while(verISBN != 1){
		if(verISBN == 2){
			printf("    [ERRO] --> ISBN ja cadastrado na biblioteca!\n");
			printf("    Por favor, digite um ISBN valido: ");
			scanf ("%d", &livro.ISBN);
			getchar();
		}
		else{
			printf("    [ERRO] --> ISBN deve conter exatamente 4 numeros inteiros!\n");
			printf("    Por favor, digite um ISBN valido: ");
			scanf ("%d", &livro.ISBN);
			getchar();
		}
		verificaISBN(b, &livro, &verISBN);
	}

	printf ("    Digite o Titulo do Livro: ");
	scanf ("%[^\n]s", livro.titulo);
	getchar();
	int verTitulo = 1;
	verificaTitulo(b, livro, &verTitulo);
	while(verTitulo != 1){
		printf("    [ERRO] --> Titulo ja cadastrado na biblioteca!\n");
		printf("    Digite um titulo valido: ");
		scanf("%[^\n]s", livro.titulo);
		getchar();
		verificaTitulo(b, livro, &verTitulo);
	}

	printf ("    Digite o Autor do Livro: ");
	scanf ("%[^\n]s", livro.autor);
	getchar();

	printf ("    Digite a Editora do Livro: ");
	scanf ("%[^\n]s", livro.editora);
	getchar();

	printf ("    Digite o Ano do Livro: ");
	scanf ("%d",&livro.ano);
	getchar();
	while(livro.ano < 1800 || livro.ano > 2017){
		printf("    [ERRO] -> Digite um ano de publicação valido: ");
		scanf("%d", &livro.ano);
		getchar();
	}

	printf ("    Digite a Edicao do Livro: ");
	scanf ("%d",&livro.edicao);
	while(livro.edicao < 1 || livro.edicao > 99){
		printf("    [ERRO] -> Digite uma edicao valida: ");
		scanf("%d", &livro.edicao);
		getchar();
	}

	printf("    Digite a Quantidade de Copias do Livro [Maximo 10 copias]: ");
	scanf ("%d", &livro.copias);
	getchar();
	while(livro.copias < 1 || livro.copias > 10){
		printf("    [ERRO] --> O livro deve ter pelo menos 1 copia e no maximo 10 copias!\n");
		printf("    Quantidade de copias: ");
		scanf ("%d", &livro.copias);
		getchar();
	}

	livro.iniesp = -1;
	livro.fimesp = -1;
	livro.iniemp = -1;
	livro.fimemp = -1;
	livro.emprestados = 0;
	livro.espera = 0;

	insereLivro(b, livro, &erro);

	if (erro != 1){
		printf("\n\n    LIVRO CADASTRADO COM SUCESSO!\n\n\n");
	}
	else{
		printf ("    [!!!ERRO NO CADASTRO DO livro!!!]");
	}
}


void descadastrarLivro(BIBLIOTECA *b){

	LIVRO livro;
	int erro, conf;

	printf("    Digite o ISBN do Livro a ser descadastrado: ");
	scanf("%d", &livro.ISBN);
			
	verificaISBN(b, &livro, &erro);

	if (erro == 2){
		mostrarDadosLivro(livro);
		printf("    Tem certeza que deseja descadastrar esse livro?\n");

		printf("    Digite [1] --> SIM\n");
		printf("    Digite [2] --> NAO\n");
		printf("    Opcao: ");
		scanf ("%d", &conf);
		if (conf == 1){
			removeLivro(b, livro, &erro);
			printf("    LIVRO DESCADASTRADO COM SUCESSO!\n\n");
		}
		else {
			printf("    DESCADASTRO CANCELADO!\n");
		}
	}
	else{
		printf("    LIVRO NAO ENCONTRADO NA BIBLIOTECA!\n\n");
	}
	
}

void mostrarDadosAluno(ALUNO aluno){
	printf("\n\n    Numero USP: %d\n", aluno.numUSP);
	printf("    Nome: %s\n", aluno.nome);
	printf("    Telefone: %s\n", aluno.telefone);
	printf("    Email: %s\n\n", aluno.email);
}

void cadastrarAluno(BIBLIOTECA *b){
	
	ALUNO aluno;
	int erro;
	
	printf ("    Digite o Numero USP do Aluno: ");
	scanf ("%d", &aluno.numUSP);
	getchar();
	int verNum = 1;
	verificaNumUSP(b, &aluno, &verNum);
	while(verNum != 1){
		if(verNum == 2){
			printf("    [ERRO] --> Numero USP ja cadastrado na biblioteca!\n");
			printf("    Por favor, digite um numero USP valido: ");
			scanf ("%d", &aluno.numUSP);
			getchar();
		}
		else{
			printf("    [ERRO] --> Numero USP deve conter exatamente 8 numeros inteiros!\n");
			printf("    Por favor, digite um numero USP valido: ");
			scanf ("%d", &aluno.numUSP);
			getchar();
		}
		verificaNumUSP(b, &aluno, &verNum);
	}


	printf ("    Digite o Nome do Aluno: ");
	scanf ("%[^\n]s", aluno.nome);
	getchar();
	int verNome = 1;
	verificaNome(b, aluno, &verNome);
	while(verNome != 1){
		printf("    [ERRO] --> Nome ja cadastrado na biblioteca!\n");
		printf("    Por favor, digite o nome de outro modo: ");
		scanf ("%[^\n]s", aluno.nome);
		getchar();
		verificaNome(b, aluno, &verNome);
	}

	printf ("    Digite o Telefone do Aluno: ");
	scanf("%[^\n]s", aluno.telefone);
	getchar();
	int verTel = 1;
	verificaTelefone(b, aluno, &verTel);
	while(verTel != 1){
		if(verTel == 2){
			printf("    [ERRO] --> O telefone deve conter exatamente 13 digitos inteiros!\n");
			printf("    Por favor, digite um teleone valido: ");
			scanf ("%[^\n]s", aluno.telefone);
			getchar();
		}
		else if(verTel == 3){
			printf("    [ERRO] --> O telefone ja esta cadastrado na biblioteca!\n");
			printf("    Por favor, digite um teleone valido: ");
			scanf ("%[^\n]s", aluno.telefone);
			getchar();
		}
		else{
			printf("    [ERRO] --> O telefone deve começar com '551899'!\n");
			printf("    Por favor, digite um teleone valido: ");
			scanf ("%[^\n]s", aluno.telefone);
			getchar();
		}
		verificaTelefone(b, aluno, &verTel);
		
	}
	
	printf("    Digite o Email do Aluno: ");

	scanf("%[^\n]s", aluno.email);

	getchar();

	int verEmail = 1;
	verificaEmail(b, aluno, &verEmail);
	while(verEmail != 1){
		if(verEmail == 2){
			printf("    [ERRO] --> Email ja cadastrado na biblioteca!\n");
			printf("    Por favor, digite um email valido: ");
			scanf ("%[^\n]s", aluno.email);
			getchar();
		}
		else{
			printf("    [ERRO] --> Email deve terminar com '@usp.br'!\n");
			printf("    Por favor, digite um email valido: ");
			scanf ("%[^\n]s", aluno.email);
			getchar();
		}
		verificaEmail(b, aluno, &verEmail);
	}

	aluno.emprestados=0;
	aluno.inicio = -1;
	aluno.fim = -1;			
	insereAluno(b, aluno, &erro);
	
	if (erro != 1){
		printf("\n\n\n    ALUNO CADASTRADO COM SUCESSO!\n\n\n");
	}
	else{
		printf ("    [!!!ERRO NO CADASTRO DO ALUNO!!!]");
	}
}

void descadastrarAluno(BIBLIOTECA *b){

	ALUNO aluno;
	int erro, conf;

	printf ("    Digite o Numero USP do Aluno a ser descadastrado:\n");
	scanf ("%d", &aluno.numUSP);
	printf("    [...Encontrando aluno...]\n\n");
	verificaNumUSP(b, &aluno, &erro);

	if (erro == 2){
		mostrarDadosAluno(aluno);

		printf("    Tem certeza que gostaria de descadastrar esse aluno?\n");
		printf("    Digite [1] --> SIM\n");
		printf("    Digite [2] --> NAO\n");
		scanf ("%d", &conf);
		while(conf != 1 || conf != 2){
			if(conf == 1){
				removeAluno(b, aluno, &erro);
				printf ("    Aluno Descadastrado com Sucesso!\n\n");
				break;
			}
			else if(conf == 2){
				printf ("    Descadastro cancelado!\n\n");
				break;
			}
			else{
				printf("    Digite [1] --> SIM\n");
				printf("    Digite [2] --> NAO\n");
			}
		}
	} 
	else{
		printf ("    Aluno nao encontrado!\n\n");
	}
	
}	

void retirarLivro(BIBLIOTECA *b){
	
	int erro=0, conf;
	LIVRO livro;
	ALUNO aluno;

	printf ("    Digite o ISBN do livro que deseja retirar: ");
	scanf ("%d", &livro.ISBN);
	printf("    [...Buscando livro...]\n\n");
	verificaISBN(b, &livro, &erro);
	if (erro == 1){
		printf ("    Livro não encontrado na biblioteca!\n");
		return;
	} 
	
	
	printf ("    Digite o Numero USP do Aluno: ");
	scanf ("%d", &aluno.numUSP);
	printf("    [...Buscando Aluno...]\n\n");
	verificaNumUSP(b, &aluno, &erro);
	if (erro == 1){
		printf ("    Aluno nao encontrato na biblioteca!\n");
		return;
	} 
	
	mostrarDadosLivro(livro);
	printf("\n    Confirma a retirada deste livro?\n");
	printf("    Digite [1] --> SIM\n");
	printf("    Digite [2] --> NAO\n");
	printf("    Opcao: "); 
	scanf("%d", &conf);
	if(conf == 2){
		printf ("    Emprestimo Cancelado!\n\n");
		return;
	}
			
	if(livro.emprestados == livro.copias){
		printf("    Nao ha copias disponiveis!\n");
		printf("    Gostaria de inserir aluno na lista de espera?\n");
		printf("    Digite [1] --> SIM\n");
		printf("    Digite [2] --> NAO\n");
		printf("    Opcao: ");
		scanf("%d", &conf);
		if (conf == 2){
			printf ("    RETIRADA CANCELADA!\n\n");
			return;
		}

		b->livros.info[livro.pos].info.espera = b->livros.info[livro.pos].info.espera + 1;
		insereEspera(b, &b->livros.info[livro.pos].info, &b->alunos.info[aluno.pos].info, &erro);
		if (erro == 1){
			printf ("    Erro: A lista de espera esta cheia! Contate o desenvolvedor para aumentar a capacidade da lista de espera\n\n");
			return;
		}
		printf ("\n    Aluno inserido na lista de espera com sucesso!\n\n");
		return;		
	}
	if(livro.emprestados < livro.copias){
	
		b->livros.info[livro.pos].info.emprestados = b->livros.info[livro.pos].info.emprestados + 1;
		b->alunos.info[aluno.pos].info.emprestados = b->alunos.info[aluno.pos].info.emprestados + 1;
		InsereEmprestados (b, &b->livros.info[livro.pos].info, &b->alunos.info[aluno.pos].info, &erro);
		if (erro==1){
			printf ("    Erro: A lista de emprestados esta cheia! Contate o desenvolvedor para aumentar a capacidade da lista de emprestados\n\n");
			return;
		}
	}

	InsereEmprestimos(b, &b->livros.info[livro.pos].info, &b->alunos.info[aluno.pos].info, &erro);
	if(erro == 1){
		printf ("    Erro: A lista de emprestimos esta cheia! Contate o desenvolvedor para aumentar a capacidade da lista de emprestimos\n\n");
		return;
	}
	
				if(b->pilha.topo == -1){
					 b->pilha.topo = 0;
					 strcpy(b->pilha.info[b->pilha.topo].mensagem, "    LIVRO RETIRADO COM SUCESSO!\n");
					 strcpy(b->pilha.info[b->pilha.topo].titulo ,b->livros.info[livro.pos].info.titulo);
					 b->pilha.info[b->pilha.topo].ISBN = b->livros.info[livro.pos].info.ISBN;
					 strcpy(b->pilha.info[b->pilha.topo].nome , b->alunos.info[aluno.pos].info.nome);
					 b->pilha.info[b->pilha.topo].numUSP = b->alunos.info[aluno.pos].info.numUSP;
					 b->pilha.info[b->pilha.topo].prox = -1;
					 
					 
					 printf("\n    ------ EMAIL ------\n");
					 printf("    Nome: %s\n", b->alunos.info[aluno.pos].info.nome);
					 printf("    Numero USP: %d\n", b->alunos.info[aluno.pos].info.numUSP);
					 printf("    Titulo: %s\n", b->livros.info[livro.pos].info.titulo);
					 printf("    ISBN: %d\n", b->livros.info[livro.pos].info.ISBN);
					 printf("    LIVRO RETIRADO COM SUCESSO!\n\n");
					 
				}
				else{
					b->pilha.info[b->pilha.topo].prox = b->pilha.pv;
					b->pilha.topo = b->pilha.pv;
					b->pilha.pv = b->pilha.info[b->pilha.pv].prox;
					strcpy(b->pilha.info[b->pilha.topo].mensagem, "    LIVRO RETIRADO COM SUCESSO!\n");
					strcpy(b->pilha.info[b->pilha.topo].titulo ,b->livros.info[livro.pos].info.titulo);
					 b->pilha.info[b->pilha.topo].ISBN = b->livros.info[livro.pos].info.ISBN;
					 strcpy(b->pilha.info[b->pilha.topo].nome , b->alunos.info[aluno.pos].info.nome);
					 b->pilha.info[b->pilha.topo].numUSP = b->alunos.info[aluno.pos].info.numUSP;
					 b->pilha.info[b->pilha.topo].prox = -1;
					
					 printf("\n    ------ EMAIL ------\n");
					 printf("    Nome: %s\n", b->alunos.info[aluno.pos].info.nome);
					 printf("    Numero USP: %d\n", b->alunos.info[aluno.pos].info.numUSP);
					 printf("    Titulo: %s\n", b->livros.info[livro.pos].info.titulo);
					 printf("    ISBN: %d\n", b->livros.info[livro.pos].info.ISBN);
					 printf("    LIVRO RETIRADO COM SUCESSO!\n\n");
				 }
				return;
}


void devolverLivro(BIBLIOTECA *b){
	
	int conf, erro;
	ALUNO aluno;
	LIVRO livro;

	printf ("    Digite o Numero USP do aluno que ira devolver o livro: ");
	scanf ("%d", &aluno.numUSP);
	printf("    [...Buscando Aluno...]\n");
	verificaNumUSP(b, &aluno, &erro);
	if (erro == 1){
		erro = 1;
		printf ("    Aluno nao encontrado na biblioteca!\n");
		return;
	}
	else{
		mostrarDadosAluno(aluno);
		printf("    Esse aluno que irá devolver o livro?\n"); 
		printf("    Digite [1] --> SIM\n");
		printf("    Digite [2] --> NAO\n");
		printf("    Opcao: ");
		scanf ("%d", &conf);
		if (conf == 2){
			printf ("    Devolucao cancelada!\n\n");
		}
		else{
			printf ("    Digite o ISBN do Livro que sera devolvido: ");
			scanf ("%d", &livro.ISBN);
			printf("    [...Buscando Livro...]\n");
			verificaISBN(b, &livro, &erro);
			if (erro == 1){
				erro = 1;
				printf ("    Livro Nao Encontrado!\n");
				return;
			} 
			else{
				mostrarDadosLivro(livro);
				printf("\n    Confirma a devolução deste livro?\n"); 
				printf("    Digite [1] --> SIM\n");
				printf("    Digite [2] --> NAO\n");
				printf("    Opcao: ");
				scanf("%d", &conf);
				while(conf != 1 || conf != 2){
					if (conf == 2){
						printf ("    Devolucao Cancelada!\n\n");
						break;
					}
					else if(conf == 1){

						if(EstaEmprestado(b, &livro, aluno)==1){
							printf ("    O livro nao esta emprestado para esse aluno!\n\n");
							break;
						}
						else{
		
							RemoveEmprestado (b, &b->livros.info[livro.pos].info, aluno, &erro);
							b->livros.info[livro.pos].info.emprestados = b->livros.info[livro.pos].info.emprestados - 1;
							b->alunos.info[aluno.pos].info.emprestados = b->alunos.info[aluno.pos].info.emprestados - 1;
				
					if(b->pilha.topo == -1){
					 b->pilha.topo = 0;
					 strcpy(b->pilha.info[b->pilha.topo].mensagem, "    LIVRO DEVOLVIDO COM SUCESSO!\n");
					 strcpy(b->pilha.info[b->pilha.topo].titulo ,b->livros.info[livro.pos].info.titulo);
					 b->pilha.info[b->pilha.topo].ISBN = b->livros.info[livro.pos].info.ISBN;
					 strcpy(b->pilha.info[b->pilha.topo].nome , b->alunos.info[aluno.pos].info.nome);
					 b->pilha.info[b->pilha.topo].numUSP = b->alunos.info[aluno.pos].info.numUSP;
					 b->pilha.info[b->pilha.topo].prox = -1;
					 
					 
					 
					 printf("\n    ------ EMAIL ------\n");
					 printf("    Nome: %s\n", b->alunos.info[aluno.pos].info.nome);
					 printf("    Numero USP: %d\n", b->alunos.info[aluno.pos].info.numUSP);
					 printf("    Titulo: %s\n", b->livros.info[livro.pos].info.titulo);
					 printf("    ISBN: %d\n", b->livros.info[livro.pos].info.ISBN);
					 printf("    LIVRO DEVOLVIDO COM SUCESSO!\n\n");
					 
				}
				else{
					b->pilha.info[b->pilha.topo].prox = b->pilha.pv;
					b->pilha.topo = b->pilha.pv;
					b->pilha.pv = b->pilha.info[b->pilha.pv].prox;
					strcpy(b->pilha.info[b->pilha.topo].mensagem, "    LIVRO DEVOLVIDO COM SUCESSO!\n");
					strcpy(b->pilha.info[b->pilha.topo].titulo ,b->livros.info[livro.pos].info.titulo);
					 b->pilha.info[b->pilha.topo].ISBN = b->livros.info[livro.pos].info.ISBN;
					 strcpy(b->pilha.info[b->pilha.topo].nome , b->alunos.info[aluno.pos].info.nome);
					 b->pilha.info[b->pilha.topo].numUSP = b->alunos.info[aluno.pos].info.numUSP;
					 b->pilha.info[b->pilha.topo].prox = -1;
					
					printf("\n    ------ EMAIL ------\n");
					 printf("    Nome: %s\n", b->alunos.info[aluno.pos].info.nome);
					 printf("    Numero USP: %d\n", b->alunos.info[aluno.pos].info.numUSP);
					 printf("    Titulo: %s\n", b->livros.info[livro.pos].info.titulo);
					 printf("    ISBN: %d\n", b->livros.info[livro.pos].info.ISBN);
					 printf("    LIVRO DEVOLVIDO COM SUCESSO!\n\n");
				 }
				return;
		
							if (b->livros.info[livro.pos].info.espera > 0){
			
								printf ("    O livro ja esta disponivel para o aluno abaixo:\n\n");
								mostrarDadosAluno(b->espera.info[livro.iniesp].info);
								RemoveEspera (b, &b->livros.info[livro.pos].info, b->espera.info[livro.iniesp].info, &erro);
								b->livros.info[livro.pos].info.espera = b->livros.info[livro.pos].info.espera - 1;
			
			
								b->livros.info[livro.pos].info.emprestados = b->livros.info[livro.pos].info.emprestados + 1;

								b->alunos.info[b->espera.info[livro.iniesp].info.pos].info.emprestados = b->alunos.info[b->espera.info[livro.iniesp].info.pos].info.emprestados + 1;

								InsereEmprestados(b, &b->livros.info[livro.pos].info, &b->espera.info[b->livros.info[livro.pos].info.iniesp].info, &erro);
								InsereEmprestimos(b, &b->livros.info[livro.pos].info, &b->espera.info[b->livros.info[livro.pos].info.iniesp].info, &erro);
								
					if(b->pilha.topo == -1){
					 b->pilha.topo = 0;
					 strcpy(b->pilha.info[b->pilha.topo].mensagem, "   O ALUNO JÁ PODE RETIRAR O LIVRO QUE ESTAVA ESPERANDO!\n\n");
					 	strcpy(b->pilha.info[b->pilha.topo].titulo ,b->livros.info[livro.pos].info.titulo);
					 b->pilha.info[b->pilha.topo].ISBN = b->livros.info[livro.pos].info.ISBN;
					 strcpy(b->pilha.info[b->pilha.topo].nome , b->alunos.info[aluno.pos].info.nome);
					 b->pilha.info[b->pilha.topo].numUSP = b->alunos.info[aluno.pos].info.numUSP;
					 b->pilha.info[b->pilha.topo].prox = -1;
					 
					 
				}
				else{
					b->pilha.info[b->pilha.topo].prox = b->pilha.pv;
					b->pilha.topo = b->pilha.pv;
					b->pilha.pv = b->pilha.info[b->pilha.pv].prox;
					strcpy(b->pilha.info[b->pilha.topo].mensagem, "    O ALUNO JÁ PODE RETIRAR O LIVRO QUE ESTAVA ESPERANDO!\n\n");
						strcpy(b->pilha.info[b->pilha.topo].titulo ,b->livros.info[livro.pos].info.titulo);
					 b->pilha.info[b->pilha.topo].ISBN = b->livros.info[livro.pos].info.ISBN;
					 strcpy(b->pilha.info[b->pilha.topo].nome , b->alunos.info[aluno.pos].info.nome);
					 b->pilha.info[b->pilha.topo].numUSP = b->alunos.info[aluno.pos].info.numUSP;
					 b->pilha.info[b->pilha.topo].prox = -1;
					
			
				 }
				return;
							}
							break;
						}
					}
					printf("    Digite [1] --> SIM\n");
					printf("    Digite [2] --> NAO\n");
					printf("    Opcao: ");
					scanf("%d", &conf);
				}
			}
		}
	}
}

void mostrarDadosEmail(DADOS dados){

	printf("\n\n    Nome: %s\n", dados.nome);
	printf("    Numero USP: %d\n", dados.numUSP);
	printf("    Titulo: %s\n", dados.titulo);
	printf("    ISBN: %d\n", dados.ISBN);
	printf("    Mensagem: %s\n\n", dados.mensagem);
}


