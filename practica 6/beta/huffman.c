#include "ArbolBin.h"
#include <stdio.h>
#include <string.h>

typedef unsigned long long int ull;

typedef struct{
	arbol_bin * A;
	int frecuencia;
} elemento;

typedef struct{
	Char c;
	Char * codificacion;
	ull tamano;
} InfoCaracter;

void PrenderBit(Char * datos, ull posicion){
	ull i = posicion >> 3;
	int j = posicion % 8;
	datos[i] = datos[i] | (128 >> j);
	return;
}

void ApagarBit(Char * datos, ull posicion){
	ull i = posicion >> 3;
	int j = posicion % 8;
	datos[i] = datos[i] & ~(128 >> j);
	return;
}

ull techo(ull num, ull den){
	if(num % den == 0)
		return num / den;
	else
		return num / den + 1;
}

void obtener_frecuencias(Char * mensaje, ull * frecuencias, ull longitud){
	ull i;
	for(i = 0; i < 256; i++)
		frecuencias[i] = 0;
	for(i = 0; i < longitud; i++)
		frecuencias[mensaje[i]]++;
	return;
}

void copiar(Char c, Char * camino, ull tamano, InfoCaracter * info){
	ull i;
	info[c].c = c;
	info[c].tamano = tamano;
	info[c].codificacion = malloc(tamano * sizeof(Char));
	for(i = 0; i < tamano; i++)
		info[c].codificacion[i] = camino[i];
	return;
}

void obtener_codificaciones(posicion p, Char * camino, ull pos, InfoCaracter * info){
	if(p != NULL){
		camino[pos] = 0;
		obtener_codificaciones(p->izq, camino, pos + 1, info);
		if(IsLeaf(p)){
			copiar(p->c, camino, pos, info);
		}
		camino[pos] = 1;
		obtener_codificaciones(p->der, camino, pos + 1, info);
	}
	return;
}

int comparador(const void * a, const void * b){
	return ((elemento*)b)->frecuencia - ((elemento*)a)->frecuencia;
}

