/*	Implementacion de las listas dinamicas doblemente enlazadas,
	basado en los videos de Makigas, por Angel Lopez Manriquez.
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
	strncpy (nuevo->nombre, nombre, TAMNOM);
	strncpy (nuevo->definicion, definicion, TAMDEF);
	nuevo->siguiente = nuevo->anterior = NULL;

	return nuevo;
}

Lista *
crearLista (void){
	Lista *l = (Lista *) malloc (sizeof (Lista));

	l->frente = NULL;
	l->longitud = 0;

	return l;
}

void
insertarPrincipio (Lista *l, char nombre[], char definicion[]){
	Nodo *n = crearNodo (nombre, definicion);

	if (!l->frente)
		l->frente = n;
	else{
		n->siguiente = l->frente;

		l->frente = n;
		(l->frente->siguiente)->anterior = l->frente;
	}

	l->longitud++;
}

void
insertarUltimo (Lista *l, char *nombre, char *definicion){
	Nodo *n = crearNodo (nombre, definicion);

	if (!l->frente)
		l->frente = n;
	else{
		Nodo *ptr = l->frente;

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
	if (l->frente){
		Nodo *borrar = l->frente;
		l->frente = (l->frente)->siguiente;
		liberarNodo (borrar);

		l->longitud--;
	}
}

void
formatearLista (Lista *l){
	while (l->frente)	
		eliminarPrincipio (l);
	free (l);
}
