
#ifndef ARBOLBIN_H
#define ARBOLBIN_H

typedef struct elemento{
    char caracter;
    int  frecuencia, direccion;
} elemento;

typedef struct nodo{
    struct nodo *izq, *der;
    elemento e;
} nodo;

typedef nodo arbol;

arbol *createTree (void);
nodo *createNode (elemento);
void insertRight (arbol **, arbol *);
void insertLeft (arbol **, arbol *);
void insertElementRight (arbol **, elemento);
void insertElementLeft (arbol **, elemento);
void preorder (arbol *);


#endif

