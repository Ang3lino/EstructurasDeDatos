/* Proyecto abandonado, solo arma el arbol de huffman no optimizado.
 *
 * tamanio de la cadena: 1000
 * caracteres de la A-Z, a-z y 0-9 
 * supongo que los espacion tambien...
 * investigar funciones de corrimiento 2 >> 1
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbolBin.h"

void 
insertionSort (elemento *arreglo, int longitud){
    int i = 0, j = 0;
    elemento aux;
    
    for (j = 1; j < longitud ; j++){
        aux = arreglo[j];
        i = j - 1;
        while (i >= 0 && arreglo[i].frecuencia > aux.frecuencia){
            arreglo[i + 1] = arreglo[i];
            i--;
        }
        arreglo[i + 1] = aux;
    }    
}

void 
printData (elemento *x, int lim){
    int i = 0;

    printf ("\n");

    for (i = 0; i < lim; i++){
        printf ("letra %c ", x[i].caracter); 
        printf ("frecuencia %d ", x[i].frecuencia);
        printf ("dir %d ", x[i].direccion);
        printf ("\n");
    }
}

int  
countFrequency (char palabra[20], elemento *cadena){
    char aux = 1;
    int longitud = strlen (palabra);
    int i = 0, j = 0, k = 0, noLetraRepetida = 1;

    for (i = 0; i < longitud; i++){
        noLetraRepetida = 1;
        aux = palabra[i];
        for (j = 0; j < i; j++)
            if (aux == palabra[j]){
                noLetraRepetida = 0;
                break;
            }
        if (noLetraRepetida){
            cadena[k].caracter = palabra[i];
            cadena[k].frecuencia++;
            for (j = i + 1; j < longitud; j++)
                if (palabra[i] == palabra[j])
                    cadena[k].frecuencia++;
            k++;
        }
    }
    cadena = (elemento *) realloc (cadena, k * sizeof (elemento));
    return k;
}

int piso (int num, int den){ return num / den; }

int 
techo (int numerador, int denominador){ 
    if (numerador % denominador == 0)
        return numerador / denominador;   
    return piso (numerador, denominador) + 1;
}

arbol *huffmanHelper (arbol *arboles, int nivel) {
    arbol *a = createTree ();
    nivel = techo (nivel, 2);
    int i = 0, j = 0, f1 = 0, f2 = 0;
     
    if (nivel == 1){
        insertLeft (&a, &arboles[j]);
        f1 = arboles[j++].e.frecuencia;
        a->e.frecuencia = f1;     
        if (arboles[j].e.frecuencia){
            insertRight (&a, &arboles[j]);
            f2 = arboles[j++].e.frecuencia;
            a->e.frecuencia = f1 + f2;
        }
        return a;
    }

    arbol *padres = (arbol *) calloc (sizeof (arbol), nivel);
    for (i = 0; i < nivel; i++){
        f1 = 0; f2 = 0; 
        insertLeft (&a, &arboles[j]);
        f1 = arboles[j++].e.frecuencia;
        a->e.frecuencia = f1 + f2;
        padres[i] = *a;
        if (!arboles[j].e.frecuencia)
            break;
        insertRight (&a, &arboles[j]);
        f2 = arboles[j++].e.frecuencia;
        a->e.frecuencia = f1 + f2;
        padres[i] = *a;
    }

    return huffmanHelper (padres, nivel);
}

arbol *huffman (elemento *cadena, int lim) {
    int nivel = techo (lim, 2);
    int i = 0, j = 0, f1 = 0, f2 = 0; 
    arbol *arboles = (arbol *) calloc (sizeof (arbol), nivel);
    arbol *a = (arbol *) calloc (sizeof (arbol), 1);

    for (i = 0, j = 0; i < nivel; i++){
        f1 = 0; f2 = 0;
        insertElementLeft (&a, cadena[j]);
        f1 = cadena[j++].frecuencia;
        arboles[i] = *a;  
        arboles[i].e.frecuencia = f1 + f2;      
        if (!cadena[j].frecuencia) 
            break;
        insertElementRight (&a, cadena[j]);
        f2 = cadena[j++].frecuencia;
        arboles[i] = *a;  
        arboles[i].e.frecuencia = f1 + f2;
    }

    return huffmanHelper (arboles, nivel);
}

/* para acceder a los hijos del arbol
    for (i = 0; i < nivel; i++){
        printf ("%c %c \n", arboles[i].izq->e.caracter, arboles[i].der->e.caracter);
    }   */

int 
main (int argc, char *argcv[]) {
    char palabra[99];
    elemento *cadena = (elemento *) calloc (sizeof (elemento), 99);
    int lim = 0;
    arbol *a = createTree ();

    strcpy (palabra, "hola a todos !!!!!!");
    lim = countFrequency (palabra, cadena);
    printData (cadena, lim);
    insertionSort (cadena, lim);
    printData (cadena, lim);

    a = huffman (cadena, lim);
	puts ("Rerrido del arbol en inorden");
	inorder (a);


    free (cadena);
    return EXIT_SUCCESS;
}

