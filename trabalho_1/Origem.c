#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 6
#define TAM 1001
#define VAZIO ' '


typedef struct frequencia Freq;
typedef struct binario Bin;

struct frequencia
{
	char caracter;
	int freq;
};

struct heap { //estrutura para o vetor da minha sequência

	char caracter;
	int freq;
};

struct binario
{
	char caracter;
	int bin;
};

struct node
{
	int chave;
	struct node* esq;
	struct node* dir;
};

typedef struct node Node;
typedef struct heap Heap;

Freq hashFreq[MAX];

void freq_char(char* linha, int* qtdElm);
int busca(char  c);
int insere_freq(char c, int* qtdElem);
void subir(Heap* v, int i);
void descer(Heap* v, int i, int tam);
Heap* createMinHeap(int qtdElm);
void create_nodes(Node* root, int qtdElm);

int main() {

	FILE* fArq;
	char linha[TAM];
	int qtdElem = 0;
	Heap* vet = NULL;


	for (int i = 0; i < MAX; i++)
	{
		hashFreq[i].caracter = VAZIO;
		hashFreq[i].freq = 0;
	}


	if (!(fArq = fopen("texto.txt", "r")))
		exit(1);

	while (!feof(fArq))
	{
		fscanf(fArq, "%[^\n]\n", linha);
		freq_char(linha, &qtdElem);
	}

	printf("tabela hash...\n");
	for (int i = 0; i < MAX; i++)
	{
		printf("char: %c - freq: %d\n", hashFreq[i].caracter, hashFreq[i].freq);
	}

	vet = createMinHeap(qtdElem);
	
	printf("min heap...\n");
	for (int i = 0; i < qtdElem; i++) {
		
		printf("char: %c - freq: %d\n", vet[i].caracter, vet[i].freq);
	}

}

int busca(char c) {
	int pos = -1;

	for (int i = 0; i < MAX; i++)
	{
		printf("%c\n", c);
		if (hashFreq[i].caracter == c) {
			pos = i;
			return pos;
		}
	}

	return pos;
}

int insere_freq(char c, int* qtdElm) {

	int pos = (int)c % MAX;

	for (int k = 0; k < MAX; k++)
	{
		pos = (pos + k) % MAX;

		if (hashFreq[k].caracter == c) { //se eu tiver uma colisão é pq o char é o mesmo
			hashFreq[k].freq++;
			return pos;
		}

		if (hashFreq[k].caracter == VAZIO) { //ainda não tenho o char na tabela
			hashFreq[k].caracter = c;
			hashFreq[k].freq++;
			*qtdElm = *qtdElm + 1;
			return pos;
		}

	}

	return -1;
}

void freq_char(char* linha, int* qtdElm) {


	for (int i = 0; i < strlen(linha); i++)
	{
		insere_freq(linha[i], qtdElm);
	}

}

void subir(Heap* v, int i) {
	int j;
	Heap* aux = (Heap*)malloc(sizeof(Heap));

	j = (i - 1) / 2;
	if (j >= 0) 
		if(v[i].freq > v[j].freq){
			aux->freq = v[i].freq;
			aux->caracter = v[i].caracter;
			v[i].freq = v[j].freq;
			v[i].caracter = v[j].caracter;
			v[j] = *aux;
			subir(v, j);
		}
}

void descer(Heap* v, int i, int tam) {
	int j, aux;
	j = (2 * i) + 1;
	if (j <= tam) {
		if (j < tam)
			if (v[j + 1].freq > v[j].freq)
				j++;
		if (v[i].freq < v[j].freq) {
			aux = v[i];
			vet[i] = vet[j];
			vet[j] = aux;
			descer(vet, j, tam);
		}
	}
}


Heap* createMinHeap(int qtdElm) {
	Heap* aux = (Heap*)malloc(sizeof(Heap) * qtdElm);
	
	for (int i = 0; i < qtdElm; i++) //inicializando o vetor
	{
		aux[i].caracter = hashFreq[i].caracter;
		aux[i].freq = hashFreq[i].freq;

	}
	
	for (int i = 1; i < qtdElm; i++) //criando o minHeap
	{
		descer(aux, i, qtdElm);
	}

	return aux;
}


void create_nodes(Node* root, int qtdElm) {

	for(int i = 0; i < qtdElm; i++) {

		int freqA = hashFreq[i].freq;
		int freqB = hashFreq[i + 1].freq;

		int sum = freqA + freqB;


	}
}