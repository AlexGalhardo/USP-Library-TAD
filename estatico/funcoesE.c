/*
	Autores:
	Alex Galhardo
	Numero USP: 10408344

	Ian Castilho Caldeira Brant
	Numero USP: 10133967

	ICMC USP - São Carlos 2017
*/

#include "estatico.h"

/* criar biblioteca */
void criaBiblioteca(BIBLIOTECA *b){

	int i;

	b->emprestimos.pv = 0;
	for(i=0; i < tamEmprestimo; i++){
		b->emprestimos.info[i].prox = i + 1;
	}
	b->emprestimos.info[tamEmprestimo-1].prox = -1;

	b->emprestados.pv = 0;
	for(i=0; i < tamEmprestados; i++){
		b->emprestados.info[i].prox = i + 1;
	}
	b->emprestados.info[tamEmprestados-1].prox = -1;

	b->espera.pv = 0;
	for(i=0; i < tamEspera; i++){
		b->espera.info[i].prox = i+1;
	}
	b->espera.info[tamEspera-1].prox = -1;

	b->livros.pv = 0;
	b->livros.inicio = -1;
	b->livros.fim = -1;
	for(i=0; i < tamLivros; i++){
		b->livros.info[i].prox = i+1;
	}
	b->livros.info[tamLivros-1].prox = -1;

	b->alunos.pv = 0; 
	b->alunos.inicio = -1;
	b->alunos.fim = -1; 
	for (i=0;i<tamAlunos;i++){ 
		b->alunos.info[i].prox = i + 1; 
	}
	b->alunos.info[tamAlunos-1].prox=-1; 
	
	b->pilha.pv = 0;
	b->pilha.topo = -1;
	for(i=0; i < tamEmail; i++){
		b->pilha.info[i].prox = i + 1;
	}
	b->pilha.info[tamEmprestados-1].prox = -1;
	
}

/* FUNCAO PARA BUSCAR UM LIVRO PELO SEU ISBN */
void verificaISBN(BIBLIOTECA *b, LIVRO *livro, int *ver){  
	
	int i;
	i = b->livros.inicio;

	*ver = 1;

	if(i == -1){
		if(livro->ISBN < 1000 || livro->ISBN > 9999){
		*ver = 3;
	}
		return;
	}
	else{
		while(i!=-1){
			if(b->livros.info[i].info.ISBN == livro->ISBN){
				*ver = 2;
				*livro = b->livros.info[i].info;
				break;
			}
			i = b->alunos.info[i].prox;
		}
	}

	if(livro->ISBN < 1000 || livro->ISBN > 9999){
		*ver = 3;
	}
}

void verificaTitulo(BIBLIOTECA *b, LIVRO livro, int *ver){  
	
	int i, erro; 
	i = b->livros.inicio; 

	*ver = 1; 

	if (i == -1){ 
		erro = 1;
		return;
	} 
	else {
		while (i != -1){ 
			if(strcmp(b->livros.info[i].info.titulo, livro.titulo)==0){ 
				//strcpy(livro->titulo, b->livros.info[i].info.titulo); 
				*ver = 2;
				break;
			}
			i = b->livros.info[i].prox; 
		}
	}
}


/* FUNCAO PARA BUSCAR UM ALUNO PELO SEU NUMERO USP */
void verificaNumUSP(BIBLIOTECA *b, ALUNO *aluno, int *ver){ 
	
	int i;
	i = b->alunos.inicio;

	*ver = 1;
	

	if (i == -1){
		
		if(aluno->numUSP < 10000000 || aluno->numUSP > 99999999){
		*ver = 3;
	}
		return;
	}
	else {
		while (i!=-1){
			if (b->alunos.info[i].info.numUSP == aluno->numUSP){
				//*x = b->alunos.info[i].info;
				*ver = 2;
				*aluno = b->alunos.info[i].info;
				break;
			}
			i = b->alunos.info[i].prox;
		}
	}
	
	if(aluno->numUSP < 10000000 || aluno->numUSP > 99999999){
		*ver = 3;
	}
}

/* FUNCAO PARA BUSCAR UM ALUNO PELO SEU NUMERO NOME */
void verificaNome(BIBLIOTECA *b, ALUNO aluno , int *ver){
	
	int i;
	i = b->alunos.inicio;

	*ver = 1;

	if (i == -1){
		return;
	}
	else {
		while (i != -1){
			if (strcmp(b->alunos.info[i].info.nome, aluno.nome)==0){
				//*aluno = b->alunos.info[i].info;
				*ver = 2;
				break;
			}
			i = b->alunos.info[i].prox;
		}
	}
}

