#include "ColaDin.h"
#include <stdlib.h>

/*	Frente -> ... -> final -> NULL 	*/

void
Initialize (cola *c)
{
	c->frente = NULL;
	c->final = NULL;
	c->num_elem = 0;

	return;
}

void
Queue (cola *c, elemento e)
{
	nodo *nuevo = (nodo *) malloc (sizeof (nodo));

	nuevo->e = e;
	nuevo->siguiente = NULL;

	if (!c->frente)
		c->frente = c->final = nuevo;
	else {
		c->final->siguiente = nuevo;
		c->final = nuevo;
	}

	c->num_elem++;
	return;
}

/*		Si la cola esta vacia, esto retorna basura.		*/
elemento
Dequeue (cola *c)
{
	elemento e;
	if (c->frente){
		e = c->frente->e;
		/*	Importante, se debe guardar la dir. de mem. del nodo a borrar.
			hacer free (c->frente->siguiente) puede causar bugs en otras funciones.
			*/
		nodo *aux = c->frente;
		c->frente = c->frente->siguiente;
		free (aux);

		if (c->frente == NULL)
			c->final = NULL;
		c->num_elem--;
	}

	return e;
}

void
Destroy (cola *c)
{
	elemento e;
	while (c->frente)
		e = Dequeue (c);
	free (c);
	return;
}

int Empty(cola *c){ return c->num_elem == 0; }

elemento Front(cola *c){ return c->frente->e; }

elemento Final(cola *c){ return c->final->e; }

int Size(cola *c){ return c->num_elem; }


elemento Element(int n, cola * c){
	int pos = 1;
	nodo * aux = c->frente;
	elemento e;

	if(n <= Size(c)){
		while(pos < n){
			aux = aux->siguiente;
			pos++;
		}
		e = aux->e;
	}

	return e;
}
