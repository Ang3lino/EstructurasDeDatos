//LIBRERIA: Cabecera del TAD Pila Dinámica

//Librería para poder realizar operaciones de memoria
#include <stdlib.h>

//Definiciones de constantes
#define TRUE 1
#define FALSE 0

//Definiciones de tipos de dato

//Definimos un boolean modelado como un char
typedef char boolean;

//Definimos un elemento, que dentro puede tener lo que sea
typedef struct{
	int entero;
	char caracter;
	float flotante;
	double doble;
	int x;
	int y;
} elemento;

//Definimos un nodo, que contiene un elemento y un apuntador al nodo que representará el enlace al nodo de abajo
typedef struct nodo{
	elemento e;           //Elemento a almacenar en cada nodo de la pila
	struct nodo * abajo;  //Apuntador al nodo de abajo
} nodo;

//Definimos la pila, que incluirá un apuntador a nodo representando el tope de la pila y una variable entera para almacenar el tamaño
typedef struct{
	nodo * tope;
	int tamano;
} pila;

//Declaración de funciones
void Initialize(pila *p);          //Inicializar pila para su uso normal
void Destroy(pila *p);             //Eliminar la pila
int Size(pila *p);                 //Obtener el número de elementos en la pila
boolean IsEmpty(pila *p);          //Verificar si la pila está vacía
boolean Push(elemento e, pila *p); //Empilar, introducir un elemento a la pila
elemento Pop(pila *p);             //Desempilar, sacar un elemento de la pila
elemento Top(pila *p);             //Consultar el elemento del tope de la pila sin sacarlo
