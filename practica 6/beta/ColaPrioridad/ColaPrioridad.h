#include "../ArbolBin/ArbolBin.h"
#include <stdlib.h>

typedef struct{
	arbol_bin * A;
	int prioridad;
} dato;

typedef struct{
	dato *nodos;
	int tamano;
	int capacidad;
} ColaPrioridad;

void InitializeQueue(ColaPrioridad *C);

void push(ColaPrioridad *C, int prioridad, arbol_bin *A);

dato pop(ColaPrioridad *C);