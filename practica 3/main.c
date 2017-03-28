/* Hashing dictionary with linked lists by Angel Lopez Manriquez */

/* Algunas implementaciones que dan valor agregado a la califiacion son:

	-El usuario puede exportar en determinado momento la lista de palabras de un archivo.
	-Se puede buscar todas las palabras que empiecen con:
		-Una letra.
		-Una frase.
		-Que contengan una subcadena.
	-Exportar una definicion de un archivo.
	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lisdob.h"

#define TRUE 1;
#define FALSE 0;

typedef char boolean;

/* This boolean controls FILE charges once */
boolean once = TRUE;

int hash (char *key){ return key[0] - 'A'; }

void
strscan (char *s, int lim){
	int i = 0;
	int c = '0';

	while (i < lim && (c = getchar ()) != '\n'){
		*(s + i) = c;
		i++;
	}

	*(s + i) = '\0';
}

void
insertarPalabra (Lista *t, char *nombre, char *def){
	insertarUltimo (&t[hash (nombre)], nombre, def);
}

void
cargar (Lista *t){
	if (once){
		FILE *fp = fopen ("dicc.txt", "r");
		int c = 'n'; /* This must be an int data type, due to EOF = -1 and 0 <= c <= 254 ? */
		char *nombre;
		char *def;
		int i = 0;

		while ((c = fgetc (fp)) != EOF){
			nombre = (char *) calloc (50, sizeof (char));
			def = (char *) calloc (100, sizeof (char));

			i = 0;
			nombre[i++] = c;

			while ((c = fgetc (fp)) != ':' && i < 50)
				nombre[i++] = c;

			c = fgetc (fp);

			i = 0;
			while ((c = fgetc (fp)) != '\n' && i < 100)
				def[i++] = c;

			insertarPalabra (t, nombre, def);

			free (nombre);
			free (def);
		}

		fclose (fp);
		once = 0;
	}
}

void
printAvailable (Lista *l){
	boolean b = 0;
	int i = 0;

	for (i = 0; i < 26; i++)
		if (l[i].cabeza){
			b = 1;
			break;
		}

	if (b){
		int i = 0, j = 0;
		Nodo *ptr = NULL;

		for (i = 0; i < 26; i++){
			ptr = l[i].cabeza;

			while (ptr){
				printf ("%s ", ptr->nombre);
				ptr = ptr->siguiente;
			}
			printf ("\n");
		}
	}
	else{
		puts ("No se ha cargado ningun archivo");
	}
}

void
printSpecific (Lista *t){
	char comp[99];
	int indice = 0, i = 0;
	Nodo *ptr = NULL;

	printf ("Escriba la palabra a buscar: ");
	strscan (comp, 99);

	if (isalpha (comp[0])){
		if (islower (comp[0]))
			comp[0] = toupper (comp[0]);
	}
	else {
		puts ("Error al escribir la palabra");
		return;
	}

	indice = hash (comp);
	ptr = t[indice].cabeza;

	while (ptr){
		if (!strcmp (comp, ptr->nombre)){
			printf ("%s: %s \n", ptr->nombre, ptr->definicion);
			return;
		}
		ptr = ptr->siguiente;
	}

	printf ("La palabra \"%s\" no se encuentra en el diccionario. \n", comp);
}

void
imprimirConsonante (Lista *t){

	char ans[3];
	int i = 0;

	printf ("Letra: ");
	fgets (ans, 3, stdin);

	if (isalpha (ans[0]))
		ans[0] = toupper (ans[0]);
	else {
		puts ("Caracter escrito erroneamente. ");
 		return;
	}
	i = hash (ans);

	if (t[i].cabeza){
		Nodo *ptr = t[i].cabeza;

		while (ptr){
			printf ("%s \n", ptr->nombre);
			ptr = ptr->siguiente;
		}
	}
	else
		puts ("No se encuentra ninguna palabra con esa letra");
}

