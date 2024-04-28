#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 13
#define TAM 1001
#define VAZIO ' '


typedef struct frequencia Freq;
typedef struct binario Bin;

struct frequencia
{
	char caracter;
	int freq;
};

struct binario
{
	char caracter;
	int bin;
};

Freq hashFreq[MAX];

void freq_char(char* linha);
int busca(char  c);
int insere_freq(char c);

int main() {

	FILE* fArq;
	char linha[TAM];
	

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
		freq_char(linha);
	}

	for (int i = 0; i < MAX; i++)
	{
		printf("char: %c - freq: %d\n", hashFreq[i].caracter, hashFreq[i].freq);
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

int insere_freq(char c) {
	
	int pos = (int)c%MAX ;
	
	for (int k = 0; k < MAX; k++)
	{
		pos = (pos + k) % MAX;

		printf("%d\n", pos);

		if (hashFreq[k].caracter == c) { //se eu tiver uma colisão é pq o char é o mesmo
			hashFreq[k].freq++;
			return pos;
		}
					
		if (hashFreq[k].caracter == VAZIO) { //ainda não tenho o char na tabela
			hashFreq[k].caracter = c;
			hashFreq[k].freq++;
			return pos;
		}
			
	}

	return -1;
}

void freq_char(char* linha) {
	

	for (int i = 0; i < strlen(linha); i++)
	{
		insere_freq(linha[i]);
	}
	
}