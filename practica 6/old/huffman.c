/* Codificacion del algoritmo de huffman */

#define TAM 1000

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "arbolBin.h"

/*  TAD COLA ===========================================================================
    INICIO

    Inclusion de la cola de prioridad, donde se guardaran arboles y se insertaran
    de acuerdo a la frecuencia del nodo.    */

/* frente -> q1 -> q2 -> ... -> final -> NULL */
typedef struct cola{
    int longitud, frente, final;
    arbol *a;
} cola;

void 
initialize (int tam){
    cola *nuevaC = (cola *) calloc (sizeof (cola), 1);
    
    nuevaC->longitud = tam;
    nuevaC->frente = nuevaC->final = 0;

    return nuevaC;
}

void 
queue (cola *c, arbol a){
    if ()

}

arbol 
dequeue (cola *c){
    arbol x = c[c->frente]->a;

    if (c->frente == c->longitud)
        c->frente = 0;
    else 
        c->frente++;

    return x;
}


/*  FIN DEL TAD ==========================================================================*/

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

/*  Embute cada caracter en un arreglo de elementos con su respectiva frecuencia */

int  
countFrequency (char palabra[], elemento *cadena){
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

void 
huffman (elemento *c, int n){
    int i = 0;
    arbol *arboles = (arbol *) malloc (sizeof (arbol) * n);

    for (i = 1; i <= n - 1; i++){
        
        

    }    


}

int 
main (int argc, char *argcv[]) {
    char palabra[TAM];
    elemento *cadena = (elemento *) calloc (sizeof (elemento), TAM);
    int lim = 0;
    arbol *a = createTree ();

    strcpy (palabra, "geografia");
    lim = countFrequency (palabra, cadena);
    printData (cadena, lim);
    insertionSort (cadena, lim);
    printData (cadena, lim);

    huffman (cadena, lim);

  
    free (cadena);
    return EXIT_SUCCESS;
}

