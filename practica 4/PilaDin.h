#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef char boolean;

typedef struct{
	int entero;
	char caracter;
	float flotante;
	double doble;
	int x;
	int y;
} elemento;

typedef struct nodo{
	elemento e;
	struct nodo * abajo;
} nodo;

typedef struct{
	nodo * tope;
	int tamano;
} pila;

void Initialize(pila *p);
void Destroy(pila *p);
int Size(pila *p);
boolean IsEmpty(pila *p);
boolean Push(elemento e, pila *p);
elemento Pop(pila *p);
elemento Top(pila *p);