void
agregarPalabra (Lista *l){
	char *nombre = (char *) calloc (50, sizeof (char));
	char *definicion = (char *) calloc (100, sizeof (char));
	char *parrafo = (char *) calloc (150, sizeof (char));
	FILE *fp = fopen ("dicc.txt", "a+");

	printf ("Palabra nueva: ");
	strscan (nombre, 50);

	printf ("Definicion: ");
	strscan (definicion, 100);

	sprintf (parrafo,"%s: %s", nombre, definicion);
	fprintf (fp, "%s \n", parrafo);
	insertarPalabra (l, nombre, definicion);

	free (nombre);
	free (definicion);
	free (parrafo);
	fclose (fp);
}

boolean
existWord (Lista *t, char s[]){
	int indice = 0;

	if (isalpha (s[0]))
		s[0] = toupper (s[0]);
	else
		return FALSE;

	indice = hash (s);
	Nodo *ptr = t[indice].cabeza;

	while (ptr){
		if (!strncmp (s, ptr->nombre, 50))
			return TRUE;
		ptr = ptr->siguiente;
	}

	return FALSE;
}

void
deleteWord (Lista *t){
	char pbuscada[50];

	printf ("\ningrese la palabra a borrar: ");
	strscan (pbuscada, 50);

	cargar (t);
	if (existWord (t, pbuscada)){
		FILE *fp = fopen ("dicc.txt", "w");
		Nodo *ptr = NULL;
		int i = 0;
		for (i = 0; i < 26; i++){
			ptr = t[i].cabeza;
			while (ptr){
				if (strncmp (ptr->nombre, pbuscada, 50))
					fprintf (fp, "%s: %s\n", ptr->nombre, ptr->definicion);
				ptr = ptr->siguiente;
			}
		}
		fclose (fp);
	}
	else
		puts ("No se encuentra la palabra ingresada.");
}

void
changeDefinition (Lista *t){
	char nuevaDef[100], pBuscada[50];
	int i = 0;

	printf ("\nIngrese la palabra a cambiar: ");
	strscan (pBuscada, 50);

	if (existWord (t, pBuscada)){
		FILE *fp = fopen ("dicc.txt", "w");
		Nodo *ptr = NULL;
		printf ("Nueva definicion: ");
		strscan (nuevaDef, 100);

		for (i = 0; i < 26; i++){
			ptr = t[i].cabeza;
			while (ptr){
				if (!strncmp (pBuscada, ptr->nombre, 50))
					fprintf (fp, "%s: %s \n", pBuscada, nuevaDef);
				else
					fprintf (fp, "%s: %s \n", ptr->nombre, ptr->definicion);
				ptr = ptr->siguiente;
			}
		}

		fclose (fp);
	}
	else
		printf ("La palabra \"%s\" no se encuentra", pBuscada);
}

void
menu (Lista *dicc){
	char opcion[3];

	while (1){
		puts ("\nDiccionario Hash");
		puts ("1.- Cargar archivo y sus definiciones ");
		puts ("2.- Agregar una palabra y su definicion");
		puts ("3.- Modificar una palabra");
		puts ("4.- Eliminar una palabra");
		puts ("5.- Salir");
		puts ("6.- Imprimir palabras disponibles ");
		puts ("7.- Imprimir palabras disponibles con base a su primer letra");
		puts ("8.- Mostrar la definicion dada una palabra");

		printf ("\nOpcion: ");
		fgets (opcion, 3, stdin);

		switch (opcion[0]){
			case '1': cargar (dicc); break;
			case '2': agregarPalabra (dicc); break;
			case '3': changeDefinition (dicc); break;
			case '4': deleteWord (dicc); break;
			case '5': puts ("Hasta luego \n"); return; break;
			case '6': printAvailable(dicc); break;
			case '7': imprimirConsonante (dicc); break;
			case '8': printSpecific (dicc); break;
			default: puts ("Opcion no valida"); break;
		}
	}
}

int
main (void){
	Lista *dicc = (Lista *) calloc (sizeof (Lista), 26);

	menu (dicc);

	formatearLista (dicc);
	return 0;
}
