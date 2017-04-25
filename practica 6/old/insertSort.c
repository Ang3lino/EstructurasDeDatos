/* Ordenamiento por inserccion */
#include <stdio.h>
#include <stdlib.h>

void 
insertionSort (int arreglo[], int longitud){
    int i = 0, j = 0;
    int aux = 0;

    for (j = 1; j < longitud ; j++){
        aux = arreglo[j];
        i = j - 1;
        while (i >= 0 && arreglo[i] > aux){
            arreglo[i + 1] = arreglo[i];
            i--;
        }
        arreglo[i + 1] = aux;
    }    
}

int 
main (void){
    int conjunto[10];
    int j = 0, i = 0;

    j = 10;
    for (i = 0; i < 10; i++){
        conjunto[i] = j;
        j--;
    }

    insertionSort (conjunto, 10);
    for (i = 0; i < 10; i++)
        printf ("%d, ", conjunto[i]);

    return 0;
}







