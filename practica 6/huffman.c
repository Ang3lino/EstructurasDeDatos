﻿/*
DESCRIPCIÓN: Programa que implementa la codificación y la decodificación
de archivos, usando el algoritmo de codificación de Huffman.
De manera breve, dado un alfabeto y la frecuencia de cada símbolo
de este en un mensaje; le asigna a cada símbolo del mensaje una nueva
codificación, con base en un árbol binario que se va generando como
resultado de la frecuencia de cada símbolo. Tiene la ventaja de que
símbolos con alta frecuencia tienen una longitud de codificación menor.

AUTORES: Equipo Quick-Coding

VERSIÓN: 2.0

FECHA: 24/04/2017

COMPILACIÓN: gcc ArbolBin.c huffman.c -o huffman.exe
*/

//BIBLIOTECAS
#include "ArbolBin.h"
#include <stdio.h>
#include <string.h>

/*
Esta estructura almacena la codificación de un caracter (en 0 y 1 char),
y el tamaño de dicha codificación.
*/
typedef struct{
	Char * codificacion;
	ull tamano;
} InfoCaracter;

/*
DESCRIPCIÓN: Esta función prende un bit específico de un arreglo de Chars
RECIBE: arreglo de Chars y una posición entera
*/
void PrenderBit(Char * datos, ull posicion){
	ull i = posicion >> 3;		//Calculamos en qué byte está el bit que buscamos
	int j = posicion & 7;		//Calculamos la posición del bit dentro del byte
	datos[i] |= (128 >> j);		//Mediante un OR, prendemos el bit correspondiente
	return;
}

/*
DESCRIPCIÓN: Esta función apaga un bit específico de un arreglo de Chars
RECIBE: arreglo de Chars y una posición entera
*/
void ApagarBit(Char * datos, ull posicion){
	ull i = posicion >> 3;		//Calculamos en qué byte está el bit que buscamos
	int j = posicion & 7;		//Calculamos la posición del bit dentro del byte
	datos[i] &= ~(128 >> j);	//Mediante un AND, apagamos el bit correspondiente
	return;
}

/*
DESCRIPCIÓN: dados dos enteros positivos "num" y "den", esta función
calcula el menor entero mayor o igual a num/den.
RECIBE: dos enteros positivos, "num" y "den"
DEVUELVE: el menor entero mayor o igual a num/den
OBSERVACIONES: ambos números deben ser enteros positivos y den != 0
*/
ull techo(ull num, ull den){
	if(num % den == 0)
		return num / den;
	else
		return num / den + 1;
}

/*
DESCRIPCIÓN: dado un mensaje, un arreglo de frecuencias enteras y la longitud en BYTES
del mensaje, se contabiliza la frecuencia de cada caracter que aparece en mensaje.
RECIBE: Char * mensaje, ull * frecuencias, ull longitud
OBSERVACIONES: la longitud del arreglo de frecuencias debe ser 256
*/
void obtener_frecuencias(Char * mensaje, ull * frecuencias, ull longitud){
	ull i;
	for(i = 0; i < 256; i++)		//Inicializamos todas las frecuencias a cero
		frecuencias[i] = 0;
	for(i = 0; i < longitud; i++)	//Mediante el método de cubeta, contabilizamos la
		frecuencias[mensaje[i]]++;	//frecuencia de cada caracter
	return;
}

/*
DESCRIPCIÓN: dado un caracter, un recorrido por el árbol binario de ceros y unos,
el tamaño del recorrido y un arreglo de información de caracteres; esta
función copia el recorrido a la información del caracter dado
RECIBE: Char c, Char * camino, ull tamano, InfoCaracter * info
OBSERVACIONES: la longitud de info debe ser 256, el recorrido se almacena con
los enteros '0' y '1', usando el '0' para la izquierda y el '1' para la derecha.
*/
void copiar(Char c, Char * camino, ull tamano, InfoCaracter * info){
	ull i;
	info[c].tamano = tamano;
	info[c].codificacion = malloc(tamano * sizeof(Char));
	for(i = 0; i < tamano; i++)
		info[c].codificacion[i] = camino[i];
	return;
}

