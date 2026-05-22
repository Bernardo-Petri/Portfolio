#include <stdio.h> 
#include <stdlib.h> 
#include <wchar.h> 
#include <locale.h>
#include <time.h>

int potencia2 (int);
void correcao(wchar_t *);
void nomescompetidores(wchar_t **, wchar_t *, int);
int potenciade2(int);
void fasedotorneio(int);
int simulacao(wchar_t **, int *, int, int, int, int);

int main(){
	setlocale(LC_ALL, "Portuguese");
	int quant, pot, vencedor;
	int * posComps;
	wchar_t ** competidores;
	wchar_t * nometemp;
	wchar_t car;
	nometemp = (wchar_t *) malloc( sizeof(wchar_t) * 80);
	wprintf(L"Digite o número de competidores (um número deve ser uma potência de 2): ");
	scanf("%d", &quant);
	pot = potencia2(quant);
	while(pot){
		wprintf(L"O número que você digitou não é válido, por favor digite um número válido (uma potência de 2): ");
		scanf("%d", &quant);
		pot = potencia2(quant);
	}
	car = getchar();
	competidores = (wchar_t **) malloc( sizeof(wchar_t *) * quant );
	posComps = (int *) malloc(sizeof(int) * quant);
	for(int i = 0 ; i < quant ; ++i){
		( *(posComps+i) ) = 1;
	}
	printf("\nDigite os nomes dos competidores:\n");
	nomescompetidores(competidores, nometemp, quant);
	printf("\n\n");
	vencedor = simulacao(competidores, posComps, quant, 0, quant-1, 0); 
	wprintf(L"\n\nO Campeão do Torneio é: %ls\n\n", *(competidores+vencedor) );
	
	free(nometemp); // nometemp
	for(int i = 0 ; i < quant ; ++i){
		free(*(competidores+i)); 
	}
	free(competidores); // competidores
	free(posComps);
	return 0;
} 

int potencia2 (int quant){
	while(quant!=1){
		if(quant%2 == 1){
			return 1;
		}
		quant /= 2;
	}
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

void nomescompetidores(wchar_t ** competidores, wchar_t * nometemp, int quant){
	wchar_t * aux; 
	int tam;
	for(int i = 0 ; i < quant ; ++i){
		wprintf(L"Competidor nº %d: ", (i+1) );
		fgetws(nometemp, 80, stdin);
		correcao(nometemp);
		tam = wcslen(nometemp);
		*(competidores+i) = (wchar_t *) malloc( sizeof(wchar_t) * tam );
		aux = *(competidores+i) ;
		wcscpy(aux, nometemp);
	} 
} 

int potenciade2(int fase){
	int pot = 1;
	for(int i = 0; i < fase; ++i){
		pot *= 2;
	}
	return pot;
}

void fasedotorneio(int fase){
	if(fase == 0){
		printf("Finais\n");
	}
	else if(fase == 1){
		printf("Semi-Finais\n");
	}
	else if(fase > 1){
		int pot = potenciade2(fase);
		printf("%das de Finais\n", pot);
	}
}

int simulacao(wchar_t ** competidores, int * posComps, int quant, int i, int j, int fase){
	int m = (i+j)/2 ;
	if(i<j){
		int comp1, comp2, vencedor, c1, c2;
		c1 = simulacao(competidores, posComps, quant, i, m, fase+1);
		c2 = simulacao(competidores, posComps, quant, m+1, j, fase+1);
		comp1 = 0;
		comp2 = 0;
		for(int i2 = i; i2 <= j; ++i2){
			if( ( *(posComps+i2) ) && ( !(comp1) ) )
				comp1 = i2;
			else if( ( *(posComps+i2) ) && ( !(comp2) ) )
				comp2 = i2;
		}
		srand(time(NULL));
		vencedor = rand();
		vencedor = vencedor%2;
		if(vencedor){
			*(posComps+comp2) = 0;
			fasedotorneio(fase);
			wprintf(L"%ls X %ls\n", *(competidores+comp1) , *(competidores+comp2) );
			wprintf(L"Vencedor da rodada: %ls\n", *(competidores+comp1) );
			printf("==========================\n");
			*(posComps+comp2) = 0; 
			return comp1;
		}
		else{
			*(posComps+comp1) = 0;
			fasedotorneio(fase);
			wprintf(L"%ls X %ls\n", *(competidores+comp1) , *(competidores+comp2) );
			wprintf(L"Vencedor da rodada: %ls\n", *(competidores+comp2) );
			printf("==========================\n");
			*(posComps+comp1) = 0; 
			return comp2;
		}
	}
	else{
		return 0;
	}
}