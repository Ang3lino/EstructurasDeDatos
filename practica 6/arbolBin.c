
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
insertRight (arbol **subraiz, elemento e) {
    nodo *nuevo = createNode (e);
    nuevo->e.direccion = 1;
    (*subraiz)->der = nuevo;
}

void 
insertLeft (arbol **subraiz, elemento e) {
    nodo *nuevo = createNode (e);
    nuevo->e.direccion = 0;
    (*subraiz)->izq = nuevo;
}

/*  This function doesn't work ...  */
void 
preorder (arbol *tree) {
    if (!tree)
        printf (" - ");
    printf ("( %d ", tree->e.caracter);
    preorder (tree->izq);
    preorder (tree->der);
    printf (" )");
}

