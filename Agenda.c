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
	wchar_t nome[41];
	char tel[16], cel[16], e_mail[41];
	struct data nasc;
	struct contato * next;
};

void correcao(wchar_t *);
struct contato * busca(struct contato *, wchar_t *);
struct contato * InsereElem (wchar_t *);
void insere (struct contato **, wchar_t *, char *, char *, char *, int, int);
void printaagenda(struct contato *);
void edita(struct contato **, wchar_t *, char *, char *, char *, int, int);
void remover(struct contato **, wchar_t *);
void desaloca(struct contato **);

int main (){
	setlocale(LC_ALL, "Portuguese");
	int opcao = 0;
	char pegaChar;
	char teltemp[16], celtemp[16], emailtemp[41];
	wchar_t nometemp[41];
	int diatemp, mestemp;
	struct contato * phead = NULL;
	wprintf(L"#Aviso: os nomes dos contatos e os e-mails devem ter no máximo 40 caracteres\n#");
	wprintf(L"As opções são:\n1 - Inserir Contato\n2 – Listar Contatos\n3 – Buscar Contato\n4 – Editar Contato\n5 – remover Contato\n");
	wprintf(L"6– removerr Contatos Duplicados\n7– Sair\n");
	wprintf(L"Digite um número de opção: ");
	scanf("%d",&opcao);
	while(opcao>7){
		wprintf(L"Opção inválida. Tente Novamente. ");
		scanf("%d",&opcao);
	}
	while(opcao!=7){
		pegaChar = getchar();
		if(opcao==1){
			printf("1- Inserir\nDigite o nome do contato: ");
			fgetws(nometemp, 41, stdin);
			correcao(nometemp);
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
			fgetws(nometemp, 41, stdin);
			correcao(nometemp);
			if(busca(phead, nometemp)){
				wprintf(L"%ls existe na agenda.\n", nometemp);
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
				wprintf(L"Digite a Nova data de Nascimento (DIA e MÊS): ");
				scanf("%d", &diatemp);
				scanf("%d", &mestemp);
				edita(&phead, nometemp, teltemp, celtemp, emailtemp, diatemp, mestemp);
				wprintf(L"Edição feita com sucesso.\n");
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

void correcao(wchar_t * nome){
	int i;
	wchar_t car;
	for(i = 0; ( *(nome+i) )!='\n' ; ++i){
		car = *(nome+i);
		switch (car){
			case 160:
				*(nome+i) = L'á';
				break;
			case 8218:
				*(nome+i) = L'é';
				break;
			case 161:
				*(nome+i) = L'í';
				break;
			case 162:
				*(nome+i) = L'ó';
				break;
			case 163:
				*(nome+i) = L'ú';
				break;
			case 402:
				*(nome+i) = L'â';
				break;
			case 710:
				*(nome+i) = L'ê';
				break;
			case 338:
				*(nome+i) = L'î';
				break;
			case 8220:
				*(nome+i) = L'ô';
				break;
			case 8211:
				*(nome+i) = L'û';
				break;
			case 198:
				*(nome+i) = L'ã';
				break;
			case 228:
				*(nome+i) = L'õ';
				break;
			case 8230:
				*(nome+i) = L'à';
				break;
			case 352:
				*(nome+i) = L'è';
				break;
			case 141:
				*(nome+i) = L'ì';
				break;
			case 8226:
				*(nome+i) = L'ò';
				break;
			case 8212:
				*(nome+i) = L'ù';
				break;
			case 183:
				*(nome+i) = L'À';
				break;
			case 212:
				*(nome+i) = L'È';
				break;
			case 222:
				*(nome+i) = L'Ì';
				break;
			case 227:
				*(nome+i) = L'Ò';
				break;
			case 235:
				*(nome+i) = L'Ù';
				break;
			case 199:
				*(nome+i) = L'Ã';
				break;
			case 229:
				*(nome+i) = L'Õ';
				break;
			case 182:
				*(nome+i) = L'Â';
				break;
			case 210:
				*(nome+i) = L'Ê';
				break;
			case 215:
				*(nome+i) = L'Î';
				break;
			case 226:
				*(nome+i) = L'Ô';
				break;
			case 234:
				*(nome+i) = L'Û';
				break;
			case 181:
				*(nome+i) = L'Á';
				break;
			case 144:
				*(nome+i) = L'É';
				break;
			case 214:
				*(nome+i) = L'Í';
				break;
			case 224:
				*(nome+i) = L'Ó';
				break;
			case 233:
				*(nome+i) = L'Ú';
				break;
			case 8225:
				*(nome+i) = L'ç';
				break;
			case 8364:
				*(nome+i) = L'Ç';
		}
	}
	*(nome+i) = '\0';
}

void printaagenda(struct contato * p){
	if(p){      // contato: nome, tel, cel, e_mail; data: dia, mes
		wprintf(L"Nome: %ls\n",  p->nome);
		printf("Telefone: %s\nCelular: %s\nE-Mail: %s\nData: %2d/%2d\n", p->tel, p->cel, p->e_mail, p->nasc.dia, p->nasc.mes);
		printf("===================\n");
		printaagenda(p->next);
	}
	else{
		printf("FIM DA LISTA\n\n");
	}
}

struct contato * busca(struct contato * P, wchar_t * N){
	if(P){
		if((wcscmp(P->nome,N))!=0){
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

void edita(struct contato ** p, wchar_t * N, char * T, char * C, char * E, int D, int M){
	if((*p)&&((wcscmp(N,(*p)->nome))!=0)){
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

struct contato * InsereElem (wchar_t * N){
	struct contato * p1 = NULL;
	p1 = malloc(sizeof(*p1));
	wcscpy (p1->nome, N);
	return p1;
}

void insere (struct contato ** p, wchar_t * N, char * T, char * C, char * E, int D, int M){
	if((*p)&&((wcscmp((*p)->nome,N))<0)){
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

void remover(struct contato ** p, wchar_t * N){
	if((*p)&&((wcscmp(N,(*p)->nome))!=0)){
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