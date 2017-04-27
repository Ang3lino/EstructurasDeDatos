/*	Implementacion de las listas dinamicas doblemente enlazadas,
	inspirado en Makigas, por Angel Lopez Manriquez.
	*/

#ifndef _LISDOB_H_
#define _LISDOB_H_

#define TAMNOM 100
#define TAMDEF 1000

typedef struct nodo{
	char nombre[TAMNOM];
	char definicion[TAMDEF];
	struct nodo *siguiente;
	struct nodo *anterior;
} Nodo;

typedef struct lista{
	Nodo *cabeza;
	int longitud;
} Lista;

Nodo *crearNodo (char nombre[], char definicion[]);
Lista *crearLista (void);
void eliminarPrincipio (Lista *l);
void formatearLista (Lista *l);
void insertarPrincipio (Lista *, char nombre[], char definicion[]);
void insertarUltimo (Lista *l, char nombre[], char definicion[]);
void liberarNodo (Nodo *n);
int hash (char *);

#endif