/* FUNCAO PARA BUSCAR UM ALUNO PELO SEU NUMERO NOME */
void verificaEmail(BIBLIOTECA *b, ALUNO aluno, int *ver){
	
	int i;
	i = b->alunos.inicio;

	*ver = 1;
	
	char verifica [7];
	strcpy(verifica, "@usp.br");
	int tamanho = strlen(aluno.email);
	int k;
	for(k=0; k < 7; k++){
		if(aluno.email[tamanho-7+k] != verifica[k]){
			*ver = 3;
			return;
		}
	}

	if (i == -1){
		
		return;
	}
	else {
		while (i != -1){
			if (strcmp(b->alunos.info[i].info.email, aluno.email)==0){
				*ver = 2; 
				break;
			}
			i = b->alunos.info[i].prox;
		}
	}

	
}

void verificaTelefone(BIBLIOTECA *b, ALUNO aluno, int *ver){

	int i, erro;
	i = b->alunos.inicio;
	char verifica[6];
	strcpy(verifica, "551899");
	int k;
	for(k=0; k< 6; k++){
		if(aluno.telefone[k] != verifica[k]){
			*ver = 4;
			return;
		}
	}

	*ver = 1;

	if (i == -1){
		erro = 1;
		return;
	}
	else {
		while (i != -1){
			if (strcmp(b->alunos.info[i].info.telefone, aluno.telefone)==0){
				*ver = 3;
				break;
			}
			i = b->alunos.info[i].prox;
		}
	}

	if(strlen(aluno.telefone)<13 || strlen(aluno.telefone)>13){
		*ver = 2;
	}

	
}

/* FUNCAO PARA INSERIR UM ALUNO NA LISTA DE ALUNOS  */
void insereAluno(BIBLIOTECA *b, ALUNO al, int *erro){  
	
	*erro = 0; 

	
	if(b->alunos.pv == -1){  
		*erro = 1; 
		return; 
	}
	else if (b->alunos.inicio == -1){ 
		b->alunos.inicio = 0; 
		b->alunos.info[b->alunos.pv].info = al; 
		b->alunos.info[b->alunos.pv].info.pos = 0; 
		b->alunos.fim = b->alunos.pv; 
		b->alunos.pv = b->alunos.info[b->alunos.pv].prox; 
		b->alunos.info[b->alunos.fim].prox = -1;  
		
	}
	else { 
		b->alunos.info[b->alunos.pv].info = al; 
		b->alunos.info[b->alunos.pv].info.pos = b->alunos.pv; 
		b->alunos.info[b->alunos.fim].prox = b->alunos.pv; 
		b->alunos.fim = b->alunos.pv;  
		b->alunos.pv = b->alunos.info[b->alunos.pv].prox; 
		b->alunos.info[b->alunos.fim].prox = -1;
	}
}


/* FUNCAO PARA REMOVER UM ALUNO DA LISTA DE ALUNOS */
void removeAluno(BIBLIOTECA *b, ALUNO aluno, int *erro){ 
	
	int i, aux;

	i = b->alunos.inicio;

	aux = i;

	while (i!=-1){
		if (b->alunos.info[i].info.numUSP == aluno.numUSP){
		
			if (b->alunos.inicio == i && b->alunos.fim != i){
				b->alunos.inicio = b->alunos.info[b->alunos.inicio].prox;
				b->alunos.info[i].prox = b->alunos.pv;
				b->alunos.pv = i;
			}
			else if(b->alunos.fim == i && b->alunos.inicio != i){
				b->alunos.fim = aux;
				b->alunos.info[aux].prox = -1;
				b->alunos.info[i].prox = b->alunos.pv;
				b->alunos.pv = i;
			}
			else if (b->alunos.inicio == i && b->alunos.fim == i){
				criaBiblioteca(b);
			} else {
				b->alunos.info[aux].prox = b->alunos.info[i].prox;
				b->alunos.info[i].prox = b->alunos.pv;
				b->alunos.pv = i;
			}
			return;
		}
		aux = i;
		i = b->alunos.info[i].prox;
	}
		
}

