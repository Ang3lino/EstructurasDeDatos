/*
DESCRIPCIÓN:
Programa que simula la atención de clientes en un supermercado.
-Contamos con n cajeras disponibles para atenderlos, cada una cuenta con
su propio tiempo de ateción.
-Los clientes llegan cada cierto tiempo, se forman al azar en alguna caja
y se quedan ahí hasta que son atendidos.
-Si ya se atendieron al menos 100 clientes y no hay clientes en las cajas,
se cerrará el supermercado.

VERSIÓN: 1.0

AUTORES: Equipo Quick-Coding

FECHA: 12/04/2016

Compilación: gcc programa1.c Cola(Din|Est|EstCirc).c presentacion(Win|Lin).c -o programa1.exe

*/

//LIBRERIAS
#include "ColaDin.h"
#include <stdio.h>
#include "presentacion.h"
#include <time.h>
#include <stdlib.h>

/*
Definimos una estructura simulación:
-char nombre[100]: string que contiene el nombre del supermercado
-int n: entero que contiene el número de cajeras disponibles
-int tiempos_cajeras[9]: cada cuándo termina de atender cada cajera
-cola cajeras[9]: las n filas de la simulación
-int tiempo_cliente: cada cuándo llega un nuevo cliente
*/
typedef struct
{
	char nombre[100];
	int n;
	int tiempos_cajeras[9];
	cola cajeras[9];
	int tiempo_cliente;
} simulacion;

//FUNCIONES PROPUESTAS

/*
Descripción: dados dos enteros, mínimo y máximo, devuelve un número
aleatorio en el intervalo [minimo, maximo]
Recibe: entero minimo, entero maximo
Devuelve: entero, el número aleatorio
*/
int aleatorio(int minimo, int maximo){
	return rand() % (maximo - minimo + 1) + minimo;
}

/*
Descripción: dado un ID de un cliente, un índice de una cajera y
una simulación S, se encola el cliente a la cajera correspondiente
Recibe: int n_cliente, int cajera, simulacion * S
Observaciones: todas las colas de la simulación deben estar inicializadas
*/
void FormarCliente(int n_cliente, int cajera, simulacion * S){
	elemento cliente;
	cliente.ID = n_cliente;
	Queue(&S->cajeras[cajera], cliente);
}

/*
Descripción: dado un índice de una cajera y una simulación, se desencola
al cliente que está hasta enfrente si la cola especificada no está vacía.
Recibe: int cajera, simulacion * S
Devuelve: entero; el ID del cliente desencolado, -1 en caso de que la
cola estuviera vacía.
Observaciones: todas las colas de la simulación deben estar inicializadas
*/
int ProcesarCajera(int cajera, simulacion * S){
	if(!Empty(&S->cajeras[cajera])){
		return Dequeue(&S->cajeras[cajera]).ID;
	}
	return -1;
}

/*
Descripción: dada una simulación, determina si todas las cajeras están vacías.
Recibe: simulacion * S
Devuelve: entero; 1 si todas las cajeras están vacías, 0 en otro caso
*/
int CajerasVacias(simulacion * S){
	int i;
	for(i = 0; i < S->n; i++){
		if(!Empty(&S->cajeras[i]))
			return 0;
	}
	return 1;
}

//PROGRAMA PRINCIPAL
int main(){
	//Declaramos una simulación
	simulacion S;

	//Contadores auxiliares
	int i, j;

	//Variables para controlar el tiempo
	int tiempo_actual = 0;
	int tiempo_base = 10;

	//Contador para identificar consecutivamente a cada cliente que va llegando
	int n_cliente = 0;
	int ID;
	elemento cliente;
	int cajera_escogida;

	//Estas variables sirven para llevar el control de los mensajes de la simulacion
	char mensajes[10][100];
	int m;
	int refrescar = 1;

	//Inicializamos la semilla para generar números aleatorios
	srand(time(0));

	//Leemos los datos de la simulación
	printf("Introduce el nombre del supermercado: ");
	fgets(S.nombre, 100, stdin);
	printf("Introduce el numero de cajeras: ");
	scanf("%d", &S.n);
	for(i = 0; i < S.n; i++){
		printf("Introduce el tiempo de atencion de la cajera %d: ", i + 1);
		scanf("%d", &S.tiempos_cajeras[i]);
		Initialize(&S.cajeras[i]);
	}
	printf("Introduce el tiempo de llegada de los compradores: ");
	scanf("%d", &S.tiempo_cliente);

	//Ejecutamos la simulación de manera indefinida
	while(TRUE){
		//Esperamos el tiempo base e incrementamos el tiempo actual
		EsperarMiliSeg(tiempo_base);
		tiempo_actual += tiempo_base;
		m = 0;

		//Llegó un cliente
		if(tiempo_actual % S.tiempo_cliente == 0){
			//El cliente escogerá una caja al azar
			cajera_escogida = aleatorio(0, S.n - 1);
			n_cliente++;
			FormarCliente(n_cliente, cajera_escogida, &S);
			sprintf(mensajes[m++], "Llego el cliente %d a la caja %d.\n", n_cliente, cajera_escogida + 1);
			refrescar = 1;
		}

		//Revisamos las cajas a ver si a alguna le toca finalizar de atender
		for(i = 0; i < S.n; i++){
			//La (i+1)-ésima cajera ha finalizado de atender al cliente actual 
			if(tiempo_actual % S.tiempos_cajeras[i] == 0){
				ID = ProcesarCajera(i, &S);
				if(ID != -1){
					//Se atendió correctamente a un cliente
					sprintf(mensajes[m++], "La cajera %d termino de atender al cliente %d.\n", i + 1, ID);
					refrescar = 1;
				}
			}
		}

		//Imprimimos la información de la simulación, solo si hubo algun cambio
		if(refrescar){
			BorrarPantalla();
			printf("%s\n\n", S.nombre);

			for(j = 0; j < m; j++)
				printf("%s", mensajes[j]);
			printf("\n");

			for(i = 0; i < S.n; i++){
				printf("Cajera %d (%d): ", i + 1, Size(&S.cajeras[i]));
				for(j = 1; j <= Size(&S.cajeras[i]); j++){
					if(Size(&S.cajeras[i]) > 10 && j >= 6 && j <= (Size(&S.cajeras[i]) - 5)){
						printf(" <-- ...");
						j = Size(&S.cajeras[i]) - 5;
					}else{
						if(j > 1)
							printf(" <-- ");
						cliente = Element(&S.cajeras[i], j);
						printf("%d", cliente.ID);
					}
				}
				printf("\n");
			}
			printf("\nClientes atendidos: %d\nTiempo actual: %dms\n\n\n", n_cliente, tiempo_actual);
			refrescar = 0;
		}

		//Si ya atendimos al menos a 100 clientes y todas las cajeras están vacías, cerramos
		if(n_cliente >= 100 && CajerasVacias(&S)){
			printf("Hemos cerrado.\n");
			break;
		}
	}

	return 0; //FIN
}