ull codificar(Char * mensaje, arbol_bin ** arbol_huffman, Char * resultado, ull longitud){
	ull frecuencias[256];
	Char camino[256];
	InfoCaracter codificaciones[256];
	ull i, j, bits = 0;
	elemento arboles[256];
	int n_arboles = 0;
	elemento primero, segundo;
	arbol_bin * A;
	Char actual;

	obtener_frecuencias(mensaje, frecuencias, longitud);
	for(i = 0; i < 256; i++){
		if(frecuencias[i] > 0){
			A = NewArbolBin();
			A->raiz = NewNode(i);
			arboles[n_arboles].A = A;
			arboles[n_arboles].frecuencia = frecuencias[i];
			n_arboles++;
		}
	}

	qsort(arboles, n_arboles, sizeof(elemento), comparador);

	while(n_arboles >= 2){
		primero = arboles[n_arboles - 1];
		segundo = arboles[n_arboles - 2];
		arboles[n_arboles - 2].A = MergeTrees(primero.A, segundo.A);
		arboles[n_arboles - 2].frecuencia = primero.frecuencia + segundo.frecuencia;
		n_arboles--;
		qsort(arboles, n_arboles, sizeof(elemento), comparador);
	}

	A = arboles[0].A;
	*arbol_huffman = A;
	obtener_codificaciones(A->raiz, camino, 0, codificaciones);

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

ull decodificar(Char * mensaje, arbol_bin * arbol_huffman, Char * resultado, ull bits){
	ull i, j, bytes = 0, bits_a_leer, longitud = techo(bits, 8);
	posicion actual = arbol_huffman->raiz;
	if(IsLeaf(actual)){
		resultado[bytes++] = actual->c;
		actual = arbol_huffman->raiz;
	}
	for(i = 0; i < longitud; i++){
		if(i < longitud - 1)
			bits_a_leer = 8;
		else
			bits_a_leer = bits % 8;
		for(j = 0; j < bits_a_leer; j++){
			if(mensaje[i] & (128 >> j))
				actual = actual->der;
			else
				actual = actual->izq;
			if(IsLeaf(actual)){
				resultado[bytes++] = actual->c;
				actual = arbol_huffman->raiz;
			}
		}
	}
	return bytes;
}

void preorden_serializar(posicion actual, FILE * archivo){
	if(actual == NULL){
		fprintf(archivo, "# ");
	}else{
		fprintf(archivo, "%hhu ", actual->c);
		preorden_serializar(actual->izq, archivo);
		preorden_serializar(actual->der, archivo);
	}
	return;
}

void serializar_arbol(Char * archivo_info, arbol_bin * arbol_huffman, ull bits, ull bytes){
	FILE * archivo = fopen(archivo_info, "wb");

	fprintf(archivo, "%llu %llu ", bits, bytes);

	preorden_serializar(arbol_huffman->raiz, archivo);

	fclose(archivo);
	return;
}

void preorden_reconstruir(posicion * actual, FILE * archivo){
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

void reconstruir_arbol(Char * archivo_info, arbol_bin ** arbol_huffman, ull * bits, ull * tamano){
	FILE * archivo = fopen(archivo_info, "rb");

	fscanf(archivo, "%llu %llu", bits, tamano);

	*arbol_huffman = NewArbolBin();
	preorden_reconstruir(&((*arbol_huffman)->raiz), archivo);

	fclose(archivo);
	return;
}

ull codificar_archivo(Char * nombre){
	ull tamano, bits;
	Char * buffer, * codificado, * decodificado;
	arbol_bin * arbol_huffman;
	Char nuevo_nombre[300], nombre_info[300];
	
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

	sprintf(nuevo_nombre, "%s.huff", nombre);
	archivo = fopen(nuevo_nombre, "wb");
	fwrite(codificado, sizeof(Char), techo(bits, 8), archivo);

	fclose(archivo);
	free(codificado);

	sprintf(nombre_info, "%s.info", nombre);
	serializar_arbol(nombre_info, arbol_huffman, bits, tamano);

	return bits;
}

void decodificar_archivo(Char * nombre, Char * nuevo_nombre, arbol_bin * arbol_huffman, ull bits, ull bytes){
	ull tamano;
	Char * buffer, * decodificado;

	FILE * archivo = fopen(nombre, "rb");
	fseek(archivo, 0, SEEK_END);
	tamano = ftell(archivo);
	rewind(archivo);

	buffer = malloc(sizeof(Char) * tamano);
	fread(buffer, sizeof(Char), tamano, archivo);

	decodificado = malloc(sizeof(Char) * bytes);
	decodificar(buffer, arbol_huffman, decodificado, bits);

	fclose(archivo);
	free(buffer);

	archivo = fopen(nuevo_nombre, "wb");
	fwrite(decodificado, sizeof(Char), bytes, archivo);

	fclose(archivo);
	free(decodificado);
}

void strscan(Char * cadena, int lim){
	fflush(stdout);
	fgets(cadena, lim, stdin);
	size_t tamano = strlen(cadena) - 1;
	if(cadena[tamano] == '\n')
		cadena[tamano] = '\0';
}

int main(){
	Char opcion[300];
	ull bits, bytes;
	Char nombre[300], nombre_info[300], nuevo_nombre[300];
	arbol_bin * arbol_huffman;

	do{
		printf("Escoge una opcion:\n");
		printf("1. Codificar un archivo\n");
		printf("2. Decodificar un archivo\n");
		printf("3. Salir\n");
		strscan(opcion, 300);
		switch(opcion[0]){
			case '1':{
				printf("\nIntroduce el nombre del archivo a codificar: ");
				strscan(nombre, 300);

				bits = codificar_archivo(nombre);

				printf("El archivo se comprimio a %llu bytes (%llu bits).\n\n", techo(bits, 8), bits);
				break;
			}
			case '2':{
				printf("\nIntroduce el nombre del archivo a decodificar: ");
				strscan(nombre, 300);
				printf("\nIntroduce el nombre del archivo de informacion: ");
				strscan(nombre_info, 300);
				printf("\nIntroduce el nuevo nombre del archivo decodificado: ");
				strscan(nuevo_nombre, 300);

				reconstruir_arbol(nombre_info, &arbol_huffman, &bits, &bytes);

				decodificar_archivo(nombre, nuevo_nombre, arbol_huffman, bits, bytes);

				printf("Se decodifico correctamente el archivo.\n\n");
				break;
			}
		}
	}while(opcion[0] != '3');
	return 0;
}