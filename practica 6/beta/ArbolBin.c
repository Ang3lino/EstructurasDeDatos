#include "ArbolBin.h"

arbol_bin * NewArbolBin(){
	arbol_bin * A = calloc(1, sizeof(arbol_bin));
	return A;
}

posicion NewNode(Char c){
	posicion nuevo = calloc(1, sizeof(nodo));
	nuevo->c = c;
	return nuevo;
}

boolean IsLeaf(posicion p){
	return p->izq == NULL && p->der == NULL;
}

arbol_bin * MergeTrees(arbol_bin *A, arbol_bin *B){
	arbol_bin * C = NewArbolBin();
	C->raiz = NewNode(0);
	C->raiz->izq = A->raiz;
	C->raiz->der = B->raiz;
	return C;
}