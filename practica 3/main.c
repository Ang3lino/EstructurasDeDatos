/* Diccionario usando tablas hash.

   Autor (es):  Angel Lopez Manriquez 
   compilacion: gcc main.c lisdob.c	*/

/* 	Algunas implementaciones que dan valor agregado a la califiacion son:
		-El usuario puede exportar en determinado momento la lista de palabras de un archivo.	OK	funcion exportList
    Se puede buscar todas las palabras que empiecen con:
		-Una letra.		OK	funcion: searchLetter 
		-Una frase.		OK	funcion: searchSentece
		-Que contengan una subcadena.	OK	funcion: searchSubstring
		-Exportar una definicion de un archivo.	OK funcion: exportDefinition

	Puesto que vamos a trabajar con archivos, es importante que el archivo tenga el formato
	
	Palabra1: definicion1 \n
	Palabra2: definicion2 \n
	.
	.
	.
	PalabraN: defincionN \n
	
	para que la funcion loadFile () funcione apropiadamente.	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lisdob.h"

#define TRUE 1
#define FALSE 0

#define TAMHASH 26

char nombreArchivo[50];

typedef char boolean;

/*	funcion hash en la que, como argumento recibiremos un puntero char, solo es 
	relevante key[0] y, con base a key[0] retornaremos un digito en donde se corresponde
	como se muestra a continuacion: 
	A: 0, B: 1, ..., Z: 26.

	El programa esta diseniado de tal forma que los caracteres de key[0] sean tales que:

	A <= key[0] <= Z	notese que las letras son mayusculas
	
	A pesar de su simpleza es muy, pero muy util, que la funcion hash reciba a un 
	caracter alfanumerico en mayusculas es muy importante, de no serlo, ocasionamos
    un SIGSEGV.	*/ 
int hash (char *key){ return key[0] - 'A'; }

/*	Funcion muy parecida a fgets (x, y, z), solo que al final del string s, 
	a diferencia de fgets (), ponemos el caracter nulo. Otra distincion 
	es que solo se puede guardar el string el usuario, con el teclado.

	Notese que fgets () tiene 3 parametros, aqui dos, digamos que por defecto tiene el 
	modo stdin si la comparamos con fgets () en el tercer parametro.	*/
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

/*	Funcion que muestra las colisiones en la tabla hash.	
	la variable l sirve para dar un salto de linea cada 2 veces que se muestren las
	colisiones de una palabra.	*/
void 
showCollisions (Lista *t){
	int i, j, l = 0;
	char k = 'A';
	Nodo *ptr;

	for (i = 0; i < TAMHASH; i++){
		ptr = t[i].cabeza;
		j = 0;
		while (ptr){
			j++;
			ptr = ptr->siguiente;
		}
		printf ("Se encontraron %d colisiones en %c.", j, k);
		k++;
		l++;
		if (l % 2 == 0){
			printf ("\n");
			l = 0;
		} else
			printf ("\t");
	}

	printf ("\n");
}

/*	Funcion que carga el archivo y va llenando la tabla hash con base al mismo.	*/
void
loadFile (Lista *t){
	int c = 'n'; 
	char *nombre;
	char *def;
	int i = 0;

	formatearLista (t);

	/*	IMPORTANTISIMO que el archivo tenga el formato descrito hasta arriba.	*/
	printf ("Nombre del archivo (.txt): ");
	strscan (nombreArchivo, 40);
	sprintf (nombreArchivo, "%s.txt", nombreArchivo);
	FILE *fp = fopen (nombreArchivo, "r");
	

	/*	Recorremos el archivo con un bucle while, mientras que c no sea EOF 
		(es decir, no lleguemos al final del archivo) vamos recorriendo el 
		archivo, caracter a caracter y vamos guardando en un string su nombre 
		y definicion por separado.	*/
	while (!feof (fp)){
		nombre = (char *) calloc (TAMNOM, sizeof (char));
		def = (char *) calloc (TAMDEF, sizeof (char));

		i = 0;

		/*	Puesto que el archivo tiene el formato:
			Palabra: definicio. \n
			se sabe que la palabra abarca desde su primera letra hasta los dos puntos.	*/ 
		while (i < TAMNOM && (c = fgetc (fp)) != ':' && c != '\n' && c != EOF)
			nombre[i++] = c;

		if(i > 0){
			nombre[i++] = '\0';

			c = fgetc (fp);

			/*	De manera similar, la definicion abarca desde su primera letra hasta el salto
				de linea.	*/
			i = 0;
			while (i < TAMDEF && (c = fgetc (fp)) != '\n' && c != EOF)
				def[i++] = c;

			def[i++] = '\0';

			/*	Insertamos la palabra a la tabla hash.	*/
			insertarUltimo (&t[hash (nombre)], nombre, def);
		}
	}
	fclose (fp);
}

