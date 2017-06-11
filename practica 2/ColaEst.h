#ifndef COLAEST_H
#define COLAEST_H

#define TRUE 1
#define FALSE 0
#define MAX_ELEMENTS 10000
typedef char boolean;

typedef struct elemento
{
	//Variables de la estructura "elemento" (El usuario puede modificar)
	//Simulación 2
	char nombre[45], actividad[200], id[45];
	int tiempo, contador;
	//Simulación 1 y 3
	int ID, tipo;
} elemento;

typedef struct{
	elemento *A;
	int frente;
	int final;
} cola;

void Initialize(cola *c);
void Destroy(cola *c);
int Size(cola *c);
boolean Empty(cola *c);
boolean Queue(cola *c, elemento e);
elemento Dequeue(cola *c);
elemento Front(cola *c);
elemento Final(cola *c);
elemento Element(cola *c, int n);

#endif