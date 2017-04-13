/*
	DESCRIPCIÓN:
	Programa que simula la llegada de personas a un banco.
	El banco consta de tres colas para distintos tipos de personas:
	-cola 0: preferentes
	-cola 1: clientes
	-cola 2: usuarios
	Contamos con n cajeros disponibles, y los tiempos de llegada y de atencion son fijos 
	durante la simulación.
	El orden de preferencia es: preferentes > clientes > usuarios.
	Sin embargo, no se debe permitir que pasen más de 5 preferentes o clientes sin que un 
	usuario en espera sea atendido.

	VERSION: 1.5

	FECHA: 12/04/2017

	AUTORES:
	Ontiveros Salazar Alan Enrique

	Compilación: gcc programa3.c Cola(Din|Est|EstCirc).c presentacion(Win|Lin).c -o programa3.exe
*/

//LIBRERIAS
#include "ColaDin.h"
//#include "ColaEst.h"
//#include "ColaEstCirc.h"
#include <stdio.h>
#include "presentacion.h"

/*
	Definimos a un cajero, podremos saber si está ocupado o libre;
	y la persona atendida actualmente en caso de que esté ocupado
*/
typedef struct{
	boolean ocupado;
	elemento persona;
} cajero;

/*
	Definimos a la simulación:
	-n_cajeros: cuántos cajeros hay disponibles para atender a las personas
	-tiempo_atencion: cada cuándo se desocupan todos los cajeros
	-tiempo_clientes: cada cuándo llegan los clientes
	-tiempo_usuarios: cada cuándo llegan los usuarios
	-tiempo_preferentes: cada cuánto llegan los preferentes
	-clientes_y_preferentes: cuántos clientes y preferentes han pasado desde el último 
	 usuario
	-colas[3]: las tres colas de nuestra simulación, 0:preferentes, 1:clientes, 2:usuarios
	-cajeros[9]: los cajeros de nuestra simulacion
*/
typedef struct 
{
	int n_cajeros;
	int tiempo_atencion;
	int tiempo_clientes;
	int tiempo_usuarios;
	int tiempo_preferentes;
	int clientes_y_preferentes;
	cola colas[3];
	cajero cajeros[9];
} simulacion;


/*
	Descripción: dada una simulación, pone en FALSE la propiedad de todos los cajeros.
	Recibe: simulacion * S
	Devuelve: el número de cajeros que pasaron de ocupado a desocupado
	Observaciones: n_cajeros < 10
*/
int DesocuparCajeros(simulacion * S){
	int i, cuantos = 0;
	for(i = 0; i < S->n_cajeros; i++){
		if(S->cajeros[i].ocupado)
			cuantos++;
		S->cajeros[i].ocupado = FALSE;
	}
	return cuantos;
}

/*
	Descripción: dada una simulación, verifica qué cajero está disponible.
	Si hay varios, devuelve el primero que encuentra. Si no hay ninguno, devuelve -1
	Recibe: simulación * S
	Devuelve: int, la posición del cajero encontrado
	Observaciones: n_cajeros < 10, la propiedad de 'ocupado' en cada cajero
	debe estar inicializada a TRUE o a FALSE
*/
int RevisarCajeroLibre(simulacion * S){
	int i;
	for(i = 0; i < S->n_cajeros; i++){
		if(S->cajeros[i].ocupado == FALSE){
			return i;
		}
	}
	return -1;
}

/*
	Descripción: dada una persona y su tipo de acuerdo a la jerarquía de atención del 
	banco, la encola en la cola de acuerdo a su tipo en la simulación.
	Recibe: int n_persona, int tipo, simulacion * S
	Devuelve:
	Observaciones: las tres colas de la simulación deben estar inicializadas,
	0 <= tipo <= 2
*/
void FormarPersona(int n_persona, int tipo, simulacion * S){
	elemento persona;
	persona.ID = n_persona;
	persona.tipo = tipo;
	Queue(&S->colas[tipo], persona);
	return;
}

