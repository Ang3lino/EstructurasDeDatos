#include <stdio.h>
#include <stdlib.h>

void inicializar_tablero(int *** tablero, int n, int ** inicial){
	int i, j;
	*tablero = malloc(sizeof(int*) * n);
	for(i = 0; i < n; i++){
		(*tablero)[i] = malloc(sizeof(int) * n);
		for(j = 0; j < n; j++){
			if(inicial == NULL){
				(*tablero)[i][j] = 0;
			}else{
				(*tablero)[i][j] = inicial[i][j];
			}
		}
	}
}

void marcar_caminos(int ** marcas, int n, int x, int y, int cambio_x, int cambio_y){
	while(0 <= x && x < n && 0 <= y && y < n){
		marcas[x][y] = 1;
		x += cambio_x;
		y += cambio_y;
	}
}

int revisar(int ** tablero, int n){
	int i, j, k;
	int ** marcas = NULL;
	int movs[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
	inicializar_tablero(&marcas, n, NULL);
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(tablero[i][j] == 1){
				if(marcas[i][j] == 1){
					return 0;
				}
				for(k = 0; k < 8 ; k++){
					marcar_caminos(marcas, n, i, j, movs[k][0], movs[k][1]);
				}
			}
		}
	}
	return 1;
}

void agregar_solucion(int ** tablero, int n, int **** soluciones, int n_soluciones){
	int i, j;
	*soluciones = realloc(*soluciones, sizeof(int**) * (n_soluciones + 1));
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			inicializar_tablero(&(*soluciones)[n_soluciones], n, tablero);
		}
	}
}

void resolver(int ** tablero, int n, int col, int **** soluciones, int * n_soluciones){
	int i;
	if(col == n){
		agregar_solucion(tablero, n, soluciones, *n_soluciones);
		(*n_soluciones)++;
	}else{
		for(i = 0; i < n; i++){
			tablero[i][col] = 1;
			if(revisar(tablero, n)){
				resolver(tablero, n, col + 1, soluciones, n_soluciones);
			}
			tablero[i][col] = 0;
		}
	}
}

int main(){
	int *** soluciones = NULL;
	int n_soluciones = 0;
	int ** tablero = NULL;
	int n, i, j, k;
	scanf("%d", &n);
	inicializar_tablero(&tablero, n, NULL);
	resolver(tablero, n, 0, &soluciones, &n_soluciones);
	for(i = 0; i < n_soluciones; i++){
		for(j = 0; j < n; j++){
			for(k = 0; k < n; k++){
				printf("%d", soluciones[i][j][k]);
			}
			printf("\n");
		}
		printf("\n");
	}
	return 0;
}