/*  FUNCAO PARA INSERIR UM LIVRO NA LISTA DE LIVROS */
void insereLivro(BIBLIOTECA *b, LIVRO li, int *erro){

	*erro = 0;

	if(b->livros.pv==-1){ 
		*erro = 1; 
		return; 
	}
	else if (b->livros.inicio == -1){ 
		b->livros.inicio = 0; 
		b->livros.info[b->livros.pv].info = li; 
		b->livros.info[b->livros.pv].info.pos = 0; 
		b->livros.fim = b->livros.pv; 
		b->livros.pv = b->livros.info[b->livros.pv].prox; 
		b->livros.info[b->livros.fim].prox = -1; 
		
	}
	else{ 
		b->livros.info[b->livros.pv].info = li; 
		b->livros.info[b->livros.pv].info.pos = b->livros.pv;
		b->livros.info[b->livros.fim].prox = b->livros.pv; 
		b->livros.fim = b->livros.pv; 
		b->livros.pv = b->livros.info[b->livros.pv].prox; 
		b->livros.info[b->livros.fim].prox = -1; 
	}
}



/* FUNCAO PARA REMOVER UM LIVRO DA LISTA DE LIVROS */
void removeLivro(BIBLIOTECA *b, LIVRO x, int *erro){ 
	
	int i, aux; 
	i = b->livros.inicio; 
	aux = i;

	*erro = 1; 

	while (i != -1){ 
		if (b->livros.info[i].info.ISBN == x.ISBN){
			*erro = 0; 

			if (b->livros.inicio == i && b->livros.fim != i){ 
				b->livros.inicio = b->livros.info[b->livros.inicio].prox; 
				b->livros.info[i].prox = b->livros.pv; 
				b->livros.pv = i; 
			}
			else if (b->livros.fim == i && b->livros.inicio != i){ 
				b->livros.fim = aux; 
				b->livros.info[aux].prox = -1; 
				b->livros.info[i].prox = b->livros.pv;  
				b->livros.pv = i; 
			}
			else if (b->livros.inicio == i && b->livros.fim == i){ 
				criaBiblioteca(b); 
			} 
			else { 
				b->livros.info[aux].prox = b->livros.info[i].prox; 
				b->livros.info[i].prox = b->livros.pv; 
				b->livros.pv = i; 
			}
		return;
		}
		aux = i; 
		i = b->livros.info[i].prox; 
	}
}

/* FUNCAO PARA INSERIR UM LIVRO NA LISTA DE EMPRSETIMOS */
void InsereEmprestimos(BIBLIOTECA *b, LIVRO *li, ALUNO *al, int *erro){ 
	
	if(b->emprestimos.pv == -1){
		*erro = 1;
	}
	else {
		*erro = 0;
	
		if (al->inicio == -1){
			al->inicio = b->emprestimos.pv;
			al->fim = b->emprestimos.pv;
			b->emprestimos.info[b->emprestimos.pv].info = *li;
			b->emprestimos.pv = b->emprestimos.info[b->emprestimos.pv].prox;
			b->emprestimos.info[al->fim].prox = -1;
		}
		else {
			b->emprestimos.info[al->fim].prox = b->emprestimos.pv;
			al->fim = b->emprestimos.pv;
			b->emprestimos.info[b->emprestimos.pv].info = *li;
			b->emprestimos.pv = b->emprestimos.info[b->emprestimos.pv].prox;
			b->emprestimos.info[al->fim].prox = -1;		
		}	
	}
}

/* FUNCAO PARA INSERIR UM ALUNO NA LISTA DE EMPRESTADOS */
void InsereEmprestados(BIBLIOTECA *b, LIVRO *li, ALUNO *al, int *erro){ 
	
	if (b->emprestados.pv == -1){
		*erro = 1;
	}
	else {
		*erro = 0;
	
		if (li->iniemp == -1){
			li->iniemp = b->emprestados.pv;
			li->fimemp = b->emprestados.pv;
			b->emprestados.info[b->emprestados.pv].info = *al;		
			b->emprestados.pv = b->emprestados.info[b->emprestados.pv].prox;
			b->emprestados.info[li->fimemp].prox = -1;
		}
		else{
			b->emprestados.info[li->fimemp].prox = b->emprestados.pv;
			li->fimemp = b->emprestados.pv;
			b->emprestados.info[b->emprestados.pv].info = *al;
			b->emprestados.pv = b->emprestados.info[b->emprestados.pv].prox;	
			b->emprestados.info[li->fimemp].prox = -1;	
		}	
	}
}


