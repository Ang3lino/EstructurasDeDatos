
#ifndef STACK_H
#define STACK_H

//BIBLIOTECA: Cabecera del TAD Pila Dinámica

#include <stdlib.h>
#include <stdbool.h>

//Definimos un elemento, que dentro puede tener lo que sea
typedef struct element {
   int entero;
   char caracter;
   float flotante;
   double doble;
} element;

// Definimos un nodo, que contiene un elemento y un apuntador al nodo que representará el 
// enlace al nodo de abajo
typedef struct nodo{
	element e;           //Elemento a almacenar en cada nodo de la pila
	struct nodo * abajo;  //Apuntador al nodo de abajo
} nodo;

// Definimos la pila, que incluirá un apuntador a nodo representando el tope de la pila y 
// una variable entera para almacenar el tamaño
typedef struct stack{
	nodo * tope;
	int tamano;
} Stack;

// Prototipos 
Stack *newStack (void);				//Declara la stack
void destroy(Stack *p);             //Eliminar la Stack
static int stackSize(Stack *p);                 //Obtener el número de elementos en la Stack
bool stackEmpty(Stack *p);          //Verificar si la Stack está vacía
bool push(Stack *, element e); //Empilar, introducir un elemento a la Stack
element pop(Stack *p);             //Desempilar, sacar un elemento de la Stack
element top(Stack *p);             //Consultar el elemento del tope de la Stack sin sacarlo

#endif