/*
	Descripción: dada una persona, su tipo y una posición de cajero válida,
	la pone como la persona atendida en ese cajero y lo pone como ocupado.
	Recibe: int n_persona, int tipo, int donde, simulacion * S
	Devuelve:
	Observaciones: 0 <= tipo <= 2
*/
void PasarPersona(int n_persona, int tipo, int donde, simulacion * S){
	elemento persona;
	persona.ID = n_persona;
	persona.tipo = tipo;
	S->cajeros[donde].persona = persona;
	S->cajeros[donde].ocupado = TRUE;
	if(tipo == 2)
		S->clientes_y_preferentes = 0;
	else
		S->clientes_y_preferentes++;
}

/*
	Descripción: dado un tipo de persona y la simulación, determina si esa persona puede pasar a algún cajero,
	respetando las políticas del banco. Si sí puede pasar, devuelve la posición del cajero candidato, si no
	devuelve -1.
	Recibe: int tipo, simulacion * S
	Devuelve: int, la posición del cajero al que la persona puede pasar.
	Observaciones: las tres colas de la simulación deben estar inicializadas,
	0 <= tipo <= 2
*/
int PersonaPuedePasar(int tipo, simulacion * S){
	int disponible = RevisarCajeroLibre(S);
	if(disponible == -1) return -1;
	if(S->clientes_y_preferentes == 5){
		if((tipo == 0 || tipo == 1) && !Empty(&S->colas[2]))
			return -1;
		return disponible;
	}
	return disponible;
}

/*
	Descripción: dada una persona, su tipo y la simulación, determina
	si la persona podría pasar directamente a algún cajero disponible
	o se tendría que formar a su cola determinada.
	Recibe: int n_persona, int tipo, simulacion * S
	Devuelve:
	Observaciones: las tres colas de la simulación deben estar inicializadas,
	0 <= tipo <= 2
*/
void ProcesarLlegadaPersona(int n_persona, int tipo, simulacion * S){
	int pos = PersonaPuedePasar(tipo, S);
	if(Empty(&S->colas[tipo]) && pos != -1){
		PasarPersona(n_persona, tipo, pos, S);
	}else{
		FormarPersona(n_persona, tipo, S);
	}
	return;
}

/*
	Descripción: esta función se ejecuta cada que es tiempo de atención,
	y determina si las personas esperando al frente de cala cola pueden pasar a algún cajero.
	Si sí pueden, las pasa y las desencola.
	Recibe: simulacion * S
	Devuelve: el número de personas que lograron pasar a algun cajero
	Observaciones: las tres colas de la simulación deben estar inicializadas,
	0 <= tipo <= 2
*/
int ProcesarColas(simulacion * S){
	int i = 0, pos, cuantas = 0;
	elemento persona;
	for(i = 0; i < 3; i++){
		if(!Empty(&S->colas[i])){
			persona = Front(&S->colas[i]);
			pos = PersonaPuedePasar(persona.tipo, S);
			if(pos != -1){
				PasarPersona(persona.ID, persona.tipo, pos, S);
				Dequeue(&S->colas[i]);
				cuantas++;
			}
		}
	}
	return cuantas;
}