/* FUNCAO PRA REMOVER UM ALUNO DA LISTA DE EMPRESTADOS */
void RemoveEmprestado(BIBLIOTECA *b, LIVRO *li, ALUNO al, int *erro){
	
	int i, aux;

	i = li->iniemp;

	aux = i;
	while (i!=-1){
		if (b->emprestados.info[i].info.numUSP == al.numUSP){
		
			if (li->iniemp == i && li->fimemp!=i){
				li->iniemp = b->emprestados.info[li->iniemp].prox;
				b->emprestados.info[i].prox = b->emprestados.pv;
				b->emprestados.pv = i;
			} 
			else if(li->fimemp == i && li->iniemp != i){
				li->fimemp = aux;
				b->emprestados.info[aux].prox = -1;
				b->emprestados.info[i].prox = b->emprestados.pv;
				b->emprestados.pv = i;
			}
			else if(li->iniemp == i && li->fimemp == i){
				li->iniemp = -1;
				li->fimemp = -1;
			}
			else{
				b->emprestados.info[aux].prox = b->emprestados.info[i].prox;
				b->emprestados.info[i].prox = b->emprestados.pv;
				b->emprestados.pv = i;
			}
			return;
		}
		aux = i;
		i = b->emprestados.info[i].prox;
	}


}

/* FUNCAO PARA CHECAR SE UM ALUNO ESTA COM UM LIVRO EMPRESTADO */
int EstaEmprestado(BIBLIOTECA *b, LIVRO *livro, ALUNO aluno){ 

	int i;
	i = livro->iniemp;

	if (i == -1){
		return 1;
	}
	else{
		while (i!=-1){
			if (b->emprestados.info[i].info.numUSP == aluno.numUSP){
				return 0;
			}
			i = b->emprestados.info[i].prox;
		}
	}
	return 1;
}

/* FUNCAO PARA INSERIR UM ALUNO NA LISTA DE ESPERA */
void insereEspera(BIBLIOTECA *b, LIVRO *li, ALUNO *al, int *erro){ 
	
	
	if(b->espera.pv == -1){
		*erro = 1;
	}
	else {
		*erro = 0;
		if (li->iniesp==-1){
			li->iniesp = b->espera.pv;
			li->fimesp = b->espera.pv;
			b->espera.info[b->espera.pv].info = *al;
			b->espera.pv = b->espera.info[b->espera.pv].prox;
			b->espera.info[li->fimesp].prox = -1;
		}
		else{
			b->espera.info[li->fimesp].prox = b->espera.pv;
			li->fimesp = b->espera.pv;
			b->espera.info[b->espera.pv].info = *al;
			b->espera.pv = b->espera.info[b->espera.pv].prox;
			b->espera.info[li->fimesp].prox = -1;		
		}	
	}
}

/* FUNCAO PARA CHECAR SE UM ALUNO ESTA NA LISTA DE ESPERA DE UM LIVRO */
int EstaNaEspera(BIBLIOTECA *b, LIVRO *livro, ALUNO aluno){  
	
	int i;

	i = livro->iniesp;

	if (i == -1){
		return 1;
	}
	else {
		while (i !=- 1){
			if (b->espera.info[i].info.numUSP == aluno.numUSP){
				return 0;
			}
			i = b->espera.info[i].prox;
		}
	}
	return 1;
}

/* FUNCAO PARA REMOVER UM ALUNO DA LISTA DE ESPERA */
void RemoveEspera(BIBLIOTECA *b, LIVRO *li, ALUNO al, int *erro){
	
	int i, aux;

	i = li->iniesp;

	aux = i;

	while (i!=-1){
		if (b->espera.info[i].info.numUSP == al.numUSP){
		
			if (li->iniesp == i && li->fimesp!=i){
				li->iniesp = b->espera.info[li->iniesp].prox;
				b->espera.info[i].prox = b->espera.pv;
				b->espera.pv = i;
			}
			else if(li->fimesp == i && li->iniesp!=i){
				li->fimesp = aux;
				b->espera.info[aux].prox = -1;
				b->espera.info[i].prox = b->espera.pv;
				b->espera.pv = i;
			}
			else if(li->iniesp == i && li->fimesp == i){
				li->iniesp = -1;
				li->fimesp = -1;
			} else {
				b->espera.info[aux].prox = b->espera.info[i].prox;
				b->espera.info[i].prox = b->espera.pv;
				b->espera.pv = i;
			}
		return;
		}
		aux = i;
		i = b->espera.info[i].prox;
	}
}
