//LUIZ FLÁVIO PEREIRA   RA91706
//MARCOS VINICIUS PERES RA94594

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 20 //aqui define-se o tamanho do triangulo de pascal/matriz. 
//Obs: O triangulo de pascal funcionará para qualquer tamanho informado no define, porém, esteticamente falando, para valores maiores que 22 a visualização poderá ser comprometida no MS-DOS

//manutenção do menu principal
char showmenu(char opcao){
	for(int i = 0; i < 120; i++) printf("=");
	printf("\t\t\t\t\t\t   Triangulo de Pascal\n[1] Criar Triangulo de Pascal\n[2] Imprimir Triangulo de Pascal\n[3] Resetar Triangulo de Pascal\n\n\n[S/s/0]Sair\n");
	for(int i = 0; i < 120; i++) printf("=");
	printf("Opcao: ");
	fflush(stdin);
	scanf("%c", &opcao);
	
	return opcao;
}

//funcao responsavel por criar o triangulo de pascal, ou seja, fazer os calculos e preencher todos os valores da matriz
void cria_trPascal(int trPascal[TAMANHO][TAMANHO]){
	for(int linha = 0; linha < TAMANHO; linha++){
		for(int coluna = 0; coluna < TAMANHO; coluna++){
			//preenche a borda do triangulo de pascal com 1
			if(coluna == 0 or linha == 0){
				trPascal[linha][coluna] = 1;
			}else{
				//preenche o interior do traingulo de pascal dinamicamente a partir dos valores menores já salvos na 'tabela'/matriz não necessitando recalculá-los
				if(coluna < (TAMANHO - linha)){
					trPascal[linha][coluna] = (trPascal[linha][coluna - 1]) + (trPascal[linha - 1][coluna]);//essa parte é que caracteriza programação dinamica (problema menor ja resolvido sendo usado para resolver um problema maior de maneira simples)
				}
			}
		}
	}	
	printf("Triangulo de Pascal criado com sucesso!\n");
}

//essa funcao armazena num vetor o tamanho/quantidade de digitos tem os numeros da ultima linha(maiores numeros do triangulo de pascal)
void recebe_tamanhosUltimaColuna(int trPascal[][TAMANHO], int armazena_TamanhoValores[]){
	int coluna = 0;
	for(int linha = 0; linha < TAMANHO; linha++){
		coluna = (TAMANHO - (linha + 1));
		if(trPascal[linha][coluna] >= 0 && trPascal[linha][coluna] < 10){
			armazena_TamanhoValores[linha] = 1;	
		}else{
			if(trPascal[linha][coluna] > 9 && trPascal[linha][coluna] < 100){
				armazena_TamanhoValores[linha] = 2;	
			}else{
				if(trPascal[linha][coluna] > 99 && trPascal[linha][coluna] < 1000){
					armazena_TamanhoValores[linha] = 3;	
				}else{
					if(trPascal[linha][coluna] > 999 && trPascal[linha][coluna] < 10000){
						armazena_TamanhoValores[linha] = 4;	
					}else{
						if(trPascal[linha][coluna] > 9999 && trPascal[linha][coluna] < 100000){
							armazena_TamanhoValores[linha] = 5;	
						}else{
							if(trPascal[linha][coluna] > 99999 && trPascal[linha][coluna] < 1000000){//optei por fazer tratativas ate um valor < 1000000, quanto maior
								armazena_TamanhoValores[linha] = 6;	
							}
						}
					}
				}
			}
		}
	}
}

//funcao que calcula quantos espaços serão dados antes da impressão do numero, é pego o tamanho do maior numero menos o tamanho do valor a ser impresso.
void corrige_Formatacao(int armazena_TamanhoValores[], int indice, int valor){
	int repete_laco = 0;
	if(valor >= 0 && valor < 10){
		repete_laco = armazena_TamanhoValores[indice] - 1;	
	}else{
		if(valor > 9 && valor < 100){
			repete_laco = armazena_TamanhoValores[indice] - 2;
		}else{
			if(valor > 99 && valor < 1000){
				repete_laco = armazena_TamanhoValores[indice] - 3;
			}else{
				if(valor > 999 && valor < 10000){
					repete_laco = armazena_TamanhoValores[indice] - 4;
				}else{
					if(valor > 9999 && valor < 100000){
						repete_laco = armazena_TamanhoValores[indice] - 5;
					}else{
						if(valor > 99999 && valor < 1000000){//optei por fazer tratativas ate um valor < 1000000, quanto maior
							repete_laco = armazena_TamanhoValores[indice] - 6;
						}
					}
				}
			}
		}
	}
	//imprimindo a quantidade exata de espaços antes de imprimir o valor de fato...
	for(int qtdeEspacos = 0; qtdeEspacos < repete_laco; qtdeEspacos++)
		printf(" ");
}

//funcao responsavel por fazer a impressão dos valores salvos na matriz. 
//Obs: Valores = 0 não serão impressos para deixar a visualização menos poluída
void imprime_trPascal(int trPascal[][TAMANHO]){
	if(trPascal[0][0] == 0){
		printf("O Triangulo de Pascal Ainda Nao Foi Gerado!\n");
	}else{
		int armazena_TamanhoValores[TAMANHO] = {}; //inicializa todo o vetor com zero
		recebe_tamanhosUltimaColuna(trPascal, armazena_TamanhoValores);
		
		//percorre a matriz corrigindo a formatação e imprimindo os valores da matriz
		for(int linha = 0; linha < TAMANHO; linha++){
			for(int coluna = 0; coluna < TAMANHO; coluna++){
				if(trPascal[linha][coluna] != 0){
					//prenche com espaços vazios antes do valor do triangulo de pascal
					corrige_Formatacao(armazena_TamanhoValores, coluna, trPascal[linha][coluna]);
					//imprimindo o valor do triangulo de pascal após os espaços
					printf("%d ", trPascal[linha][coluna]);
				}		
			}
			printf("\n");
		}	
	}		
}

//faz com que toda a matriz receba 0, em todas as posições
void reseta_trPascal(int trPascal[][TAMANHO]){
	for(int linha = 0; linha < TAMANHO; linha++){
		for(int coluna = 0; coluna < TAMANHO; coluna++){
			trPascal[linha][coluna] = 0;
		}
	}
	printf("Triangulo de Pascal 'Excluido' Com Sucesso!\n");
}

//programa principal
int main(void){
	int trPascal[TAMANHO][TAMANHO] = {};//inicializa toda a matriz com zero
	
	char opcao = showmenu(opcao); 
	while(opcao != 's' && opcao != 'S' && opcao != '0'){
		system("cls");
		switch (opcao){
			case '1':
				cria_trPascal(trPascal);
				break;
			case '2': 
				imprime_trPascal(trPascal);	
				break;
			case '3':
				reseta_trPascal(trPascal);
				break;
			default :
				printf("Opcao invalida!\n");
				break;
		}
		opcao = showmenu(opcao);
	}
}
