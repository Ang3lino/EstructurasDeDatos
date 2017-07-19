
/*` Biblioteca del TAD queue dinamica 								     IPN-ESCOM
 *  =================================================================================
 *  
 *  Esta es una implementacion dinamica eficiente del TAD queue, en el lenguaje C. 
 *  
 *  Para su uso simplemente agrega la cabecera #include "queue.h" al codigo fuente
 *  y compilalo mediante el comando gcc fuente.c queue.c 
 *  
 *  para declarar una cola se usa la instruccion Queue *nombre = newQueue();
 *  
 *  Caracteristicas
 *  --------------------------------------------------------------------------------
 *  Al incluir la cabecera "queue.h", tambien se incluiran las bibliotecas stdbool.h
 *  (por lo que se incluye el tipo de dato bool y sus valores true y false), stdio.h 
 *  y stdlib.h. 
 *  
 *  Para agregar un tipo de dato se hace uso de una estructura element, en la cual 
 *  se definiran los datos deseados en sus campos. Es obligatorio el uso de esta 
 *  estructura para modificar y consultar el TAD.
 *  
 *  Notas
 *  -------------------------------------------------------------------------------
 *  Pueden fallar las funciones del tipo bool si no se tiene una version C99 o supe-
 *  rior, actualizate, el futuro es hoy v:.
 *  
 *  Autor: Makigas Octubre 2015, primera version.
 *  Modificada por: Lopez Manriquez Angel y Ontiveros Salazar Alan Enrique, Julio 2017.
 *  Version: 3	
 *  
 *  Cualquier optimizacion al codigo, por favor, hazla saber a github/Ang3lino        */ 

#ifndef QUEUE_H 
#define QUEUE_H 

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/*	Variables de la estructura element, puedes modificarla. */
typedef struct element {
	char Char,
String[100];
	int Integer;
	double Double;
	long Long;
	bool Boolean; 
} element;

/*	Definir un nodo que será utilizado para almacenar una posición de la Queue (Nodo), 
 *	lo que incluira a un element y a un apuntador al siguiente nodo.	*/
typedef	struct node {
	element e;
	struct node *next;
}node;

typedef struct Queue {
	node *front,
		 *back;
	int size;
} Queue;

/* Declaracion de queue. */
Queue *newQueue();	

/* Modificadores */
void enqueue (Queue *c, element e);	
element dequeue (Queue *c);	/* Retorna un elemento y lo elimina a la vez. */	
void clear  (Queue *c);  /* Limpia la queue, se puede utilizar nuevamente. */

/* Operaciones de consulta */
static int queueSize (Queue *c);		
bool queueEmpty (Queue *c);			
element front (Queue *c);		
element back (Queue *c);		
element Element (Queue *c, int n); /* Elemento (Element): Recibe una Queue y una posicion, y devuelve 
									   el n-esimo termino en la Queue. */

#endif

