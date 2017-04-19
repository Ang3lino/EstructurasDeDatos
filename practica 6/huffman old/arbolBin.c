
#include <stdio.h>
#include <stdlib.h>
#include "arbolBin.h"

nodo *createNode (elemento e) {
    nodo *nuevoNodo = (nodo *) malloc (sizeof (nodo));
    nuevoNodo->izq = nuevoNodo->der = NULL;
    nuevoNodo->e = e;
    return nuevoNodo;
}

arbol *createTree (void) {
    arbol *nuevo = (arbol *) calloc (sizeof (arbol), 1);
    nuevo->der = nuevo->izq = NULL;
    return nuevo;
}

void 
insertLeft (arbol **subraiz, arbol *rama){
    (*subraiz)->izq = rama;
	(*subraiz)->e.direccion = 0;

}

void 
insertRight (arbol **subraiz, arbol *rama){
    (*subraiz)->der = rama;
	(*subraiz)->e.direccion = 1;

}

void 
insertElementRight (arbol **subraiz, elemento e) {
    nodo *nuevo = createNode (e);
    nuevo->e.direccion = 1;
    (*subraiz)->der = nuevo;
}

void 
insertElementLeft (arbol **subraiz, elemento e) {
    nodo *nuevo = createNode (e);
    nuevo->e.direccion = 0;
    (*subraiz)->izq = nuevo;
}

void 
preorder (arbol *tree) {
    if (!tree){
        printf (" - ");
        return;
    }
    
    printf ("( %c", tree->e.caracter);
    preorder (tree->izq);
    preorder (tree->der);
    printf (" )");
}

void 
inorder (arbol *tree){
	if (!tree)
		printf (" - ");
	else {
		printf ("( ");
		inorder (tree->izq);
		printf (" %c ", tree->e.caracter);
		inorder (tree->der);
		printf (" )");
	}

}