//Programa principal
int main(){
	//Inicializamos una simulación
	simulacion S;
	S.clientes_y_preferentes = 0;

	//Variables para controlar el tiempo
	int tiempo_actual = 0;
	int tiempo_base = 10;

	//Contadores auxiliar
	int i, j;

	//Elemento auxiliar
	elemento e;

	//Contador para identificar consecutivamente a cada persona que va llegando
	int n_persona = 0;

	//Estas variables sirven para llevar el control de los mensajes de la simulacion
	int refrescar = 1;
	char mensajes[5][100];

	//Leemos la entrada de la simulación
	printf("Introduce el numero de cajeros disponibles: ");
	scanf("%d", &S.n_cajeros);
	printf("Introduce el tiempo de atencion: ");
	scanf("%d", &S.tiempo_atencion);
	printf("Introduce el tiempo de llegada de los clientes: ");
	scanf("%d", &S.tiempo_clientes);
	printf("Introduce el tiempo de llegada de los usuarios: ");
	scanf("%d", &S.tiempo_usuarios);
	printf("Introduce el tiempo de llegada de los preferentes: ");
	scanf("%d", &S.tiempo_preferentes);
	
	//Inicializamos las tres colas
	for(i = 0; i < 3; i++)
		Initialize(&S.colas[i]);

	//Al principio, todos los cajeros están desocupados
	DesocuparCajeros(&S);
	
	//Ejecutamos la simulación de manera indefinida
	while(TRUE){
		EsperarMiliSeg(tiempo_base);
		tiempo_actual += tiempo_base;
		i = 0;

		//Los cajeros han finalizado de atender a las personas que estaban atendiendo
		if(tiempo_actual % S.tiempo_atencion == 0){
			if(DesocuparCajeros(&S) > 0)
				sprintf(mensajes[i++], "Los cajeros terminaron de atender.\n");
			if(ProcesarColas(&S) > 0)
				sprintf(mensajes[i++], "Pasaron nuevas personas a los cajeros.\n");
			refrescar = 1;
		}

		//Llegó un preferente
		if(tiempo_actual % S.tiempo_preferentes == 0){
			n_persona++;
			ProcesarLlegadaPersona(n_persona, 0, &S);
			sprintf(mensajes[i++], "Llego un preferente con ID %d.\n", n_persona);
			refrescar = 1;
		}

		//Llegó un cliente
		if(tiempo_actual % S.tiempo_clientes == 0){
			n_persona++;
			ProcesarLlegadaPersona(n_persona, 1, &S);
			sprintf(mensajes[i++], "Llego un cliente con ID %d.\n", n_persona);
			refrescar = 1;
		}

		//Llegó un usuario
		if(tiempo_actual % S.tiempo_usuarios == 0){
			n_persona++;
			ProcesarLlegadaPersona(n_persona, 2, &S);
			sprintf(mensajes[i++], "Llego un usuario con ID %d.\n", n_persona);
			refrescar = 1;
		}

		//Mostramos la información de la simulación, solo si hubo algun cambio
		if(refrescar){
			BorrarPantalla();
			printf("Informacion del banco\n\n");
			for(j = 0; j < i; j++)
				printf(mensajes[j]);
			printf("\n");
			for(i = 0; i < 3; i++){
				printf("Cola de ");
				if(i == 0)
					printf("preferentes (%d): ", Size(&S.colas[i]));
				else if(i == 1)
					printf("clientes    (%d): ", Size(&S.colas[i]));
				else if(i == 2)
					printf("usuarios    (%d): ", Size(&S.colas[i]));
				for(j = 1; j <= Size(&S.colas[i]); j++){
					e = Element(&S.colas[i], j);
					printf("%d", e.ID);
					if(j < Size(&S.colas[i]))
						printf(" <-- ");
				}
				printf("\n\n");
			}
			for(i = 0; i < S.n_cajeros; i++){
				e = S.cajeros[i].persona;
				printf("Cajero %d: ", i + 1);
				if(S.cajeros[i].ocupado){
					printf("ocupado: (ID: %d, tipo: ", e.ID);
					switch(e.tipo){
						case 0:{
							printf("preferente)");
							break;
						}
						case 1:{
							printf("cliente)");
							break;
						}
						case 2:{
							printf("usuario)");
							break;
						}
					}
				}else
					printf("desocupado");
				printf("\n");
			}
			printf("\nTiempo actual: %d\n\n\n", tiempo_actual);
			refrescar = 0;
		}
	}
	return 0; //FIN
}
