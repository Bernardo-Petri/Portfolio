/*
Objetivo: Criar uma lista de contatos personalizada
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <locale.h>
#include <wchar.h>

struct data{
	int dia, mes;
};

struct contato{
	char nome[41], tel[16], cel[16], e_mail[41];
	struct data nasc;
	struct contato * next;
};

struct contato * busca(struct contato *, char *);
struct contato * InsereElem (char *);
void insere (struct contato **, char *, char *, char *, char *, int, int);
void printaagenda(struct contato *);
void edita(struct contato **, char *, char *, char *, char *, int, int);
void remover(struct contato **, char *);
void desaloca(struct contato **);

int main (){
	setlocale(LC_ALL, "Portuguese");
	int opcao = 0;
	char nometemp[41], teltemp[16], celtemp[16], emailtemp[41];
	int diatemp, mestemp;
	struct contato * phead = NULL;
	wprintf(L"#Aviso: os nomes dos contatos e os e-mails devem ter no máximo 40 caracteres\n#");
	wprintf(L"As opções são:\n1 - Inserir Contato\n2 – Listar Contatos\n3 – Buscar Contato\n4 – Editar Contato\n5 – removerr Contato\n");
	wprintf(L"6– removerr Contatos Duplicados\n7– Sair\n");
	wprintf(L"Digite um número de opção: ");
	scanf("%d",&opcao);
	while(opcao>7){
		wprintf(L"Opção inválida. Tente Novamente. ");
		scanf("%d",&opcao);
	}
	while(opcao!=7){
		if(opcao==1){
			printf("1- Inserir\nDigite o nome do contato: ");
			scanf("%s", nometemp);
			if (busca(phead, nometemp)){
				wprintf(L"Contato já existente.\n");
			}
			else{
				printf("Digite o Telefone: ");
				scanf("%s", teltemp);
				printf("Digite o Celular: ");
				scanf("%s", celtemp);
				printf("Digite o E-Mail: ");
				scanf("%s", emailtemp);
				wprintf(L"Digite a data de Nascimento (DIA e MÊS): ");
				scanf("%d", &diatemp);
				scanf("%d", &mestemp);
				insere(&phead, nometemp, teltemp, celtemp, emailtemp, diatemp, mestemp);
			}
			wprintf(L"Digite um número de opção: ");
			scanf("%d",&opcao);
		}
		else if(opcao==2){
			printf("2- Listar Contatos\nAgenda:\n");
			printaagenda(phead);
			wprintf(L"Digite um número de opção: ");
			scanf("%d",&opcao);
		}
		else if(opcao==3){
			printf("3- Buscar Contato\nDigite o nome do contato: ");
			scanf("%s", nometemp);
			if(busca(phead, nometemp)){
				printf("%s existe na agenda.\n", nometemp);
			}
			else{
				printf("Contato Inexistente.\n");
			}
			wprintf(L"Digite um número de opção: ");
			scanf("%d",&opcao);
		}
		else if(opcao==4){
			printf("4- Editar Contato\nDigite o nome do contato: ");
			scanf("%s", nometemp);
			if(busca(phead, nometemp)){
				printf("%s existe na agenda.\n", nometemp);
				printf("Digite o Novo Telefone: ");
				scanf("%s", teltemp);
				printf("Digite o Novo Celular: ");
				scanf("%s", celtemp);
				printf("Digite o Novo E-Mail: ");
				scanf("%s", emailtemp);
				printf("Digite a Nova data de Nascimento (DIA e MÊS): ");
				scanf("%d", &diatemp);
				scanf("%d", &mestemp);
				edita(&phead, nometemp, teltemp, celtemp, emailtemp, diatemp, mestemp);
				printf("Edição feita com sucesso.\n");
			}
			else{
				printf("Contato Inexistente.\n");
			}
			wprintf(L"Digite um número de opção: ");
			scanf("%d",&opcao);
		}
		else if(opcao==5){
			printf("5- Remover Contato\nDigite o nome do contato: ");
			scanf("%s", nometemp);
			if(busca(phead, nometemp)){
				remover(&phead, nometemp);
				printf("Contato Removido\n");
			}
			else{
				printf("Contato Inexistente.\n");
			}
			wprintf(L"Digite um número de opção: ");
			scanf("%d",&opcao);
		}
		else if(opcao==6){
			wprintf(L"6 - remover Contatos Duplicados (Opção Indisponível)\n");
			wprintf(L"Digite um número de opção: ");
			scanf("%d",&opcao);
		}
		else if(opcao>7){
			while (opcao>7){
				wprintf(L"Opção inválida. Tente Novamente. ");
				scanf("%d",&opcao);
			}
		}
	}
	printf("\n\nAgenda Atual: \n");
	printaagenda(phead);
	desaloca(&phead);
	wprintf(L"\n\nAgenda Atual 2 (Verificação): \n");
	printaagenda(phead);
	return 0;
}

void printaagenda(struct contato * p){
	if(p){      // contato: nome, tel, cel, e_mail; data: dia, mes
		printf("Nome: %s\nTelefone: %s\nCelular: %s\nE-Mail: %s\nData: %2d/%2d\n", p->nome, p->tel, p->cel, p->e_mail, p->nasc.dia, p->nasc.mes);
		printaagenda(p->next);
	}
	else{
		printf("FIM DA LISTA\n\n");
	}
}

struct contato * busca(struct contato * P, char * N){
	if(P){
		if((strcmp(P->nome,N))!=0){
			return busca(P->next, N);
		}
		else{
			return(P);
		}
		
	}
	else{
		return NULL;
	}
}

void edita(struct contato ** p, char * N, char * T, char * C, char * E, int D, int M){
	if((*p)&&((strcmp(N,(*p)->nome))!=0)){
		edita(&((*p)->next),N, T, C, E, D, M);
	}
	else{
		strcpy ((*p)->tel, T);
		strcpy ((*p)->cel, C);
		strcpy ((*p)->e_mail, E);
		((*p)->nasc.dia) = D;
		((*p)->nasc.mes) = M;
	}
}

struct contato * InsereElem (char * N){
	struct contato * p1 = NULL;
	p1 = malloc(sizeof(*p1));
	strcpy (p1->nome, N);
	return p1;
}

void insere (struct contato ** p, char * N, char * T, char * C, char * E, int D, int M){
	if((*p)&&((strcmp((*p)->nome,N))<0)){
		insere(&((*p)->next), N, T, C, E, D, M);
	}
	else{
		struct contato * p1 = NULL;
		p1 = InsereElem (N);
		strcpy (p1->tel, T);
		strcpy (p1->cel, C);
		strcpy (p1->e_mail, E);
		(p1->nasc.dia) = D;
		(p1->nasc.mes) = M;
		(p1->next) = (*p);
		(*p) = p1;
	}
}

void remover(struct contato ** p, char * N){
	if((*p)&&((strcmp(N,(*p)->nome))!=0)){
		remover(&((*p)->next), N);
	}
	else{    // contato : tel[16], cel[16], e_mail[41]; data dia, mes;
		struct contato * p1 = NULL;
		p1 = (*p);
		(*p) = (p1->next);
		free(p1);
	}
}

void desaloca(struct contato ** p){
	if(*p){
		desaloca(&((*p)->next));
		free(*p);
		(*p) = NULL;
	}
}