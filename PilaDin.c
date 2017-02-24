//IMPLEMENTACIONES DE LA PILA DINÁMICA

//Librerías
#include "PilaEst.h"

//DEFINICIÓN DE FUNCIONES

/*
Descripción: inicializa la pila para su uso normal
Recibe: pila *p (apuntador a pila)
Devuelve: 
Observaciones: la pila debe de estar referenciada correctamente por el usuario
*/
void Initialize(pila *p){
	p->tope = NULL;
	p->tamano = 0;
	return;
}

/*
Descripción: Elimina la pila (borra sus elementos de la memoria de forma iterativa)
Recibe: pila *p (apuntador a pila)
Devuelve: 
Observaciones: la pila debe de estar referenciada correctamente por el usuario
*/
void Destroy(pila *p){
	nodo * tmp;
	while(p->tope != NULL){
		tmp = p->tope->abajo;
		free(p->tope);
		p->tope = tmp;
	}
	p->tamano = 0;
	return;
}

/*
Descripción: Obtiene el número de elementos actualmente en la pila
Recibe: pila *p (apuntador a pila)
Devuelve: int (tamaño de la pila, siempre ≥ 0)
Observaciones: es necesaria una referencia válida a la pila y que esté inicializada
*/
int Size(pila *p){
	return p->tamano;
}

/*
Descripción: Consultar si la pila está vacía
Recibe: pila *p (apuntador a pila)
Devuelve: boolean (TRUE si está vacía, FALSE en caso contrario)
Observaciones: es necesaria una referencia válida a la pila y que esté inicializada
*/
boolean IsEmpty(pila *p){
	return Size(p) == 0;
}

/*
Descripción: Empila o introduce un elemento a la pila
Recibe: elemento e (elemento a empilar), pila *p (apuntador a pila)
Devuelve: boolean (TRUE si la inserción fue correcta, FALSE en caso de que la función malloc() no haya podido apartar memoria)
Observaciones: es necesaria una referencia válida a la pila y que esté inicializada
*/
boolean Push(elemento e, pila *p){
	boolean r;
	nodo * nuevo = (nodo*)malloc(sizeof(nodo));
	if(nuevo == NULL){
		r = FALSE;
	}else{
		nuevo->e = e;
		nuevo->abajo = p->tope;
		p->tope = nuevo;
		p->tamano++;
		r = TRUE;
	}
	return r;
}

/*
Descripción: Desempila o saca el elemento del tope de la pila, eliminándolo
Recibe: pila *p (apuntador a pila)
Devuelve: elemento (elemento que se desempiló)
Observaciones: es necesaria una referencia válida a la pila y que esté inicializada.
Además, si la pila estaba vacía, devuelve un elemento e no especificado; y se asume que la función free() siempre puede liberar memoria.
*/
elemento Pop(pila *p){
	elemento e;
	nodo * tmp;
	if(!IsEmpty(p)){
		e = p->tope->e;
		tmp = p->tope->abajo;
		free(p->tope);
		p->tope = tmp;
		p->tamano--;
	}
	return e;
}

/*
Descripción: Consultar el elemento del tope de la pila, sin eliminarlo
Recibe: pila *p (apuntador a pila)
Devuelve: elemento (elemento que se desempiló)
Observaciones: es necesaria una referencia válida a la pila y que esté inicializada.
Además, si la pila estaba vacía, devuelve un elemento e no especificado
*/
elemento Top(pila *p){
	elemento e;
	if(!IsEmpty(p)){
		e = p->tope->e;
	}
	return e;
}
