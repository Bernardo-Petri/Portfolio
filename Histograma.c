#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define MAX 100000 
#define EMPAL 1
#define FORAPAL 0

struct pals {
	char * pal;
	int cont;
	struct pals * next;
};

void constroi (struct pals **, char *, char *, int);
struct pals * busca(struct pals **, char *);
void insere (struct pals **, char *);
struct pals * insereElem (char *);
void printaLista (struct pals *);
void desaloca(struct pals **);
struct pals * busca(struct pals **, char *);

int main (){
	int i=0, c;
	char ent[MAX];
	char paltemp[1024];
	struct pals * phead = NULL;
	printf("Para terminar de digitar, aperte: Ctrl+Z\n");
	printf("Digite as palavras: \n");
	while ((i<MAX-1)&&((c = getchar()) != EOF)){
		ent[i++]=c;
	}
	ent[i]='\0';
	printf("\n\nArray ent: %s \n\n", ent);
	constroi (&phead, ent, paltemp, i);
	printaLista (phead);
	desaloca(&phead);
	printf("\n\n");
	printaLista (phead);
	return 0;
}

void desaloca(struct pals ** p){
	struct pals * p1 = (*p);
	while(*p){
		(*p) = (p1->next);
		free(p1->pal);
		free(p1);
		p1 = (*p);
	}
}

void printaLista (struct pals * p){
	while(p){
		printf("%s\t\t%d\n", p->pal, p->cont);
		p = (p->next);
	}
}

struct pals * busca(struct pals ** p, char * P){
	while((*p)&&(strcmp(P,(*p)->pal)!=0)){
		p=(&((*p)->next));
	}
	if (*p){
		return *p;
	}
	else{
		return NULL;
	}
}

struct pals * insereElem (char * P){
	struct pals * p;
	int n;
	p = malloc(sizeof(*p));
	(p->cont)=1;
	n = (strlen(P)+1);
	(p->pal)= malloc(n*sizeof(char));
	strcpy(p->pal,P);
	return p;
}

void insere (struct pals ** p, char * P){
	int n1, n2, c1;
	char * vet1, * vet2, c;
	int i=0;
	vet2=NULL;
	n1 = (strlen(P)+1);
	vet1 = malloc(n1*sizeof(char));
	while(P[i]){
		c = P[i];
		vet1[i] = tolower(c);
		i++;
	}
	vet1[i]='\0';
	i=0;
	if(*p){
		n2 = (strlen((*p)->pal)+1);
		vet2 = malloc(n2*sizeof(char));
		while(*(((*p)->pal)+i)){
			c = *(((*p)->pal)+i);
			vet2[i] = tolower(c);
			i++;
		}
		vet2[i]='\0';
		i=0;
	}
	i=0;		
	while((*p)&&(strcmp(vet1,vet2)>0)){
		p=(&((*p)->next));
		free(vet2);
		if (*p){
			n2 = (strlen((*p)->pal)+1);
			vet2 = malloc(n2*sizeof(char));
			while(*(((*p)->pal)+i)){
				c = *(((*p)->pal)+i);
				vet2[i] = tolower(c);
				i++;
			}
			vet2[i]='\0';
			i=0;
		}
		else{
			vet2 = NULL;
		}
	}
	free(vet1);
	if(vet2){
		free(vet2);
	}
	struct pals * p1;
	p1 = insereElem (P);
	(p1->next)=(*p);
	(*p)=(p1);
}

void constroi (struct pals ** p, char * N, char * P, int lim){
	int i=0, j=0, c=0, sit = FORAPAL;
	struct pals * p1 = NULL;
	while (N[i]!='\0'){
		while ((N[i]==' ')||(N[i]==',')||(N[i]=='.')||(N[i]=='-')||(N[i]==';')||(N[i]==':')||(N[i]=='!')||(N[i]=='\n')||(N[i]=='\t')){
			i++;
		}
		while((N[i]!=' ')&&(N[i]!=',')&&(N[i]!='.')&&(N[i]!='-')&&(N[i]!=';')&&(N[i]!=':')&&(N[i]!='!')&&(N[i]!='\n')&&(N[i]!='\t')&&(N[i]!='\0')){
			P[j++]=N[i++];
		}
		if(j>0){
			sit = EMPAL;
		}
		P[j]='\0';
		if (sit){
			c+=1;
		}
		if(p1 = busca(p, P)){
			(p1->cont)++;
		}
		else{
			insere (p, P);
		}
		i++;
		j=0;
		sit = FORAPAL;
	}
}