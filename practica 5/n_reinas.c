/*
PROBLEMA DE LAS N REINAS
Sea n un etnero tal que 3 < n < 10. Este programa halla todas las posibles
configuraciones de tableros de n*n, tal que existen n reinas colocadas
de tal forma que ninguna ataque a otra. Decimos que dos reinas se atacan
si y solo si están en la misma fila, columna o diagonal del tablero.
La solución propuesta usa el concepto de "backtracking", es decir,
prueba con todas las configuraciones posibles para hallar las correctas.

VERSION: 1.5

AUTORES: Equipo Quick-Coding

Compilación: gcc n_reinas.c -o n_reinas.exe
*/


//BIBLIOTECAS
#include <stdio.h>   //Entrada y salida estándar
#include <stdlib.h>  //Manejo de memoria dinámica

//FUNCIONES PROPUESTAS

/*
Descripción: dado un tablero, sus dimensiones y otro tablero inicial,
se prepara el tablero para usarse normalmente. Si el tablero inicial
es NULL, se rellena el tablero con ceros; si no, se copia el
contenido del inicial al tablero.
Recibe: apuntador a matriz tablero, entero n (dimensiones)
y tablero inicial.
Observaciones: hay que tener cuidado de mandar la referencia a tablero
(triple apuntador) y el tablero inicial (doble apuntador).
*/
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

/*
Descripción: dado un tablero, sus dimensiones y una coordenada,
determina si es posible colocar una reina ahí de tal forma que no
se ataque con alguna otra existente en el tablero
Recibe: matriz tablero, entero n (dimensiones), entero x, entero y
(coordenada inicial)
Devuelve: entero: 1 si sí se puede colocar la reina en la coordenada
especificada, 0 en otro caso
Obsrvaciones: el tablero debe ser distinto de NULL. (x, y) debe ser una
coordenada válida, dentro del tablero. Si en una casilla del tablero
hay un valor de 1 se asume que hay una reina, si hay un 0 se asume que
la casilla está vacía.
*/
int sePuedeColocarReina(int ** tablero, int n, int x, int y){
	int i, j;

	//Revisamos en la fila actual, hacia la izquierda
	for(j = 0; j < y; j++){
		if(tablero[x][j] == 1){
			return 0;
		}
	}

	//Revisamos hacia arriba a la izquierda
	for(i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--){
		if(tablero[i][j] == 1){
			return 0;
		}
	}

	//Revisamos hacia abajo a la izquierda
	for(i = x + 1, j = y - 1; i < n && j >= 0 ; i++, j--){
		if(tablero[i][j] == 1){
			return 0;
		}
	}

	//Notamos que no es necesario revisar:
	//-Hacia la derecha en la fila actual
	//-Hacia arriba a la derecha
	//-Hacia abajo a la derecha
	//-Hacia abajo en la columna actual;
	//ya que al implementar el backtracking correremos el tablero siempre
	//de arriba hacia abajo, y de izquierda a derecha; por lo que en las
	//direcciones enlistadas anteriormente se garantiza que no hay reina. 
	return 1;
}

/*
Descripción: dado un tablero, sus dimensiones, el arreglo de soluciones y el número de
soluciones al momento, se añade el tablero al arreglo de soluciones.
Recibe: matriz tablero, entero n (dimensiones), apuntador a arreglo de soluciones (tableros)
(sí, un apuntador cuádruple :v), entero n_soluciones
Observaciones: tablero debe ser distinto de NULL, tener cuidado con los apuntadores.
*/
void agregar_solucion(int ** tablero, int n, int **** soluciones, int n_soluciones){
	*soluciones = realloc(*soluciones, sizeof(int**) * (n_soluciones + 1));
	inicializar_tablero(&(*soluciones)[n_soluciones], n, tablero);
}

