//IMPLEMENTACIONES DE LA PILA ESTÁTICA

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
	p->tope = -1;
	return;
}

/*
Descripción: Elimina la pila (borra sus elementos de la memoria)
Recibe: pila *p (apuntador a pila)
Devuelve: 
Observaciones: en realidad solo establecemos el tope de la pila de nuevo a -1
*/
void Destroy(pila *p){
	Initialize(p);
	return;
}

/*
Descripción: Obtiene el número de elementos actualmente en la pila
Recibe: pila *p (apuntador a pila)
Devuelve: int (tamaño de la pila, siempre ≥ 0)
Observaciones: es necesaria una referencia válida a la pila y que esté inicializada
*/
int Size(pila *p){
	return p->tope + 1;
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
Devuelve: boolean (TRUE si la inserción fue correcta, FALSE en caso de desbordamiento)
Observaciones: es necesaria una referencia válida a la pila y que esté inicializada
*/
boolean Push(elemento e, pila *p){
	boolean r;
	if(Size(p) == MAX_ELEMENTS){
		r = FALSE;
	}else{
		p->tope++;
		p->A[p->tope] = e;
		r = TRUE;
	}
	return r;
}

/*
Descripción: Desempila o saca el elemento del tope de la pila, eliminándolo
Recibe: pila *p (apuntador a pila)
Devuelve: elemento (elemento que se desempiló)
Observaciones: es necesaria una referencia válida a la pila y que esté inicializada, además, si la pila estab vacía, devuelve un elemento e no especificado
*/
elemento Pop(pila *p){
	elemento e;
	if(!IsEmpty(p)){
		e = p->A[p->tope];
		p->tope--;
	}
	return e;
}

/*
Descripción: Consultar el elemento del tope de la pila, sin eliminarlo
Recibe: pila *p (apuntador a pila)
Devuelve: elemento (elemento que se desempiló)
Observaciones: es necesaria una referencia válida a la pila y que esté inicializada, además, si la pila estab vacía, devuelve un elemento e no especificado
*/
elemento Top(pila *p){
	elemento e;
	if(!IsEmpty(p)){
		e = p->A[p->tope];
	}
	return e;
}
