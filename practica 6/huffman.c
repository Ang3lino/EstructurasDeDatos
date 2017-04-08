/* Codificacion del algoritmo de huffman */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct elemento{
    int caracter, frecuencia, direccion;
} elemento;

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
bubbleSort (elemento *s, int lim){
    int i = 0, j = 0;
    elemento aux;

    for (i = 0; i < lim - 1; i++)
        for (j = 0; j < lim - 1; j++)
            if (s[j].frecuencia > s[j + 1].frecuencia){
                aux = s[j];
                s[j] = s[j + 1];
                s[j + 1] = aux;                
            } 

}

void 
printData (elemento *x, int lim){
    int i = 0;

    printf ("\n");

    for (i = 0; i < lim; i++){
        printf ("letra %c ", x[i].caracter);
        printf ("frecuencia %d", x[i].frecuencia);
        printf ("dir %d", x[i].direccion);
        printf ("\n");
    }
}

int  
countFrequency (char palabra[20], elemento *cadena){
    char aux = 1;
    int longitud = strlen (palabra);
    int i = 0, j = 0, k = 0, buul = 1;

    for (i = 0; i < longitud; i++){
        buul = 1;
        aux = palabra[i];
        for (j = 0; j < i; j++)
            if (aux == palabra[j])
                buul = 0;
        if (buul){
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

int 
main (void){
    char palabra[99];
    elemento *cadena = (elemento *) calloc (sizeof (elemento), 99);
    int lim = 0;

    strcpy (palabra, "geografia");

    lim = countFrequency (palabra, cadena);
    printData (cadena, lim);
    //bubbleSort (cadena, 7);
    insertionSort (cadena, lim);
    printData (cadena, lim);

    return 0;
}