/*
Descripción: dado un tablero, sus dimensiones y un número de espacios,
lo muestra en pantalla. El número de espacios sirve como identación.
Recibe: matriz tablero, entero n (dimensiones), entero espacios.
Observaciones: tablero debe ser distinto de NULL, tener cuidado con los apuntadores,
espacios >= 0. El tablero tiene únicamente como entradas al 0 o al 1; si
es 0 se asume que no hay reina e imprimimos un punto, si es 1 se asume que
hay reina e imprimimos un cuadro (254 ascii).
*/
void imprimir_tablero(int ** tablero, int n, int espacios){
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < espacios; j++) printf(" ");
		for(j = 0; j < n; j++){
			if(tablero[i][j] == 1) printf("%c", 254);
			else printf(".");
		}
		printf("\n");
	}
}

/*
Descripción: dado un tablero, sus dimensiones, una columna, el arreglo de soluciones y
el número de soluciones; esta función se encargará de buscar todas las configuraciones
posibles para colocar a las n reinas en el tablero, usando el método de backtracking,
es decir, buscando mediante fuerza bruta todas las soluciones
Recibe: matriz tablero, entero n (dimensiones), entero col (columna actual),
apuntador a arreglo de soluciones (tableros), apuntador a entero de n_soluciones,
char imprimir
Observaciones: el tablero debe estar inicializado en ceros. Si el char imprimir es 'S',
se irá mostrando el procedimiento del backtracking, si es 'N', no se mostrará.
*/
void resolver(int ** tablero, int n, int col, int **** soluciones, int * n_soluciones, char imprimir){
	int i;
	if(col == n){
		//Si ya llegamos a una columna más allá de la última, quiere decir que este tablero
		//es una configuración válida, pues pasó todas las pruebas.
		//Procedemos a añadirlo a las soluciones.
		agregar_solucion(tablero, n, soluciones, *n_soluciones);
		(*n_soluciones)++;
		if(imprimir == 'S'){
			for(i = 0; i < col - 1; i++) printf(" ");
			printf("Encontramos una solucion.\n\n");
		}
	}else{
		for(i = 0; i < n; i++){
			//Marcamos
			tablero[i][col] = 1;
			//Imprimimos el tablero
			if(imprimir == 'S'){
				imprimir_tablero(tablero, n, col);
				printf("\n");
			}
			if(sePuedeColocarReina(tablero, n, i, col)){
				//Llamamos recursivamente, avanzando a la siguiente columna
				resolver(tablero, n, col + 1, soluciones, n_soluciones, imprimir);
			}
			//Desmarcamos, hacemos el "backtracking"
			tablero[i][col] = 0;
		}
	}
}

//PROGRAMA PRINCIPAL
int main(){
	//Declaramos las variables principales
	int *** soluciones = NULL;
	int n_soluciones = 0;
	int ** tablero = NULL;
	int n;
	char imprimir;

	//Contadores auxiliares
	int i, j, k;

	//Leemos el valor de n
	printf("Introduce la dimension n del tablero: ");
	scanf("%d", &n);

	//Le damos a escoger al usuario si quiere mostrar procedimiento o solo las soluciones
	printf("Introduce S para mostrar el procedimiento usado para encontrar las soluciones, o N para mostrar solo las soluciones: ");
	scanf(" %c", &imprimir);

	//Inicializamos el tablero con ceros
	inicializar_tablero(&tablero, n, NULL);

	//Hallamos mediante backtracking todas las configuraciones comenzando en
	//la columna 0, que guardaremos en el arreglo de soluciones y contaremos
	//en el entero n_soluciones 
	resolver(tablero, n, 0, &soluciones, &n_soluciones, imprimir);

	//Mostramos las configuraciones que resultaron correctas
	printf("Soluciones encontradas: %d\n\n", n_soluciones);
	for(i = 0; i < n_soluciones; i++){
		printf("Tablero %d:\n", i + 1);
		imprimir_tablero(soluciones[i], n, 0);
		printf("\n");
	}

	//Liberamos la memoria usada
	for(i = 0; i < n; i++){
		free(tablero[i]);
	}
	free(tablero);
	for(i = 0; i < n_soluciones; i++){
		for(j = 0; j < n; j++){
			free(soluciones[i][j]);
		}
		free(soluciones[i]);
	}
	free(soluciones);

	return 0; //FIN DEL PROGRAMA
}
