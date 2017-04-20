#include "ColaPrioridad.h"

void InitializeQueue(ColaPrioridad *C){
    C->tamano = 0;
    C->capacidad = 0;
    C->nodos = NULL;
}

void push(ColaPrioridad *C, int prioridad, arbol_bin *A){
    if (C->tamano + 1 >= C->capacidad) {
        C->capacidad = C->capacidad ? C->capacidad * 2 : 4;
        C->nodos = realloc(C->nodos, C->capacidad * sizeof (dato));
    }
    int i = C->tamano + 1;
    int j = i / 2;
    while (i > 1 && C->nodos[j].prioridad >= prioridad) {
        C->nodos[i] = C->nodos[j];
        i = j;
        j = j / 2;
    }
    C->nodos[i].prioridad = prioridad;
    C->nodos[i].A = A;
    C->tamano++;
    return;
}
 
dato pop(ColaPrioridad *C){
    int i, j, k;
    dato d;
    if (C->tamano == 0)
        return d;
    d = C->nodos[1];
    C->nodos[1] = C->nodos[C->tamano];
    C->tamano--;
    i = 1;
    while (1) {
        k = i;
        j = 2 * i;
        if (j <= C->tamano && C->nodos[j].prioridad <= C->nodos[k].prioridad)
            k = j;
        if (j + 1 <= C->tamano && C->nodos[j + 1].prioridad <= C->nodos[k].prioridad)
            k = j + 1;
        if (k == i)
            break;
        C->nodos[i] = C->nodos[k];
        i = k;
    }
    C->nodos[i] = C->nodos[C->tamano + 1];
    return d;
}