/*
DESCRIPCIÓN: dada una posición de un árbol binario, un recorrido de '0' y '1',
una posición y un InfoCaracter; esta función obtiene todas las codificaciones
para todos los caracteres que se encuentren en las hojas del árbol, mediante
un recorrido inorden. Cuando vamos por la izquierda, anexamos un 0, y por la
derecha un 1. Estas codificaciones son guardadas en info.
RECIBE: nodo * p, Char * camino, ull pos, InfoCaracter * info
*/
void obtener_codificaciones(nodo * p, Char * camino, ull pos, InfoCaracter * info){
	if(p != NULL){
		if(IsLeaf(p)){		//Si la posición es una hoja, almacenamos la codificación de su Char
			copiar(p->c, camino, pos, info);
		}
		camino[pos] = 0;	//Vamos por la izquierda recursivamente
		obtener_codificaciones(p->izq, camino, pos + 1, info);
		camino[pos] = 1;	//Vamos por la derecha recursivamente
		obtener_codificaciones(p->der, camino, pos + 1, info);
	}
	return;
}

/*
DESCRIPCIÓN: esta función es auxiliar para comparar dos nodos y ordenar un arreglo
de mayor a menor, mediante su frecuencia. Es usada por la función qsort de C.
RECIBE: const void * a, const void * b
DEVUELVE: entero: 1 si la frecuencia del segundo es mayor a la del primero,
-1 si la frecuencia del segundo es menor a la del primero,
0 si ambas frecuencias son iguales.
*/
int comparador(const void * a, const void * b){
	const nodo * e1 = *(const nodo**)a;
	const nodo * e2 = *(const nodo**)b;
	if(e2->frecuencia > e1->frecuencia)
		return 1;
	else if(e2->frecuencia < e1->frecuencia)
		return -1;
	else
		return 0;
}

