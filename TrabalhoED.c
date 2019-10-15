#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAM 1000000

void Menu();
void gerarMassaDados();
int * lerMassaDados();
int BubbleSort(int size, int *array);
int SelectionSort(int size, int *array);
int InsertionSort(int sizeInsertion, int *arrayInsertion);
void buildMaxHeap(int*, int);
void maxHeapify(int*, int, int);
void HeapSort(int size, int* array);
void QuickSort(int *arrayQuick, int left, int right, int size);
void QuickSortInterno(int *arrayQuickInterno, int left, int right);

unsigned long int qtdComparacaoQuick = 0, qtdTrocaQuick = 0; //Declara variaveis para extração dos dados de troca e comparações
time_t tInicio, tFim;

int main () {
        Menu();
        
        return 0;
}

void Menu() {
	int option = 0;
	int valor;
	
	printf("[1] GERAR ARQUIVO\n[2] LER ARQUIVO E APLICAR ALGORITMOS\n");
	scanf ("%i", &option);
	
	switch(option) {
		case 1: gerarMassaDados();
		break;
		case 2: lerMassaDados();
		break;
		
		default: Menu();
	};
	
};

//Gera arquivo com massa de dados
//
void gerarMassaDados() {
	//variaveis
    int i, valor; //auxiliar e quantidade de dados a serem gerados no arquivo
    char filename[100]; //armazena nome que sera dado ao arquivo txt

	//input usuario
    printf ("Digite a quantidade de dados:\n");
    scanf("%i", &valor);
    
    printf("Digite o nome do arquivo de saida:\n");
    scanf("%s", filename);
    printf ("\n");

	//inicializa a função rand com valor vazio
    srand(time(NULL));

	//declara ponteiro do tipo FILE
    FILE *output;
    //abre o arquivo fazendo concatenação do nome escolhido com a extensao txt.
	//Parametro " w " para abrir e escrever.
    output = fopen(strcat(filename, ".txt"), "w" );

	//faz a geração e escreve no documento aberto
    for ( i = 0; i < valor ; i++){
        fprintf (output, "%i\n", rand() % 1000);
    }

	//fecha o arquivo
    fclose(output);
	
	//mensagem de sucesso
    printf ("Arquivo gravado !\n");
    
    //chama menu novamente
    Menu();
};
//Lê arquivo com massa de dados
//
int * lerMassaDados() {
	FILE *fp; //declara ponteiro do tipo FILE
    char str[60]; //declara array que vai ler os dados do arquivo
    int *v = (int *) malloc (TAM * sizeof(int)); //declara ponteiro e aloca ponteiro do tipo inteiro para armazenar lote de dados
    int i, count = 0; //declara ponteiro e aloca ponteiro do tipo inteiro para armazenar lote de dados
    char nomeArquivo[50]; //armazena nome do arquivo txt que sera lido

	//input usuario
    printf("Digite o nome do arquivo\n");
    scanf("%s", nomeArquivo);

	//abre arquivo
	fp = fopen(nomeArquivo , "r");
	//caso arquivo não exista, apresenta o erro e volta pro menu
	if(fp == NULL) {
		printf("Arquivo na existe !\n");
      
		Menu();
	};
   
	//caso exista, enquanto ouver dados faz armazenamento em ponteiro
	while(fgets (str, 60, fp) != NULL ) {
		v[count] = atoi(str);
		count++;
	};
   
   //imprime para verificar se arquivo foi lido corretamente
   for(i = 0 ; i < count; i ++) {
       printf ("\n%i", v[i]);
   };

	//fecha arquivo
   fclose(fp);
   
   //Aplica algoritmos de ordenação   
   //BubbleSort(count, v);
   //SelectionSort(count, v);
   //InsertionSort(count, v);
   //HeapSort(count, v);
   QuickSort(v, 0, count, count);
      
};
//Bubble Sort
//
int BubbleSort(int sizeBubble, int *arrayBubble) {
	int j, i, cont, tempBubble, tam; //Declara variaveis auxiliares
	unsigned long int qtdComparacao = 0, qtdTroca = 0; //Declara variaveis para extração dos dados de troca e comparações
	
	int *bkpArrayBubble = (int *) malloc (sizeBubble * sizeof(int)); //declara e aloca ponteiro de tamanho x
	for (i = 0 ; i < sizeBubble ; i ++) { //transcreve o array bagunçado para um bkp
		bkpArrayBubble[i] = arrayBubble[i];
	};
			
	tInicio = time(NULL); //tInicio recebe valor com hora do momento em que é chamado;
	
	//algoritmo de ordenação
	for (i = sizeBubble - 2 ; i >= 0 ; i--){
		for (j = 0 ; j <= i ; j++){
			qtdComparacao++;
			if (bkpArrayBubble[j] > bkpArrayBubble[j + 1]){
				tempBubble = bkpArrayBubble[j];
				bkpArrayBubble[j] = bkpArrayBubble[j + 1];
				bkpArrayBubble[j + 1] = tempBubble;
                qtdTroca++;
			}
		}
	};
	
	tFim = time(NULL); //tFim recebe valor com hora do momento em que é chamado
	double diff = (tFim - tInicio); //declara variavel diff e realiza conta para diferenciar os tempos.
			
	//output resultados tela
	printf ("\n");
    printf ("\n\n===\tBubble Sort\t===\n");
	for(i = 0 ; i < sizeBubble ; i ++){
		printf("%i \t", bkpArrayBubble[i]);	
	};
    printf ("\nQuantidade dados: %i\n", sizeBubble);
    printf ("Comparacoes: %lu\nTrocas: %lu\n", qtdComparacao, qtdTroca);	
	printf ("Tempo: %.0lfs\n\n", diff);
	
	FILE *arq; //declara ponteiro do tipo FILE
	char saida[100]; //declara variavel para armazenar nome de arquivo txt de saida
	int result; //variavel de controle para função fprintf
	
	//input usuario
	printf ("Digite o nome do arquivo de saida:\n");
	scanf ("%s", saida);
	
	//gera arquivo com nome digitado e agrega extensao txt
	arq = fopen (strcat (saida,".txt"), "w");
	//escreve no arquivo
	result = fprintf(arq, "===\tBubble Sort\t===\nQuantidade: %i\nComparacoes: %lu\nTrocas: %lu\nTempo: %.0lfs\n=========================\n", sizeBubble, qtdComparacao, qtdTroca, diff);
	result = fprintf (arq, "===\tOrdenados\t===\n");
	for(i = 0 ; i < sizeBubble ; i ++) {
		result = fprintf(arq, "%i \t", bkpArrayBubble[i]);
	};
	
	fclose (arq); //fecha arquivo
	free(bkpArrayBubble);
};
//Selection Sort
//
int SelectionSort(int sizeSelection, int *arraySelection){
	int i, j, tempSelection; //Declara variaveis auxiliares
	unsigned long int qtdComparacao = 0, qtdTroca = 0; //Declara variaveis para extração dos dados de troca e comparações
	
	int *bkpArraySelection = (int *) malloc (sizeSelection * sizeof(int)); //declara e aloca ponteiro de tamanho x
	for (i = 0 ; i < sizeSelection ; i ++) { //transcreve o array bagunçado para um bkp
		bkpArraySelection[i] = arraySelection[i];
	};

	tInicio = time(NULL); //tInicio recebe valor com hora do momento em que é chamado;
	
	//algoritmo de ordenação
    for (i = 0; i < sizeSelection - 1; i++) {    	
		for (j = i; j < sizeSelection; j++) {
			qtdComparacao++;
        	if (bkpArraySelection[i] > bkpArraySelection[j]) {
        	qtdTroca++;
            tempSelection = bkpArraySelection[i];
            bkpArraySelection[i] = bkpArraySelection[j];
            bkpArraySelection[j] = tempSelection;
        	};
    	};
	};
	
	tFim = time(NULL); //tFim recebe valor com hora do momento em que é chamado
	double diff = (tFim - tInicio); //declara variavel diff e realiza conta para diferenciar os tempos.
			
	//output resultados tela
	printf ("\n");
    printf ("\n\n===\tSelection Sort\t===\n");
	for(i = 0 ; i < sizeSelection ; i ++){
		printf("%i \t", bkpArraySelection[i]);	
	};
    printf ("\nQuantidade dados: %i\n", sizeSelection);
    printf ("Comparacoes: %lu \nTrocas: %lu \n", qtdComparacao, qtdTroca);	
	printf ("Tempo: %.0lfs\n\n", diff);
	
	FILE *arq; //declara ponteiro do tipo FILE
	char saida[100]; //declara variavel para armazenar nome de arquivo txt de saida
	int result; //variavel de controle para função fprintf
	
	//input usuario
	printf ("Digite o nome do arquivo de saida:\n");
	scanf ("%s", saida);
	
	//gera arquivo com nome digitado e agrega extensao txt
	arq = fopen (strcat (saida,".txt"), "w");
	//escreve no arquivo
	result = fprintf(arq, "===\tSelection Sort\t===\nQuantidade: %i\nComparacoes: %lu\nTrocas: %lu\nTempo: %.0lfs\n=========================\n", sizeSelection, qtdComparacao, qtdTroca, diff);
	result = fprintf (arq, "===\tOrdenados\t===\n");
	for(i = 0 ; i < sizeSelection ; i ++) {
		result = fprintf(arq, "%i \t", bkpArraySelection[i]);
	};
	
	fclose (arq); //fecha arquivo
	free(bkpArraySelection);
};
//Insertion Sort
//
int InsertionSort(int sizeInsertion, int *arrayInsertion){
	int i, j, tempInsertion; //Declara variaveis auxiliares
	unsigned long int qtdComparacao = 0, qtdTroca = 0; //Declara variaveis para extração dos dados de troca e comparações
	
	int *bkpArrayInsertion = (int *) malloc (sizeInsertion * sizeof(int)); //declara e aloca ponteiro de tamanho x
	for (i = 0 ; i < sizeInsertion ; i ++) { //transcreve o array bagunçado para um bkp
		bkpArrayInsertion[i] = arrayInsertion[i];
	}

	tInicio = time(NULL); //tInicio recebe valor com hora do momento em que é chamado;
	
	for(i = 1; i < sizeInsertion; i++){		
		tempInsertion = bkpArrayInsertion[i];
		j = i - 1;		
		qtdComparacao++;			

		while((bkpArrayInsertion[j] > tempInsertion) && (j >= 0)) {
			bkpArrayInsertion[j + 1] = bkpArrayInsertion[j];
			qtdTroca++;
			j--;
		};

		bkpArrayInsertion[j + 1] = tempInsertion;
	};
	
	tFim = time(NULL); //tFim recebe valor com hora do momento em que é chamado
	double diff = (tFim - tInicio); //declara variavel diff e realiza conta para diferenciar os tempos.
			
	//output resultados tela
	printf ("\n");
    printf ("\n\n===\tInsertion Sort\t===\n");
	for(i = 0 ; i < sizeInsertion ; i ++){
		printf("%i \t", bkpArrayInsertion[i]);	
	};
    printf ("\nQuantidade dados: %i\n", sizeInsertion);
    printf ("Comparacoes: %lu\nTrocas: %lu\n", qtdComparacao, qtdTroca);	
	printf ("Tempo: %.0lfs\n\n", diff);
	
	FILE *arq; //declara ponteiro do tipo FILE
	char saida[100]; //declara variavel para armazenar nome de arquivo txt de saida
	int result; //variavel de controle para função fprintf
	
	//input usuario
	printf ("Digite o nome do arquivo de saida:\n");
	scanf ("%s", saida);
	
	//gera arquivo com nome digitado e agrega extensao txt
	arq = fopen (strcat (saida,".txt"), "w");
	//escreve no arquivo
	result = fprintf(arq, "===\tInsertion Sort\t===\nQuantidade: %i\nComparacoes: %lu\nTrocas: %lu\nTempo: %.0lfs\n=========================\n", sizeInsertion, qtdComparacao, qtdTroca, diff);
	result = fprintf (arq, "===\tOrdenados\t===\n");
	for(i = 0 ; i < sizeInsertion ; i ++) {
		result = fprintf(arq, "%i \t", bkpArrayInsertion[i]);
	};
	
	fclose (arq); //fecha arquivo
	
};
//Heap Sort
//
void HeapSort(int sizeHeap, int *arrayHeap) {  
  	int i, j, n, tempHeap; //Declara variaveis auxiliares
	unsigned long int qtdComparacao = 0, qtdTroca = 0; //Declara variaveis para extração dos dados de troca e comparações
	
	int *bkpArrayHeap = (int *) malloc (sizeHeap * sizeof(int)); //declara e aloca ponteiro de tamanho x
	for (i = 0 ; i < sizeHeap ; i ++) { //transcreve o array bagunçado para um bkp
		bkpArrayHeap[i] = arrayHeap[i];
	};
   
   tInicio = time(NULL);
   
   buildMaxHeap(bkpArrayHeap, sizeHeap);
  
   i, n = sizeHeap;
    
   for(i = (sizeHeap - 1); i > 0; i--) {
   		qtdComparacao++;
		tempHeap = bkpArrayHeap[i];
		qtdTroca++;
		bkpArrayHeap[i] = bkpArrayHeap[0];
		qtdTroca++;
		bkpArrayHeap[0] = tempHeap;
		qtdTroca++;
      	maxHeapify(bkpArrayHeap, 0, --n);
   };
   
   tFim = time(NULL);
   float diff = difftime(tFim, tInicio);
	
    //output resultados tela
	printf ("\n");
    printf ("\n\n===\tHeap Sort\t===\n");
	for(i = 0 ; i < sizeHeap ; i ++){
		printf("%i \t", bkpArrayHeap[i]);	
	};
    printf ("\nQuantidade dados: %i\n", sizeHeap);
    printf ("Comparacoes: %lu\nTrocas: %lu\n", qtdComparacao, qtdTroca);	
	printf ("Tempo: %.0lfs\n\n", diff);
	
	FILE *arq; //declara ponteiro do tipo FILE
	char saida[100]; //declara variavel para armazenar nome de arquivo txt de saida
	int result; //variavel de controle para função fprintf
	
	//input usuario
	printf ("Digite o nome do arquivo de saida:\n");
	scanf ("%s", saida);
	
	//gera arquivo com nome digitado e agrega extensao txt
	arq = fopen (strcat (saida,".txt"), "w");
	//escreve no arquivo
	result = fprintf(arq, "===\tHeap Sort\t===\nQuantidade: %i\nComparacoes: %lu\nTrocas: %lu\nTempo: %.0lfs\n=========================\n", sizeHeap, qtdComparacao, qtdTroca, diff);
	result = fprintf (arq, "===\tOrdenados\t===\n");
	for(i = 0 ; i < sizeHeap ; i ++) {
		result = fprintf(arq, "%i \t", bkpArrayHeap[i]);
	};
	
	fclose (arq); //fecha arquivo
};

