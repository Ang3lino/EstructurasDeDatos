#include <stdio.h>
#include "PilaDin.h"

char * nombre_disco(int disco){
	switch(disco){
		case 0: return "origen";
		case 1: return "auxiliar";
		case 2: return "destino";
	}
}

void imprime_pila(pila * p){
	nodo * tmp = p->tope;
	while(tmp != NULL){
		printf("%d ", tmp->e.entero);
		tmp = tmp->abajo;
	}
}

void mostrar_torres(pila * torres){
	printf("Origen: ");
	imprime_pila(&torres[0]);
	printf("\nAuxiliar: ");
	imprime_pila(&torres[1]);
	printf("\nDestino: ");
	imprime_pila(&torres[2]);
	printf("\n\n");
}

void mover(int n, int origen, int destino, pila * torres, int * movs){
	(*movs)++;
	Push(Pop(&torres[origen]), &torres[destino]);
	printf("Movimiento %d: Mover el disco %d desde %s hasta %s.\n", *movs, n, nombre_disco(origen), nombre_disco(destino));
	mostrar_torres(torres);
}

void hanoi(int n, int origen, int auxiliar, int destino, pila * torres, int * movs){
	if(n == 1){
		mover(n, origen, destino, torres, movs);
	}else{
		hanoi(n - 1, origen, destino, auxiliar, torres, movs);
		mover(n, origen, destino, torres, movs);
		hanoi(n - 1, auxiliar, origen, destino, torres, movs);
	}
}

int main(){
	int n, i;
	elemento e;
	int movs = 0;
	pila torres[3];
	for(i = 0; i < 3; i++) Initialize(&torres[i]);
	scanf("%d", &n);
	for(i = n; i >= 1; i--){
		e.entero = i;
		Push(e, &torres[0]);
	}
	mostrar_torres(torres);
	hanoi(n, 0, 1, 2, torres, &movs);
	for(i = 0; i < 3; i++) Destroy(&torres[i]);
	return 0;
}
