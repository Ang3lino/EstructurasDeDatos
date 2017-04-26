/*	Implementacion de las listas dinamicas doblemente enlazadas,
	inspirado en Makigas, por Angel Lopez Manriquez.
	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lisdob.h"


Nodo *
crearNodo (char nombre[], char definicion[]){
	Nodo *nuevo = (Nodo *) malloc (sizeof (Nodo));
	if (!nuevo){
		perror ("No hay espacion suficiente \n");
		exit (1);
	}
	strncpy (nuevo->nombre, nombre, 50);
	strncpy (nuevo->definicion, definicion, 250);
	nuevo->siguiente = nuevo->anterior = NULL;

	return nuevo;
}

Lista *
crearLista (void){
	Lista *l = (Lista *) malloc (sizeof (Lista));

	l->cabeza = NULL;
	l->longitud = 0;

	return l;
}

void
insertarPrincipio (Lista *l, char nombre[], char definicion[]){
	Nodo *n = crearNodo (nombre, definicion);

	if (!l->cabeza)
		l->cabeza = n;
	else{
		n->siguiente = l->cabeza;

		l->cabeza = n;
		(l->cabeza->siguiente)->anterior = l->cabeza;
	}

	l->longitud++;
}

void
insertarUltimo (Lista *l, char *nombre, char *definicion){
	Nodo *n = crearNodo (nombre, definicion);

	if (!l->cabeza)
		l->cabeza = n;
	else{
		Nodo *ptr = l->cabeza;

		while (ptr->siguiente)
			ptr = ptr->siguiente;
		ptr->siguiente = n;
		(ptr->siguiente)->anterior = ptr;
	}

	l->longitud++;
}

void
liberarNodo (Nodo *n){

	n->siguiente = n->anterior = NULL;

	free (n);
}

void
eliminarPrincipio (Lista *l){
	if (l->cabeza){
		Nodo *borrar = l->cabeza;
		l->cabeza = (l->cabeza)->siguiente;
		liberarNodo (borrar);

		l->longitud--;
	}
}

void
formatearLista (Lista *l){

	if (l->cabeza){
		while (l->cabeza)
			eliminarPrincipio (l);

	}
	free (l);
}