void buildMaxHeap(int* array, int size) { 
   int i;
   for (i = size / 2 - 1; i >= 0; i--)
      maxHeapify(array, i , size);
};

void maxHeapify(int* array, int pos, int n) { 
	int max = 2 * pos + 1, right = max + 1;

	if (max < n) {
		//qtdComparacao++;
		if ( right < n && array[max] < array[right]){
		max = right;
		}
		
		if (array[max] > array[pos]) { 
		//qtdComparacao++;
		int aux = array[max];
		//qtdTroca++;
		array[max] = array[pos];
		//qtdTroca++;
		array[pos] = aux;
		//qtdTroca++;
		maxHeapify(array, max, n);
		}
	}
};
//Função que recebe quick sort
//
void QuickSort(int *arrayQuick, int left, int right, int size) {
	int i;
	float diffQuick;
	tInicio = time(NULL);
	QuickSortInterno(arrayQuick, left, right);
	tFim = time(NULL);
	
	diffQuick = (tFim - tInicio);
	
	//output resultados tela
	printf ("\n");
    printf ("\n\n===\tQuick Sort\t===\n");
	for(i = 1 ; i <= size ; i ++){
		printf("%i \t", arrayQuick[i]);	
	};
    printf ("\nQuantidade dados: %i\n", size);
    printf ("Comparacoes: %lu\nTrocas: %lu\n", qtdComparacaoQuick, qtdTrocaQuick);	
	printf ("Tempo: %.0lfs\n\n", diffQuick);
	
	FILE *arq; //declara ponteiro do tipo FILE
	char saida[100]; //declara variavel para armazenar nome de arquivo txt de saida
	int result; //variavel de controle para função fprintf
	
	//input usuario
	printf ("Digite o nome do arquivo de saida:\n");
	scanf ("%s", saida);
	
	//gera arquivo com nome digitado e agrega extensao txt
	arq = fopen (strcat (saida,".txt"), "w");
	//escreve no arquivo
	result = fprintf(arq, "===\tQuick Sort\t===\nQuantidade: %i\nComparacoes: %lu\nTrocas: %lu\nTempo: %.0lfs\n=========================\n", size, qtdComparacaoQuick, qtdTrocaQuick, diffQuick);
	result = fprintf (arq, "===\tOrdenados\t===\n");
	for(i = 1 ; i <= size ; i ++) {
		result = fprintf(arq, "%i \t", arrayQuick[i]);
	};
	
	fclose (arq); //fecha arquivo
};
//Quick Sort
//
void QuickSortInterno(int *arrayQuickInterno, int left, int right) {
	if(left >= right) {
	return;
	}
	
	int i = left, j = right, tempQuick, pivot = arrayQuickInterno[i]; //Declara variaveis auxiliares
  
  	i = left, j = right;
  	tempQuick, pivot = arrayQuickInterno[i];
  
  	qtdComparacaoQuick++;
  	while(i <= j) {
  		qtdComparacaoQuick++;
	    while(arrayQuickInterno[i] < pivot && i < right) {
	    	 i++;
		};
		qtdComparacaoQuick++;
	    while(arrayQuickInterno[j] > pivot && j > left) {
	    	 j--;
		};
	    if(i <= j) {
	    tempQuick = arrayQuickInterno[i];
		arrayQuickInterno[i] = arrayQuickInterno[j];
		arrayQuickInterno[j] = tempQuick;
	    i++;
		j--;
		qtdTrocaQuick++;
		}
  }
	
	if (j > left) {
		QuickSortInterno(arrayQuickInterno, left, j + 1);
	}
	if (i < right) {
		QuickSortInterno(arrayQuickInterno, i, right);
	}
};