/*	Funcion que imprime todas las palabras del archivo.	*/
void
printAvailable (Lista *l){
	boolean b = 0;
	int i = 0;

	/*	Nos aseguramos que exista una palabra, como minimo.	*/
	for (i = 0; i < TAMHASH; i++)
		if (l[i].cabeza){
			b = 1;
			break;
		}

	if (b){
		int i = 0, j = 0, tab = 0;
		char c = 'A';
		Nodo *ptr = NULL;

		for (i = 0; i < TAMHASH; i++){
			ptr = l[i].cabeza;

			printf ("\t ========== %c ========== \n\n", c);
			/*	Imprimimos la palabra, si existe almenos una palabra 
				con un caracter en la fila i, se entra al bucle, si no
				no entra, asi nos aseguramos de evadir el error SIGSEGV.	*/ 
			tab = 0;
			while (ptr){
				printf ("%s \t", ptr->nombre);
				ptr = ptr->siguiente;
				tab++;
				if (tab % 4 == 0){
					printf ("\n");
					tab = 0;
				}
			}
			printf ("\n \n");
			c++;
		}
	}
	else{
		puts ("No se ha cargado ningun archivo");
	}
}

/*	Funcion que imprime una palabra solicitada, si existe.	*/
void
printSpecific (Lista *t){
	char comp[99];
	int indice = 0, i = 0;
	Nodo *ptr = NULL;

	printf ("Escriba la palabra a buscar: ");
	strscan (comp, 99);

	/*	Nos aseguramos que sea que el caracter sea alfanumerico, de 
		ser el caso forzamos que el caracter sea mayuscula.	En caso 
		contrario no procedemos a buscar, no tiene sentido.	*/  
	if (isalpha (comp[0])){
		if (islower (comp[0]))
			comp[0] = toupper (comp[0]);
	}
	else {
		puts ("Error al escribir la palabra");
		return;
	}

	/*	Obtenemos el indice correspondiente a la palabra.	*/
	indice = hash (comp);
	ptr = t[indice].cabeza;

	/*	Procedemos a buscar la palabra, si existe se imprimira la palabra
		con su correspondiente definicion, si no existe se muestra por 
		pantalla que no existe la palabra buscada.	*/
	while (ptr){
		if (!strcmp (comp, ptr->nombre)){
			printf ("%s: %s \n", ptr->nombre, ptr->definicion);
			return;
		}
		ptr = ptr->siguiente;
	}

	printf ("La palabra \"%s\" no se encuentra en el diccionario. \n", comp);
}