/*
DESCRIPCIÓN: Dado un mensaje, una referencia a un árbol binario, un arreglo para almacenar
la codificación y la longitud en BYTES del mensaje, esta función ejecuta el algoritmo de codificación
de Huffman, almacenando en resultado la codificación y el árbol binario resultante en
arbol_huffman.
RECIBE: Char * mensaje, nodo ** arbol_huffman, Char * resultado, ull longitud
DEVUELVE: entero, indicando la longitud en BITS del mensaje codificado.
*/
ull codificar(Char * mensaje, nodo ** arbol_huffman, Char * resultado, ull longitud){
	ull frecuencias[256];				//Declaramos un arreglo de 256 frecuencias, una para cada símbolo ASCII
	Char camino[256];					//Declaramos un camino para ir almacenando los recorridos, a lo más serán de 256
	InfoCaracter codificaciones[256];	//Declaramos un arreglo para almacenar 256 codificaciones por caracter
	nodo * arboles[256];				//Declaramos un arreglo de 256 elementos, aquí se irá creando el árbol huffman
	ull i, j;							//Contadores auxiliares
	ull bits = 0;						//Aquí se irán contabilizando los bits del mensaje codificado
	int n_arboles = 0;					//Aquí contabilizamos cuántos árboles tenemos
	nodo * nodo_izq, * nodo_der;		//Elementos auxiliares para el momento de ejecutar el algoritmo de ordenar los árboles
	Char actual;						//Caracter actual que se va a estar leyendo del mensaje original

	obtener_frecuencias(mensaje, frecuencias, longitud);		//Obtenemos las frecuencias por caracter del mensaje original
	for(i = 0; i < 256; i++){
		if(frecuencias[i] > 0){									//Si la frecuencia es mayor a cero, creamos un nuevo árbol
			arboles[n_arboles] = NewNode(i);
			arboles[n_arboles]->frecuencia = frecuencias[i];
			n_arboles++;										//Incrementamos el número de árboles
		}
	}

	while(n_arboles > 1){										//Mientras tengamos más de un árbol, ejecutamos el algoritmo
		qsort(arboles, n_arboles, sizeof(nodo*), comparador);	//Ordenamos el arreglo de elementos, de mayor a menor
		nodo_izq = arboles[n_arboles - 1];						//Obtenemos el último árbol del arreglo, es decir, el de menor frecuencia
		nodo_der = arboles[n_arboles - 2];						//Obtenemos el penúltimo árbol del areglo, el que tiene la segunda menor frecuencia.
		arboles[n_arboles - 2] = NewNode(0);					//Juntamos los dos árboles anteriores
		arboles[n_arboles - 2]->frecuencia = nodo_izq->frecuencia + nodo_der->frecuencia;	//Sumamos sus frecuencias
		arboles[n_arboles - 2]->izq = nodo_izq;					//Asignamos el hijo izquierdo
		arboles[n_arboles - 2]->der = nodo_der;					//Aignamos el hijo derecho
		n_arboles--;											//Disminuímos en uno el número de árboles, puesto que los últimos dos se convirtieron en uno
	}

	*arbol_huffman = arboles[0];					//Lo copiamos para que sea accesible fuera de la función
	obtener_codificaciones(arboles[0], camino, 0, codificaciones);	//Obtenemos las codificaciones para cada caracter, mirando en las hojas del árbol

	for(i = 0; i < longitud; i++){		//Iteramos sobre todo el mensaje original
		actual = mensaje[i];
		for(j = 0; j < codificaciones[actual].tamano; j++){		//Iteramos sobre la codificación del caracter actual
			if(codificaciones[actual].codificacion[j] == 0)
				ApagarBit(resultado, bits++);					//Si es cero esta parte del recorrido, apagamos el bit actual
			else if(codificaciones[actual].codificacion[j] == 1)
				PrenderBit(resultado, bits++);					//Si es uno esta parte del recorrido, prendemos el bit actual
		}														//En ambos casos, incrementamos en uno el número de bits
	}

	return bits;
}
/*
DESCRIPCIÓN: dado un mensaje codificado, un arbol huffman, un arreglo para almacenar la decodificación
y la longitud en BITS del mensaje codificado, esta función recupera el mensaje codificado, con base
en el arbol binario de huffman creado durante la codificación.
RECIBE: Char * mensaje, nodo * arbol_huffman, Char * resultado, ull bits
DEVUELVE: La longitud en BYTES del mensaje decodificado.
*/
ull decodificar(Char * mensaje, nodo * arbol_huffman, Char * resultado, ull bits){
	ull i, j;									//Contadores auxiliares
	ull bits_a_leer;							//En cada iteración excepto en la última, leeremos 8 bits
	ull bytes = 0;								//Aquí se contabilizan los bytes del mensaje decodificado
	ull longitud = techo(bits, 8);				//Obtenemos la longitud en bytes del mensaje codificado
	nodo * actual = arbol_huffman;				//Leemos la raíz del árbol
	if(IsLeaf(actual)){							//Este if se ejecutará si y solo si la cadena decodificada consta de 1 byte,
		resultado[bytes++] = actual->c;			//es decir, si la raíz también es la única hoja del árbol.
		actual = arbol_huffman;
	}
	for(i = 0; i < longitud; i++){				//Iteramos sobre el mensaje codificado
		if(i < longitud - 1)
			bits_a_leer = 8;					//Si no estamos en la última iteración, leemos los 8 bits completos del byte actual
		else
			bits_a_leer = bits % 8;				//Si estamos en la última iteración, solo leemos los bits que falten
		for(j = 0; j < bits_a_leer; j++){		//Iteramos sobre los bits del byte actual
			if(mensaje[i] & (128 >> j))			
				actual = actual->der;			//Si el bit está prendido, nos vamos por la derecha
			else
				actual = actual->izq;			//Si el bit está apagado, nos vamos por la izquierda
			if(IsLeaf(actual)){					//Si estamos en una hoja, almacenamos su caracter en el mensaje decodificado
				resultado[bytes++] = actual->c;	//Además, también incrementamos el contador de bytes
				actual = arbol_huffman;			//Nos regresamos a la raíz de nuevo
			}
		}
	}
	return bytes;
}

/*
DESCRIPCIÓN: dada una posición de un árbol y un archivo abierto, esta función
guarda de forma recursiva todo el subárbol que comienza en "actual" en su
representación preorden. Cada que encuentra un nodo nulo, imprime un "#", si
encuentra una hoja con un caracter, lo imprime en su representación decimal; todo
esto separado por espacios.
RECIBE: nodo * actual, FILE * archivo
*/
void preorden_serializar(nodo * actual, FILE * archivo){
	if(actual == NULL){
		fprintf(archivo, "# ");
	}else{
		fprintf(archivo, "%hhu ", actual->c);
		preorden_serializar(actual->izq, archivo);
		preorden_serializar(actual->der, archivo);
	}
	return;
}

