#include "ColaEstCirc.h"
#include <stdlib.h>

void Initialize(cola *c){
	c->frente = 0;
	c->final = -1;
	c->tamano = 0;
	c->A = malloc(MAX_ELEMENTS * sizeof(elemento));
	return;
}

void Destroy(cola *c){
	c->frente = 0;
	c->final = -1;
	c->tamano = 0;
	free(c->A);
	return;
}

int Size(cola *c){
	return c->tamano;
}

boolean Empty(cola *c){
	return Size(c) == 0;
}

boolean Queue(cola *c, elemento e){
	boolean r = FALSE;
	if(Size(c) != MAX_ELEMENTS){
		c->final = (c->final + 1) % MAX_ELEMENTS;
		c->A[c->final] = e;
		c->tamano++;
		r = TRUE;
	}
	return r;
}

elemento Dequeue(cola *c){
	elemento e;
	if(!Empty(c)){
		e = c->A[c->frente];
		c->frente = (c->frente + 1) % MAX_ELEMENTS;
		c->tamano--;
	}
	return e;
}

elemento Front(cola *c){
	elemento e;
	if(!Empty(c))
		e = c->A[c->frente];
	return e;
}

elemento Final(cola *c){
	elemento e;
	if(!Empty(c))
		e = c->A[c->final];
	return e;
}

elemento Element(cola *c, int n){
	elemento e;
	if(n <= Size(c)){
		e = c->A[(c->frente + n - 1) % MAX_ELEMENTS];
	}
	return e;
}