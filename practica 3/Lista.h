#ifndef Lista_h
#define Lista_h

#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define TAMNOM 100
#define TAMDEF 1000

typedef char boolean;

typedef struct{
	char nombre[TAMNOM];
	char definicion[TAMDEF];
} elemento;

typedef struct nodo{
	elemento e;
	struct nodo * anterior;
	struct nodo * siguiente;
} nodo;

typedef struct{
	nodo * frente;
	nodo * final;
	int tamano;
} lista;

typedef nodo* posicion;

//Operaciones de construccion
void Initialize(lista *l);
void Destroy(lista *l);

//Operaciones de posicionamiento y busqueda
posicion First(lista *l);
posicion Final(lista *l);
posicion Previous(lista *l, posicion p);
posicion Following(lista *l, posicion p);
posicion Search(lista *l, elemento e);

//Operaciones de consulta
elemento Position(lista *l, posicion p);
boolean ValidatePosition(lista *l, posicion p);
elemento Element(lista *l, int n);
posicion ElementPosition(lista *l, int n);
int Size(lista *l);
boolean IsEmpty(lista *l);

//Operaciones de modificacion
boolean AddBeginning(lista *l, elemento e);
boolean AddEnd(lista *l, elemento e);
boolean InsertBefore(lista *l, elemento e, posicion p);
boolean InsertAfter(lista *l, elemento e, posicion p);
boolean Remove(lista *l, posicion p);
boolean Replace(lista *l, posicion p, elemento e);

#endif