/*	Funcion que imprime todas las palabras disponibles con la consonante propuesta.	*/
void
searchLetter (Lista *t){
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

/*	Agregamos una palabra, tanto a el archivo como a la lista.	*/
void
addWord (Lista *l){
	char *nombre = (char *) calloc (TAMNOM, sizeof (char));
	char *definicion = (char *) calloc (TAMDEF, sizeof (char));
	char *parrafo = (char *) calloc (TAMNOM + TAMDEF + 10, sizeof (char));
	FILE *fp = fopen (nombreArchivo, "a+");

	printf ("Palabra nueva: ");
	strscan (nombre, TAMNOM);

	printf ("Definicion: ");
	strscan (definicion, TAMDEF);

	sprintf (parrafo,"%s: %s", nombre, definicion);
	/*	Escribimos nuestra palabra al final de nuestro archivo, si daniar la palabra 
		anterior.	*/
	fprintf (fp, "%s\n", parrafo);
	insertarUltimo (&l[hash (nombre)], nombre, definicion);

	free (nombre);
	free (definicion);
	free (parrafo);
	fclose (fp);
}

/*	Funcion que recibe la lista * y un string s, en la funcion solo nos importa la primera letra 
	del string. Como extra cambia el caracter s[0] a mayuscula, en case de que sea alfanumerico
	este caracter, obviamente.	*/
boolean
existWord (Lista *t, char s[]){
	int indice = 0;

	/*	Comprobamos que el caracter sea alfanumerico.	*/
	if (isalpha (s[0]))
		s[0] = toupper (s[0]);
	else
		return FALSE;

	/*	Obtenemos el indice de s[0]. Se sabe que existe un valor correspondiente puesto que ya paso
		la condicion anterior.	*/
	indice = hash (s);
	Nodo *ptr = t[indice].cabeza;

	/*	Buscamos en nuestra fila i-esima de nuestra tabla, si existe, retornamos TRUE	*/
	while (ptr){
		if (!strncmp (s, ptr->nombre, TAMNOM))
			return TRUE;
		ptr = ptr->siguiente;
	}

	return FALSE;
}

void
deleteWord (Lista *t){
	char pbuscada[TAMNOM];

	printf ("\ningrese la palabra a borrar: ");
	strscan (pbuscada, TAMNOM);
	
	/*	Comprobamos que exista la palabra y, si existe, procedemos borramos y 
		escribimos el archivo, saltandonos la palabra no deseada.	*/
	if (existWord (t, pbuscada)){
		FILE *fp = fopen (nombreArchivo, "w");
		Nodo *ptr = NULL;
		int i = 0;
		for (i = 0; i < TAMHASH; i++){
			ptr = t[i].cabeza;
			while (ptr){
				if (strncmp (ptr->nombre, pbuscada, TAMNOM))
					fprintf (fp, "%s: %s\n", ptr->nombre, ptr->definicion);
				ptr = ptr->siguiente;
			}
		}
		fclose (fp);
	}
	else
		puts ("No se encuentra la palabra ingresada.");
}

/*	Funcion que cambia la definicion de una palabra.	*/
void
changeDefinition (Lista *t){
	char nuevaDef[TAMDEF], pBuscada[TAMNOM];
	int i = 0;

	printf ("\nIngrese la palabra a cambiar: ");
	strscan (pBuscada, TAMNOM);

	/*	Comprobamos si existe la palabra	*/
	if (existWord (t, pBuscada)){
		FILE *fp = fopen (nombreArchivo, "w");
		Nodo *ptr = NULL;
		/*	Obtenemos la nueva definicion.	*/
		printf ("Nueva definicion: ");
		strscan (nuevaDef, TAMDEF);

		/*	Recorremos las 26 palabras y reescribimos todo el archivo, cuando nos 
			encontremos con la palabra a cambiar, escribimos la nueva palabra y nos
			saltamos la sobreescritura de la palabra anterior, asi como su definicion.*/
		for (i = 0; i < TAMHASH; i++){
			ptr = t[i].cabeza;
			while (ptr){
				if (!strncmp (pBuscada, ptr->nombre, TAMNOM)){
					sprintf(ptr->definicion, "%s", nuevaDef);
					fprintf (fp, "%s: %s\n", pBuscada, nuevaDef);
				}
				else
					fprintf (fp, "%s: %s\n", ptr->nombre, ptr->definicion);
				ptr = ptr->siguiente;
			}
		}

		fclose (fp);
	}
	else
		printf ("La palabra \"%s\" no se encuentra", pBuscada);
}

void 
exportList (Lista *t){
	int i, j;
	Nodo *ptr = NULL;
	char nombre[50];

	printf ("\nNombre del archivo (.txt): ");
	strscan (nombre, 40);
	sprintf (nombre, "%s.txt", nombre);

	FILE *fp = fopen (nombre, "w");

	for (i = 0; i < TAMHASH; i++){
		ptr = t[i].cabeza;
		while (ptr){
			fprintf (fp, "%s: %s\n", ptr->nombre, ptr->definicion);
			ptr = ptr->siguiente;
		}
	}
	
	fclose (fp);
}

/*	Funcion que exporta una palabra con su definicion a un archivo de texto.
 *	Problema: Se guarda basura al final del archivo creado.		*/
void 
exportDefinition (Lista *t){
	char nombre[TAMNOM];

	printf ("\nNombre de la palabra a exportar: ");
	strscan (nombre, TAMNOM);

	if (existWord (t, nombre)){
		char nombreArchivoNuevo[50];
		Nodo *ptr = t[hash (nombre)].cabeza;

		printf ("Nombre del archivo (.txt): ");
		strscan (nombreArchivoNuevo, 40);
		sprintf (nombreArchivoNuevo, "%s.txt", nombreArchivoNuevo);
		FILE *fp = fopen (nombreArchivoNuevo, "w");
		while (ptr){
			if (!strncmp (nombre, ptr->nombre, TAMNOM)){
				fprintf (fp, "%s: %s", ptr->nombre, ptr->definicion);
				puts ("Palabra exportada exitosamente :D. ");
				break;
			}
			ptr = ptr->siguiente;
		}
		fclose (fp);
	} else 
		printf ("la palabra %s no se encuentra en el diccionario. ", nombre);
}

/*	Funcion que busca todas las palabras disponibles, con su respectiva definicion
    que contengan una subcadena dada (si existe).	*/
void 
searchSubstring (Lista *t){
	char substr[TAMNOM];
	int i, n, N, hayUna = 0;
	Nodo *ptr = NULL;

	printf ("\nEscriba la subcadena: ");
	strscan (substr, TAMNOM);
	n = strlen (substr);

	/*	Con un bucle recorremos las 26 listas que como maximo puede tener la tabla.	*/
	for (i = 0; i < TAMHASH; i++){
		ptr = t[i].cabeza;
		while (ptr){
			N = strlen (ptr->nombre);
			if (n <= N)
				/*	La funcion char *strstr (char *A, char *B) retorna true si la subcadena B esta en A	*/ 
				if (strstr (ptr->nombre, substr)){
					printf ("%s: %s \n", ptr->nombre, ptr->definicion);
					hayUna = 1;
				}
			ptr = ptr->siguiente;
		}
	}	
	if (!hayUna)
		printf ("No se encuentra ninguna palabra con la subcadena %s. ", substr);			
}

/*	Funcion que, pregunta alguna frase y muestra las palabras disponibles en el diccionario 
	tales que su definicion contengan a la frase.	*/ 
void 
searchSentence (Lista *t){
	char frase[TAMNOM];
	Nodo *ptr;
	int i, j, noHay = 1;

	printf ("\nFrase: ");
	strscan (frase, TAMNOM);
	for (i = 0; i < TAMHASH; i++){
		ptr = t[i].cabeza;
		while (ptr){
			if (strstr (ptr->definicion, frase)){
				printf ("%s: %s \n", ptr->nombre, ptr->definicion);
				noHay = 0;
			}	
			ptr = ptr->siguiente;
		}
	}
	if (noHay)
		printf ("La frase \" %s \" no se encuentra en el diccionario.", frase);
}

/*	Funcion que muestra las opciones disponibles para el programa. 	*/
void
menu (Lista *dicc){
	char aux[9];
	int opcion;

	while (1){
		puts ("\nDiccionario Hash \n");

		puts ("0.-  Mostrar estadisticas \n");

		puts ("1.-  Cargar archivo y sus definiciones ");
		puts ("2.-  Agregar una palabra y su definicion");
		puts ("3.-  Mostrar la definicion de una palabra");
		puts ("4.-  Modificar una palabra");
		puts ("5.-  Eliminar una palabra");

		puts ("\nOpciones para puntos extra");
		
		puts ("\nOpciones de busqueda ");
		puts ("6.-  Buscar por subcadena ");
		puts ("7.-  Buscar palabras por su primer letra ");
		puts ("8.-  Buscar por una frase ");
	
		puts ("\nOpciones de exportacion ");
		puts ("9.-  Exportar lista a un archivo de texto ");
		puts ("10.- Exportar una palabra con su definicion a un archivo ");

		puts ("\nOpciones extra ");
		puts ("11.- Imprimir palabras disponibles ");

		puts ("\n12.- Salir");

		printf ("\nOpcion: ");
		fgets (aux, 9, stdin);
		sscanf (aux, "%d", &opcion);

		switch (opcion){
			case 0: showCollisions (dicc); break;
			case 1: loadFile (dicc); break;
			case 2: addWord (dicc); break;
			case 3: printSpecific (dicc); break;
			case 4: changeDefinition (dicc); break;
			case 5: deleteWord (dicc); break;
			case 6: searchSubstring (dicc); break;
			case 7: searchLetter (dicc); break;
			case 8: searchSentence (dicc);  break;
			case 9: exportList (dicc); break;
			case 10: exportDefinition (dicc); break;
			case 11: printAvailable (dicc); break;
			case 12: puts ("Hasta luego \n"); return; break;
			default: puts ("Opcion no valida"); break;
		}
	}
}

/*	Raiz del programa	*/
int 
main (int argc, char *argv[]){
	Lista *dicc = (Lista *) calloc (sizeof (Lista), TAMHASH);

	menu (dicc);

	formatearLista (dicc);
	return EXIT_SUCCESS;
}
