//IMPLEMETNACIÓN DE LAS FUNCIONES MÍNIMAS DEL ÁRBOL BINARIO
#include "ArbolBin.h"

/*Devuelve un apuntador a un nuevo nodo listo para usar, inicializándolo
con el Char c*/
nodo * NewNode(Char c){
	nodo * nuevo = calloc(1, sizeof(nodo));
	nuevo->c = c;
	return nuevo;
}

/*Dada una posición, devuelve TRUE si es una hoja, es decir, si tanto su
hijo izquierdo como derecho son nulos; en caso contrario devuelve FALSE*/
boolean IsLeaf(nodo * p){
	return p->izq == NULL && p->der == NULL;
}