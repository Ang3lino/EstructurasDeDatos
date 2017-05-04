/* Diccionario usando tablas hash.

   Equipo: Quick Coding
   compilacion: gcc main.c lisdob.c	*/

/* 	Algunas implementaciones que dan valor agregado a la califiacion son:
		-El usuario puede exportar en determinado momento la lista de palabras de un archivo.	OK	funcion exportList
    Se puede buscar todas las palabras que empiecen con:
		-Una letra.		OK	funcion: searchLetter 
		-Una frase.		OK	funcion: searchSentece
		-Que contengan una subcadena.	OK	funcion: searchSubstring
		-Exportar una definicion de un archivo.	OK funcion: exportDefinition

	Puesto que vamos a trabajar con archivos, es importante que el archivo tenga el formato
	
	palabra1: definicion1 \n
	palabra2: definicion2 \n
	.
	.
	.
	palabraN: defincionN \n
	
	para que la funcion loadFile () funcione apropiadamente.	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Lista.h"

char nombreArchivo[50];
bool archivoCargado = false;

/*	Funcion que obtiene el modulo de a % b positivo.	*/
int 
mod (int a, int b){
	int r = a % b;
	if(r < 0)
		r += b;
	return r;
}

/*	Funcion que obtiene el tamanio de un archivo, dado el nombre del archivo.	*/
int 
fileSize (char nombre[]){

	int tamano;
	FILE * archivo = fopen(nombre, "rb");
	if (!archivo){
		printf ("Error, el archivo %s no existe. \n", nombre);
		exit (1);
	}
	fseek(archivo, 0, SEEK_END);
	tamano = ftell(archivo);
	
	/*	rewind (fp) te regresa al principio del archivo.	*/
	fclose (archivo);

	return tamano;
}

/*	Funcion hash mejorada en la que, como argumento recibiremos un puntero a un arreglo
 *	de char, solo es relevante key[0] y, con base a key[0] retornaremos un digito en donde 
 *	se corresponde. Como se muestra a continuacion: 
	
		A: 0, B: 1, ..., Z: 26.

	El programa esta diseniado de tal forma que los caracteres de key[0] sean tales que:

		A <= key[0] <= Z	notese que las letras son mayusculas
	
	A pesar de su simpleza es muy, pero muy util. Que la funcion hash reciba a un 
	caracter alfanumerico en mayusculas la primera letra del arreglo favorece a la busqueda
	del programa.	*/ 

int hash (char *key){ return mod(key[0] - 'A', TAMHASH); }

/*
int 
hash (char *st){
	int i = 0, acum = 0;
	for (i = 0; i < strlen (st); i++)
		acum += st[i];
	return mod (acum, TAMHASH);
}
*/

/*	Funcion muy parecida a fgets (x, y, z), solo que al final del string s, 
	a diferencia de fgets (), ponemos el caracter nulo. Otra distincion 
	es que solo se puede guardar el string el usuario, con el teclado.

	Notese que fgets () tiene 3 parametros, aqui dos, digamos que por defecto tiene el 
	modo stdin si la comparamos con fgets () en el tercer parametro.	*/