/*
DESCRIPCIÓN: dado un nombre de archivo, un arbol binario de huffman, el número de bits de un
mensaje codificado y el número de bytes del ese mensaje sin codificar; esta función guarda
en el archivo especificado: el número de bits, el número de bytes y la representación del
árbol comenzando por su raíz.
*/
void serializar_arbol(Char * archivo_info, nodo * arbol_huffman, ull bits, ull bytes){
	FILE * archivo = fopen(archivo_info, "wb");
	fprintf(archivo, "%lld %lld ", bits, bytes);
	preorden_serializar(arbol_huffman, archivo);
	fclose(archivo);
	return;
}

/*
DESCRIPCIÓN: dado un apuntador a una posición de un árbol y un archivo abierto, esta función recupera
el contenido del subárbol y lo va guardando en "actual", asumiendo que los nodos nulos
se representan con "#", que los caracteres están en su forma decimal y que está codificado
en preorden.
RECIBE: nodo ** actual, FILE * archivo
*/
void preorden_reconstruir(nodo ** actual, FILE * archivo){
	Char tmp[4];
	Char c;
	if(fscanf(archivo, "%s", tmp) != EOF && tmp[0] != '#'){
		sscanf(tmp, "%hhu", &c);
		*actual = NewNode(c);
		preorden_reconstruir(&((*actual)->izq), archivo);
		preorden_reconstruir(&((*actual)->der), archivo);
	}
	return;
}

/*
DESCRIPCIÓN: dado un nombre de archivo, un doble apuntador a un arbol binario de huffman, un apuntador a un
número de bits y un apuntador a un tamaño; esta función reconstruye el árbol codificado en el
archivo especificado y lo guarda en "arbol_huffman". También recupera el número bits del mensaje codificado
y el número de su tamaño original en bytes, ya que estos también se guardan en el archivo.
RECIBE: Char * archivo_info, nodo ** arbol_huffman, ull * bits, ull * tamano
*/
void reconstruir_arbol(Char * archivo_info, nodo ** arbol_huffman, ull * bits, ull * tamano){
	FILE * archivo = fopen(archivo_info, "rb");
	fscanf(archivo, "%lld %lld", bits, tamano);
	preorden_reconstruir(arbol_huffman, archivo);
	fclose(archivo);
	return;
}

/*
DESCRIPCIÓN: Dado un nombre de archivo, esta función ejecuta el algoritmo de Huffman
sobre los bytes del archivo. Se crean dos archivos nuevos: el primero contiene el archivo codificado,
y el segundo contiene el árbol binario generado.
RECIBE: Char * nombre
DEVUELVE: El tamaño en BITS del archivo codificado.
*/
ull codificar_archivo(Char * nombre){
	//Declaramos variables iniciales
	ull tamano, bits;
	Char * buffer, * codificado;
	nodo * arbol_huffman;
	Char nuevo_nombre[300], nombre_info[300];
	
	//Abrimos el archivo original en modo binario y leemos su tamaño en bytes
	FILE * archivo = fopen(nombre, "rb");
	fseek(archivo, 0, SEEK_END);
	tamano = ftell(archivo);
	rewind(archivo);

	buffer = malloc(sizeof(Char) * tamano);			//Reservamos memoria para el arreglo de Char en donde guardaremos el archivo
	codificado = malloc(sizeof(Char) * tamano);		//Reservamos memoria para el archivo codificado, que será a lo más el tamaño del original
	fread(buffer, sizeof(Char), tamano, archivo);	//Guardamos en memoria el archivo original

	//Codificamos el archivo original
	bits = codificar(buffer, &arbol_huffman, codificado, tamano);

	//Cerramos el archivo y liberamos memoria
	fclose(archivo);
	free(buffer);

	//Guardamos la codificación del archivo en uno nuevo, agregándole ".huff" al final
	sprintf(nuevo_nombre, "%s.huff", nombre);
	archivo = fopen(nuevo_nombre, "wb");
	fwrite(codificado, sizeof(Char), techo(bits, 8), archivo);

	//Cerramos el archivo y liberamos memoria
	fclose(archivo);
	free(codificado);

	//Por último, guardamos el árbol binario generado en un tercer archivo, agregándole ".info" al final
	sprintf(nombre_info, "%s.info", nombre);
	serializar_arbol(nombre_info, arbol_huffman, bits, tamano);

	return bits;
}

