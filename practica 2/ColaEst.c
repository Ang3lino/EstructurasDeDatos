#include "ColaEst.h"
#include <stdlib.h>

void Initialize(cola *c){
	c->frente = 0;
	c->final = -1;
	c->A = malloc(MAX_ELEMENTS * sizeof(elemento));
	return;
}

void Destroy(cola *c){
	c->frente = 0;
	free(c->A);
	return;
}

int Size(cola *c){
	return c->final+1;
}

boolean Empty(cola *c){
	return Size(c) == 0;
}

boolean Queue(cola *c, elemento e){
	boolean r = FALSE;
	if(Size(c) != MAX_ELEMENTS){
		c->final++;
		c->A[c->final] = e;
		r = TRUE;
	}
	return r;
}

elemento Dequeue(cola *c){
	elemento e;
	int i;
	if(!Empty(c)){
		e = c->A[c->frente];
		for(i = 0; i < c->final; i++)
			c->A[i] = c->A[i + 1];
		c->final--;
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
	if(n <= Size(c))
		e = c->A[n - 1];
	return e;
}