void
strscan (char *s, int lim){
	int i = 0, c = '0';

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
showCollisions (lista *t){
	int i, j, l = 0;
	char k = 'A';
	nodo *ptr;

	for (i = 0; i < TAMHASH; i++){
		ptr = t[i].frente;
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

/*	Embutimos en un elemento e los arreglos de caracteres.	*/
void 
fillElement (elemento *e, char nombre[], char definicion[]){
	strncpy (e->nombre, nombre, TAMNOM);
	strncpy (e->definicion, definicion, TAMDEF);
}

/*	Inserta alfabeticamente en un arreglo de listas un elemento que contenga un campo nombre.	*/
void 
insertAlpha (lista *t, elemento e){
	int i = 0, indice = hash (e.nombre);
	lista *subl = &t[indice];
	nodo *pos = t[indice].frente;

	while (i < Size (subl) && strncmp (e.nombre, pos->e.nombre, TAMNOM) > 0){
		//pos = pos->siguiente;
		pos = Following (subl, pos);
		i++;
	}
	if (pos != NULL)
		InsertBefore (subl, e, pos);
	else 
		AddEnd (subl, e);

}

/*	Funcion que carga el archivo y va llenando la tabla hash con base al mismo.	*/
void
loadFile (lista *t){
	int c = 'n', i = 0; 
	char *nombre, *def;
	elemento e;

	/*	Esta condicion sirve para saber si el usuario desea cargar otro archivo.	*/
	if (archivoCargado){
		char ans[9];
		printf ("\nParece ser que el archivo %s ya ha sido cargado\n", nombreArchivo);
		printf ("Desea cargar otro? (s / n): ");	
		fgets (ans, 9, stdin);
		if (ans[0] == 's' || ans[0] == 'S'){
			for (i = 0; i < TAMHASH; i++)
				Destroy (&t[i]);
			/*	Importante la declaracion lista *t, no basta con t = ... 	*/
			lista *t = (lista *) calloc (TAMHASH, sizeof (lista));
		} else
			return;
	}
	printf ("Nombre del archivo (.txt): ");
	strscan (nombreArchivo, 40);
	sprintf (nombreArchivo, "%s.txt", nombreArchivo);
	FILE *fp = fopen (nombreArchivo, "rb");

	if (!fp){
		printf ("El archivo %s no existe. \n", nombreArchivo);
		return;
	}
	
	/*	Recorremos el archivo con un bucle while, mientras que c no sea EOF 
		(es decir, no lleguemos al final del archivo) vamos recorriendo el 
		archivo, caracter a caracter y vamos guardando en un string su nombre 
		y definicion por separado.	*/
	while (!feof (fp)){
		nombre = (char *) calloc (TAMNOM, sizeof (char));
		def = (char *) calloc (TAMDEF, sizeof (char));
		i = 0;
		/*	Puesto que el archivo tiene el formato:
				Palabra: definicion. \n
			se sabe que la palabra abarca desde su primera letra hasta los dos puntos.	*/ 
		while (i < TAMNOM && (c = fgetc (fp)) != ':' && c != '\n' && c != EOF)
			nombre[i++] = c;
		if(i > 0){
			nombre[i++] = '\0';
			c = fgetc (fp);
			i = 0;
			/*	De manera similar, la definicion abarca desde su primera letra hasta el salto 
			 *	de linea.	*/
			while (i < TAMDEF && (c = fgetc (fp)) != '\n' && c != EOF)
				def[i++] = c;
			def[i++] = '\0';
			/*	Insertamos la palabra a la tabla hash.	*/
			fillElement (&e, nombre, def);
			//AddEnd (&t[hash (nombre)], e);
			insertAlpha (t, e);
		}
	}
	archivoCargado = true;
	fclose (fp);
}

/*	Funcion que imprime todas las palabras del archivo.	*/
void
printAvailable (lista *l){
	bool b = false;
	int i = 0;

	/*	Nos aseguramos que exista una palabra, como minimo.	*/
	for (i = 0; i < TAMHASH; i++)
		if (l[i].frente){
			b = true;
			break;
		}

	if (b){
		int i = 0, j = 0, tab = 0;
		nodo *ptr = NULL;

		for (i = 0; i < TAMHASH; i++){
			ptr = l[i].frente;

			/*	Imprimimos la palabra, si existe almenos una palabra 
				con un caracter en la fila i, se entra al bucle, si no
				no entra, asi nos aseguramos de evadir el error SIGSEGV.	*/ 
			tab = 0;
			while (ptr){
				printf ("%s \t", ptr->e.nombre);
				ptr = ptr->siguiente;
				tab++;
				if (tab % 4 == 0){
					printf ("\n");
					tab = 0;
				}
			}
			printf ("\n \n");
		}
	}
	else
		puts ("No se ha cargado ningun archivo");
}

/*	Funcion que imprime una palabra solicitada, si existe.	*/
void
showDefinition (lista *t){
	char comp[99];
	int indice = 0, i = 0, contador = 0;
	nodo *ptr = NULL;

	printf ("Escriba la palabra a buscar: ");
	strscan (comp, 99);

	/*	Obtenemos el indice correspondiente a la palabra.	*/
	indice = hash (comp);
	ptr = t[indice].frente;

	/*	Procedemos a buscar la palabra, si existe se imprimira la palabra
		con su correspondiente definicion, si no existe se muestra por 
		pantalla que no existe la palabra buscada.	*/
	while (ptr){
		if (!strcmp (comp, ptr->e.nombre)){
			printf ("%s: %s \n", ptr->e.nombre, ptr->e.definicion);
			printf ("Iteraciones para encontrar la palabra: %d. \n", contador++);
			return;
		}
		ptr = ptr->siguiente;
		contador++;
	}

	printf ("La palabra \"%s\" no se encuentra en el diccionario. \n", comp);
}

/*	Funcion que imprime todas las palabras disponibles con la consonante propuesta.	*/
void
searchLetter (lista *t){
	char ans[3];
	int i = 0, contador = 0;

	printf ("Letra (mayus): ");
	fgets (ans, 3, stdin);

	i = hash (ans);

	if (t[i].frente){
		nodo *ptr = t[i].frente;

		while (ptr){
			printf ("%d.- %s \n", contador + 1, ptr->e.nombre);
			ptr = ptr->siguiente;
			contador++;
		}
	}
	else
		puts ("No se encuentra ninguna palabra con esa letra");
}

/*	Agregamos una palabra, tanto a el archivo como a la lista.	*/
void
addWord (lista *l){
	char nombre[TAMNOM], definicion[TAMDEF], parrafo[TAMNOM + TAMDEF + 10];
	elemento e;
	FILE *fp = fopen (nombreArchivo, "ab+");
	if (!fp){
		printf ("\n El archivo %s no existe. \n", nombreArchivo);
		return;
	}
	printf ("Palabra nueva: ");
	strscan (nombre, TAMNOM);

	printf ("Definicion: ");
	strscan (definicion, TAMDEF);

	sprintf (parrafo,"%s: %s", nombre, definicion);
	/*	Escribimos nuestra palabra al final de nuestro archivo, si daniar la palabra 
		anterior.	*/
	fprintf (fp, "%s\n", parrafo);
	fillElement (&e, nombre, definicion);
	AddEnd (&l[hash (nombre)], e);

	puts ("No se requieren iteraciones para agregar una palabra.");

	fclose (fp);
}

/*	Funcion que recibe la lista * y un string s, en la funcion solo nos importa la primera letra 
	del string. Como extra cambia el caracter s[0] a mayuscula, en case de que sea alfanumerico
	este caracter, obviamente.	*/
bool
existWord (lista *t, char s[]){
	int indice = 0;

	/*	Obtenemos el indice de s[0]. Se sabe que existe un valor correspondiente puesto que ya paso
		la condicion anterior.	*/
	indice = hash (s);
	nodo *ptr = t[indice].frente;

	/*	Buscamos en nuestra fila i-esima de nuestra tabla, si existe, retornamos true	*/
	while (ptr){
		if (!strncmp (s, ptr->e.nombre, TAMNOM))
			return true;
		ptr = ptr->siguiente;
	}

	return false;
}

/*	Borra la palabra p, tanto en la tabla como en el archivo, si existe.	*/
void
deleteWord (lista *t){
	char pbuscada[TAMNOM];

	printf ("\ningrese la palabra a borrar: ");
	strscan (pbuscada, TAMNOM);
	
	/*	Comprobamos que exista la palabra y, si existe, procedemos borramos y 
		escribimos el archivo, saltandonos la palabra no deseada.	*/
	if (existWord (t, pbuscada)){
		FILE *fp = fopen (nombreArchivo, "wb");
		nodo *ptr = NULL;
		int i = 0;
		for (i = 0; i < TAMHASH; i++){
			ptr = t[i].frente;
			while (ptr){
				if (strncmp (ptr->e.nombre, pbuscada, TAMNOM))
					fprintf (fp, "%s: %s\n", ptr->e.nombre, ptr->e.definicion);
				else
					Remove (&t[hash (ptr->e.nombre)], ptr);
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
changeDefinition (lista *t){
	char nuevaDef[TAMDEF], pBuscada[TAMNOM];
	int i = 0, contador = 0;

	printf ("\nIngrese la palabra a cambiar: ");
	strscan (pBuscada, TAMNOM);

	/*	Comprobamos si existe la palabra	*/
	if (existWord (t, pBuscada)){
		FILE *fp = fopen (nombreArchivo, "wb");
		if (!fp){
			printf ("\nEl archivo %s no existe. \n", nombreArchivo);
			return;
		}
		nodo *ptr;
		/*	Obtenemos la nueva definicion.	*/
		printf ("Nueva definicion: ");
		strscan (nuevaDef, TAMDEF);

		/*	Recorremos las 26 palabras y reescribimos todo el archivo, cuando nos 
			encontremos con la palabra a cambiar, escribimos la nueva palabra y nos
			saltamos la sobreescritura de la palabra anterior, asi como su definicion.*/
		for (i = 0; i < TAMHASH; i++){
			ptr = t[i].frente;
			while (ptr){
				if (!strncmp (pBuscada, ptr->e.nombre, TAMNOM)){
					sprintf(ptr->e.definicion, "%s", nuevaDef);
					fprintf (fp, "%s: %s\n", pBuscada, nuevaDef);
					strncpy (ptr->e.definicion, nuevaDef, TAMDEF);
					printf ("\nSe realizaron %d iteraciones para localizar la palabra", contador + 1);
				} else
					fprintf (fp, "%s: %s\n", ptr->e.nombre, ptr->e.definicion);
				ptr = ptr->siguiente;
				contador++;
			}
		}

		fclose (fp);
	}
	else
		printf ("La palabra \"%s\" no se encuentra", pBuscada);
}

/*	Exporta toda la lista a un archivo con el nombre que el usuario desee.	*/
void 
exportList (lista *t){
	int i, cont = 1;
	nodo *ptr = NULL;
	char nombre[50];

	printf ("\nNombre del archivo (.txt): ");
	strscan (nombre, 40);
	sprintf (nombre, "%s.txt", nombre);

	FILE *fp = fopen (nombre, "wb");
	if (!fp){
		printf ("\nEl archivo %s no existe. \n", nombre);
		return;
	}

	for (i = 0; i < TAMHASH; i++){
		ptr = t[i].frente;
		while (ptr){
			fprintf (fp, "%s: %s\n", ptr->e.nombre, ptr->e.definicion);
			ptr = ptr->siguiente;
			cont++;
		}
	}
	printf ("Se exportaron %d palabras a %s. \n", cont, nombre);
	
	fclose (fp);
}

/*	Funcion que exporta una palabra con su definicion a un archivo de texto.
 *	Problema: Se guarda basura al final del archivo creado.		*/
void 
exportDefinition (lista *t){
	char nombre[TAMNOM];

	printf ("\nNombre de la palabra a exportar: ");
	strscan (nombre, TAMNOM);

	if (existWord (t, nombre)){
		char nombreArchivoNuevo[50];
		nodo *ptr = t[hash (nombre)].frente;
		int cont = 1;

		printf ("Nombre del archivo (.txt): ");
		strscan (nombreArchivoNuevo, 40);
		sprintf (nombreArchivoNuevo, "%s.txt", nombreArchivoNuevo);
		FILE *fp = fopen (nombreArchivoNuevo, "wb");
		if (!fp){
			printf ("\nEl archivo %s no existe.\n", nombreArchivoNuevo);
			return;
		}
		while (ptr){
			if (!strncmp (nombre, ptr->e.nombre, TAMNOM)){
				fprintf (fp, "%s: %s", ptr->e.nombre, ptr->e.definicion);
				puts ("Palabra exportada exitosamente :D. ");
				printf ("Se requirieron %d iteraciones para localizar la palabra %s. \n", cont, nombre);
				break;
			}
			ptr = ptr->siguiente;
			cont++;
		}
		fclose (fp);
	} else 
		printf ("la palabra %s no se encuentra en el diccionario. ", nombre);
}

/*	Funcion que busca todas las palabras disponibles, con su respectiva definicion
    que contengan una subcadena dada (si existe).	*/
void 
searchSubstring (lista *t){
	char substr[TAMNOM];
	int i, n, N, cont = 1;
	bool hayUna = false; 
	nodo *ptr = NULL;

	printf ("\nEscriba la subcadena: ");
	strscan (substr, TAMNOM);
	n = strlen (substr);

	/*	Con un bucle recorremos las 26 listas que como maximo puede tener la tabla.	*/
	for (i = 0; i < TAMHASH; i++){
		ptr = t[i].frente;
		while (ptr){
			N = strlen (ptr->e.nombre);
			if (n <= N)
				/*	La funcion char *strstr (char *A, char *B) retorna true si la subcadena B esta en A	*/ 
				if (strstr (ptr->e.nombre, substr)){
					printf ("%s: %s \n", ptr->e.nombre, ptr->e.definicion);
					printf ("Iteraciones para localizar la subcadena %s: %d \n", substr, cont);
					hayUna = 1;
				}
			ptr = ptr->siguiente;
			cont++;
		}
	}	
	if (!hayUna)
		printf ("No se encuentra ninguna palabra con la subcadena %s. ", substr);			
}

/*	Funcion que, pregunta alguna frase y muestra las palabras disponibles en el diccionario 
	tales que su definicion contengan a la frase.	*/ 
void 
searchSentence (lista *t){
	char frase[TAMNOM];
	nodo *ptr;
	int i, j, noHay = true, cont = 1;
	
	printf ("\nFrase: ");
	strscan (frase, TAMNOM);
	for (i = 0; i < TAMHASH; i++){
		ptr = t[i].frente;
		while (ptr){
			if (strstr (ptr->e.definicion, frase)){
				printf ("%s: %s \n", ptr->e.nombre, ptr->e.definicion);
				printf ("%s encontrada despues de %d pasos", frase, cont); 
				noHay = 0;
			}	
			ptr = ptr->siguiente;
			cont++;
		}
	}
	if (noHay)
		printf ("La frase \" %s \" no se encuentra en el diccionario.", frase);
}

/*	Funcion que muestra las opciones disponibles para el programa. 	*/
void
menu (lista *dicc){
	char aux[9];
	int opcion;

	do{
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
			case 3: showDefinition (dicc); break;
			case 4: changeDefinition (dicc); break;
			case 5: deleteWord (dicc); break;
			case 6: searchSubstring (dicc); break;
			case 7: searchLetter (dicc); break;
			case 8: searchSentence (dicc);  break;
			case 9: exportList (dicc); break;
			case 10: exportDefinition (dicc); break;
			case 11: printAvailable (dicc); break;
			case 12: puts ("Hasta luego \n"); break;
			default: puts ("Opcion no valida"); break;
		}
	}while(opcion != 12);
}

/*	Raiz del programa	*/
int 
main (int argc, char *argv[]){
	lista *dicc = (lista *) calloc (TAMHASH, sizeof (lista));
	int i;
	
	/*	con void *calloc no es necesaria la funcion void Initialize (lista *).	
	for (i = 0; i < TAMHASH; i++)
		Initialize (&dicc[i]);
	*/
	menu (dicc);
	
	for (i = 0; i < TAMHASH; i++)
		Destroy (&dicc[i]);

	return 0;
}
