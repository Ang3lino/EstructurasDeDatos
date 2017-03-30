#include "PilaDin.h"

void Initialize(pila *p){
	p->tope = NULL;
	p->tamano = 0;
	return;
}

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

int Size(pila *p){
	return p->tamano;
}

boolean IsEmpty(pila *p){
	return Size(p) == 0;
}

boolean Push(elemento e, pila *p){
	boolean r = FALSE;
	nodo * nuevo = (nodo*)malloc(sizeof(nodo));
	if(nuevo != NULL){
		nuevo->e = e;
		nuevo->abajo = p->tope;
		p->tope = nuevo;
		p->tamano++;
		r = TRUE;
	}
	return r;
}

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

elemento Top(pila *p){
	elemento e;
	if(!IsEmpty(p)){
		e = p->tope->e;
	}
	return e;
}
