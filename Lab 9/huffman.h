#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string.h>

typedef struct {
    unsigned char value;
    int left, right;
} HuffmanNode;

#define Item int

// Including below so `Item` is defined.
#include "heap.h"

void computeFreqs(char *text, int size, int freqs[256]) {
	int i, j, V;
	for(i = 0; i < 256; i++){
		freqs[i] = 0;
	}
	for(i = 0; i < size; i++){
		if(freqs[(int)text[i]] == 0){
			V = 0;
			for(j = 0; j < size; j++){
				if(text[j] == text[i]){
					V++;
				}
			}
			freqs[(int)text[i]] = V;
		}
	}
	
}

HuffmanNode *makeTree(int freqs[256], int *size) {
	int i;
	HuffmanNode *hftree = (HuffmanNode *) malloc(256 * sizeof(HuffmanNode));
	APriQueue heap = makeQueue(1);
	ItemType n1, n2, parent;
	for(i = 0, *size = 0; i < 256; i++){
		if(freqs[i] != 0){
			hftree[*size].value = (char) i;
			hftree[*size].left = -1;
			hftree[*size].right = -1;
			ItemType item;
			item.content = *size;
			item.prior = freqs[i];
			insert(heap, item);
			*size += 1;
		}
	}
	if (*size == 1){
		*size = 2;
		hftree[1].left = 0;
		hftree[1].right = -1;
		hftree[1].value = (char) 0;
	}
	while(heap->size >= 2){
		n1 = removeMin(heap);
		n2 = removeMin(heap);
		hftree[*size].value = (char) 0;
		hftree[*size].left = n1.content;
		hftree[*size].right = n2.content;
		parent.content = *size;
		parent.prior = n1.prior + n2.prior;
		*size += 1;
		insert(heap, parent);
	}
	return hftree;
}

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code) {
	if(nodes[index].left == -1 && nodes[index].right == -1){
		strcpy(codes[nodes[index].value], code);
		code[0] = '\0';
		return;
	}
	char copy[255];
	copy[0] = '\0';
	strcpy(copy, code);
	strcat(code, "0");
	makeCodes(nodes[index].left, nodes, codes, code);
	strcpy(code, copy);
	strcat(code, "1");
	makeCodes(nodes[index].right, nodes, codes, code);
	
}

char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {
	if(text[0] == '\0'){
		return "-1";
	}
	char **codes = (char **) malloc(255 * sizeof(char *));
	char *compressed = (char *) malloc(255 * textSize * sizeof(char));
	compressed[0] = '\0';
	int i;
	for(i = 0; i < 255; i++){
		codes[i] = (char *) malloc(255 * sizeof(char));
	}
	char code[255];
	code[0] = '\0';
	makeCodes(numNodes - 1, nodes, codes, code);
	for(i = 0; i < textSize; i++){
		strcat(compressed, codes[(int)text[i]]);
	}
	return compressed;
}

char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes) { 
	char *decompress = (char *) malloc(255 * textSize * sizeof(char));
	int i, index = numNodes - 1, j;
	decompress[0] = '\0';
	if(strcmp(text, "-1") == 0){
		return decompress;
	}
	j = 0;
	for(i = 0; i < textSize; i++){
		if(text[i] == '0'){
			index = nodes[index].left;
		}
		else{
			index = nodes[index].right;
		}
		if(nodes[index].left == -1 && nodes[index].right == -1){
			decompress[j++] = nodes[index].value;
			index = numNodes - 1;
		}
	}
	return decompress;
}

#endif

