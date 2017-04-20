#include "ArbolBin/ArbolBin.h"
#include "ColaPrioridad/ColaPrioridad.h"
#include <stdio.h>

typedef unsigned char Char;
typedef unsigned long long int ull;

typedef struct{
	Char c;
	Char * codificacion;
	int tamano;
} InfoCaracter;

void PrenderBit(Char * datos, int posicion){
	int i = posicion >> 3;
	int j = posicion % 8;
	datos[i] = datos[i] | (128 >> j);
	return;
}

void ApagarBit(Char * datos, int posicion){
	int i = posicion >> 3;
	int j = posicion % 8;
	datos[i] = datos[i] & ~(128 >> j);
	return;
}

int techo(int num, int den){
	if(num % den == 0)
		return num / den;
	else
		return num / den + 1;
}

void obtener_frecuencias(Char * mensaje, int * frecuencias, int longitud){
	int i;
	for(i = 0; i < 256; i++)
		frecuencias[i] = 0;
	for(i = 0; i < longitud; i++)
		frecuencias[mensaje[i]]++;
	return;
}

void copiar(Char c, int * camino, int tamano, InfoCaracter * info){
	int i;
	info[c].c = c;
	info[c].tamano = tamano;
	info[c].codificacion = malloc(tamano * sizeof(Char));
	for(i = 0; i < tamano; i++)
		info[c].codificacion[i] = camino[i];
	return;
}

void obtener_codificaciones(arbol_bin *A, posicion p, int * camino, int pos, InfoCaracter * info){
	int i;
	Char c;
	if(p != NULL){
		camino[pos] = 0;
		obtener_codificaciones(A, LeftSon(A, p), camino, pos + 1, info);
		if(IsLeaf(A, p)){
			c = ReadNode(A, p).c;
			copiar(c, camino, pos, info);
		}
		camino[pos] = 1;
		obtener_codificaciones(A, RightSon(A, p), camino, pos + 1, info);
	}
	return;
}

int codificar(Char * mensaje, arbol_bin ** arbol_huffman, Char * resultado, int longitud){
	int frecuencias[256];
	int camino[100];
	InfoCaracter codificaciones[256];
	int i, j, bits = 0;
	ColaPrioridad C;
	dato primero, segundo;
	arbol_bin * A;
	posicion p;
	elemento e;
	Char actual;

	InitializeQueue(&C);
	obtener_frecuencias(mensaje, frecuencias, longitud);
	for(i = 0; i < 256; i++){
		if(frecuencias[i] > 0){
			A = malloc(sizeof(arbol_bin));
			Initialize(A);
			e.c = i;
			NewLeftSon(A, p, e);
			push(&C, frecuencias[i], A);
		}
	}

	while(C.tamano >= 2){
		primero = pop(&C);
		segundo = pop(&C);
		push(&C, primero.prioridad + segundo.prioridad, MergeTrees(primero.A, segundo.A));
	}

	A = pop(&C).A;
	*arbol_huffman = A;
	obtener_codificaciones(A, Root(A), camino, 0, codificaciones);

	for(i = 0; i < longitud; i++){
		actual = mensaje[i];
		for(j = 0; j < codificaciones[actual].tamano; j++){
			if(codificaciones[actual].codificacion[j] == 0)
				ApagarBit(resultado, bits++);
			else if(codificaciones[actual].codificacion[j] == 1)
				PrenderBit(resultado, bits++);
		}
	}

	return bits;
}

int decodificar(Char * mensaje, arbol_bin * arbol_huffman, Char * resultado, int bits){
	int i, j, bytes = 0, bits_a_leer, longitud = techo(bits, 8);
	posicion actual = Root(arbol_huffman);
	if(IsLeaf(arbol_huffman, actual)){
		resultado[bytes++] = ReadNode(arbol_huffman, actual).c;
		actual = Root(arbol_huffman);
	}
	for(i = 0; i < longitud; i++){
		if(i < longitud - 1)
			bits_a_leer = 8;
		else
			bits_a_leer = bits % 8;
		for(j = 0; j < bits_a_leer; j++){
			if(mensaje[i] & (128 >> j))
				actual = RightSon(arbol_huffman, actual);
			else
				actual = LeftSon(arbol_huffman, actual);
			if(IsLeaf(arbol_huffman, actual)){
				resultado[bytes++] = ReadNode(arbol_huffman, actual).c;
				actual = Root(arbol_huffman);
			}
		}
	}
	return bytes;
}

int codificar_archivo(char * nombre){
	int tamano, bits;
	Char * buffer, * codificado, * decodificado;
	arbol_bin * arbol_huffman;
	Char nuevo_nombre[300];
	
	FILE * archivo = fopen(nombre, "rb");
	fseek(archivo, 0, SEEK_END);
	tamano = ftell(archivo);
	rewind(archivo);

	buffer = malloc(sizeof(Char) * tamano);
	codificado = malloc(sizeof(Char) * tamano * 100);
	fread(buffer, sizeof(Char), tamano, archivo);

	bits = codificar(buffer, &arbol_huffman, codificado, tamano);

	fclose(archivo);
	free(buffer);

	sprintf(nuevo_nombre, "%s.huffman", nombre);
	archivo = fopen(nuevo_nombre, "wb");
	fwrite(codificado, sizeof(Char), techo(bits, 8), archivo);

	fclose(archivo);
	free(codificado);

	return bits;
}

int decodificar_archivo(char * nombre, char * nuevo_nombre, arbol_bin * arbol_huffman, int bits){
	int tamano, bytes;
	Char * buffer, * decodificado;

	FILE * archivo = fopen(nombre, "rb");
	fseek(archivo, 0, SEEK_END);
	tamano = ftell(archivo);
	rewind(archivo);

	buffer = malloc(sizeof(Char) * tamano);
	fread(buffer, sizeof(Char), tamano, archivo);

	bytes = decodificar(buffer, arbol_huffman, decodificado, bits);
	decodificado = malloc(sizeof(Char) * bytes);

	fclose(archivo);
	free(buffer);

	archivo = fopen(nuevo_nombre, "wb");
	fwrite(decodificado, sizeof(Char), bytes, archivo);

	fclose(archivo);
	free(decodificado);

	return bytes;
}

int reconstruir_arbol(arbol_bin ** arbol_huffman, char * archivo_info){
	return;
}

int main(){
	int opcion;
	int bits, bytes;
	Char nombre[300], nombre_info[300], nuevo_nombre[300];
	arbol_bin * arbol_huffman;

	do{
		printf("Escoge una opcion:\n");
		printf("1. Codificar un archivo\n");
		printf("2. Decodificar un archivo\n");
		printf("3. Salir\n");
		scanf("%d", &opcion);
		switch(opcion){
			case 1:{
				printf("\nIntroduce el nombre del archivo a codificar: ");
				scanf("%s", nombre);

				bits = codificar_archivo(nombre);

				printf("El archivo se comprimio a %d bytes (%d bits).\n\n", techo(bits, 8), bits);
				break;
			}
			case 2:{
				printf("\nIntroduce el nombre del archivo a decodificar: ");
				scanf("%s", nombre);
				printf("\nIntroduce el nombre del archivo de informacion: ");
				scanf("%s", nombre_info);
				printf("\nIntroduce el nuevo nombre del archivo decodificado: ");
				scanf("%s", nuevo_nombre);

				bits = reconstruir_arbol(&arbol_huffman, nombre_info);

				bytes = decodificar_archivo(nombre, nuevo_nombre, arbol_huffman, bits);
				break;
			}
		}
	}while(opcion != 3);
	return 0;
}