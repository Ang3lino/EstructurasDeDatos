#ifndef ArbolBin_H
#define ArbolBin_H

#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef unsigned char boolean;
typedef unsigned char Char;

typedef struct nodo{
	struct nodo * izq;
	struct nodo * der;
	Char c;
} nodo;

typedef struct{
	nodo * raiz;
} arbol_bin;

typedef nodo* posicion;

arbol_bin * NewArbolBin();
posicion NewNode(Char c);
boolean IsLeaf(posicion p);
arbol_bin * MergeTrees(arbol_bin *A, arbol_bin *B);

#endif