/*
DESCRIPCIÓN: dado un nombre de archivo codificado, un nombre de archivo para el archivo decodificado,
un árbol binario de Huffman, el tamaño en bits del archivo codificado y el tamaño el bytes del archivo
sin codificar; esta función decodifica el contenido del archivo codificado, con base en el árbol que recibe.
RECIBE: Char * nombre, Char * nuevo_nombre, nodo * arbol_huffman, ull bits, ull bytes
*/
void decodificar_archivo(Char * nombre, Char * nuevo_nombre, nodo * arbol_huffman, ull bits, ull bytes){
	//Declaramos variables iniciales
	ull tamano;
	Char * buffer, * decodificado;

	//Abrimos el archivo codificado en modo binario y obtenemos su tamaño en bytes
	FILE * archivo = fopen(nombre, "rb");
	fseek(archivo, 0, SEEK_END);
	tamano = ftell(archivo);
	rewind(archivo);

	//Reservamos memoria para el archivo codificado y lo guardamos ahí
	buffer = malloc(sizeof(Char) * tamano);
	fread(buffer, sizeof(Char), tamano, archivo);

	//Reservamos memoria para el archivo decodificado, y lo decodificamos ahí
	decodificado = malloc(sizeof(Char) * bytes);
	decodificar(buffer, arbol_huffman, decodificado, bits);

	//Cerramos el archivo y liberamos memoria
	fclose(archivo);
	free(buffer);

	//Creamos un nuevo archivo, en donde guardaremos el contenido del archivo decodificado
	archivo = fopen(nuevo_nombre, "wb");
	fwrite(decodificado, sizeof(Char), bytes, archivo);

	//Cerramos el archivo y liberamos memoria
	fclose(archivo);
	free(decodificado);
}

/*
DESCRIPCIÓN: esta función permite leer de la entrada estándar una cadena con espacios.
RECIBE: Char * cadena, int lim
*/
void strscan(Char * cadena, int lim){
	fflush(stdout);
	fgets(cadena, lim, stdin);
	size_t tamano = strlen(cadena) - 1;
	if(cadena[tamano] == '\n')
		cadena[tamano] = '\0';
}

//PROGRAMA PRINCIPAL
int main(){
	//Declaración de variables iniciales
	Char opcion[10];
	ull bits, bytes;
	Char nombre[300], nombre_info[300], nuevo_nombre[300];
	nodo * arbol_huffman = NULL;

	do{
		//Mostramos el menú
		printf("Escoge una opcion:\n");
		printf("1. Codificar un archivo\n");
		printf("2. Decodificar un archivo\n");
		printf("3. Salir\n");

		//Leemos la opción
		strscan(opcion, 10);
		switch(opcion[0]){
			case '1':{
				//Leemos el nombre de archivo a codificar
				printf("\nIntroduce el nombre del archivo a codificar: ");
				strscan(nombre, 300);

				//Codificamos el archivo y mostramos a cuánto se comprimió
				bits = codificar_archivo(nombre);

				printf("El archivo se comprimio a %lld bytes (%lld bits).\n\n", techo(bits, 8), bits);
				break;
			}
			case '2':{
				//Leemos el nombre de archivo a decodificar, el nombre del que contiene el árbol y el nuevo nombre para el archivo decodificado
				printf("\nIntroduce el nombre del archivo a decodificar: ");
				strscan(nombre, 300);
				printf("\nIntroduce el nombre del archivo de informacion: ");
				strscan(nombre_info, 300);
				printf("\nIntroduce el nuevo nombre del archivo decodificado: ");
				strscan(nuevo_nombre, 300);

				//Reconstruimos el árbol, y almacenamos el árbol, el número de bits del archivo codificado y el número de bytes del original
				reconstruir_arbol(nombre_info, &arbol_huffman, &bits, &bytes);

				//Decodificamos el archivo y mostramos un mensaje
				decodificar_archivo(nombre, nuevo_nombre, arbol_huffman, bits, bytes);

				printf("Se decodifico correctamente el archivo.\n\n");
				break;
			}
		}
	}while(opcion[0] != '3');
	return 0; //FIN
}