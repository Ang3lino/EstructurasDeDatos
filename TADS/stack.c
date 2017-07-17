//IMPLEMENTACIONES DE LA PILA DINÁMICA

#include "stack.h"

/*  Funcion: newStack
 *  Caracteristicas: Declara una nueva stack mediante la instruccion 
 *  	Stack *name = newStack ();
 *  Parametros: No hay.
 *  Regresa: Un apuntador a la estructura Stack. */
Stack *newStack (void) {
	Stack *s = (Stack *) calloc (sizeof (Stack), 1);
	s->tope = NULL;
	s->tamano = 0;
	return s;
}

/*	Descripción: Elimina la Stack (borra sus elementos de la memoria de forma iterativa)
	Recibe: Stack *p (apuntador a Stack)
	Devuelve: 
	Observaciones: la Stack debe de estar referenciada correctamente por el usuario */
void destroy (Stack *p) {
	nodo *tmp;
	while (p->tope != NULL) {
		tmp = p->tope->abajo;
		free(p->tope);
		p->tope = tmp;
	}
	p->tamano = 0;
}

/*	Descripción: Obtiene el número de elementos actualmente en la Stack
	Recibe: Stack *p (apuntador a Stack)
	Devuelve: int (tamaño de la Stack, siempre ≥ 0)
	Observaciones: es necesaria una referencia válida a la Stack y que esté inicializada */
static int stackSize(Stack *p){
	return p->tamano;
}

/*	Descripción: Consultar si la Stack está vacía
	Recibe: Stack *p (apuntador a Stack) Devuelve: boolean (true si está vacía, false en caso contrario)
	Observaciones: es necesaria una referencia válida a la Stack y que esté inicializada */
bool stackEmpty(Stack *p){
	return stackSize(p) == 0;
}

/*  Descripción: Empila o introduce un element a la Stack
	Recibe: element e (element a empilar), Stack *p (apuntador a Stack)
	Devuelve: boolean (true si la inserción fue correcta, false en caso de que la función 
			  malloc() no haya podido apartar memoria)
	Observaciones: es necesaria una referencia válida a la Stack y que esté inicializada */
bool push (Stack *p, element e) {
	bool r;
	nodo *nuevo = (nodo*) malloc (sizeof (nodo));
	if (!nuevo)
		r = false;
	else {
		r = true;
		nuevo->e = e;
		nuevo->abajo = p->tope;
		p->tope = nuevo;
		p->tamano++;
	}
	return r;
}

/*  Descripción: Desempila o saca el element del tope de la Stack, eliminándolo
	Recibe: Stack *p (apuntador a Stack)
	Devuelve: element (element que se desempiló)
	Observaciones: es necesaria una referencia válida a la Stack y que esté inicializada.
			       Además, si la Stack estaba vacía, devuelve un element e no especificado; 
				   y se asume que la función free() siempre puede liberar memoria.  */
element pop (Stack *p) {
	element e;
	nodo * tmp;
	if (!stackEmpty (p)) {
		e = p->tope->e;
		tmp = p->tope->abajo;
		free(p->tope);
		p->tope = tmp;
		p->tamano--;
	}
	return e;
}

/*  Descripción: Consultar el element del tope de la Stack, sin eliminarlo
	Recibe: Stack *p (apuntador a Stack)
	Devuelve: element (element que se desempiló)
	Observaciones: es necesaria una referencia válida a la Stack y que esté inicializada.
	Además, si la Stack estaba vacía, devuelve un element e no especificado  */
element top(Stack *p){
	element e;
	if (!stackEmpty (p)){
		e = p->tope->e;
	}
	return e;
}

