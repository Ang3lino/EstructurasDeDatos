/* Parte 2 */

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "TADColaDin.c"

typedef elemento programa;

/* Funcion que uso para hacer prebas.
    encola en una cola c.*/
void
prueba (cola *c){
    programa p;

    strcpy (p.nombre, "word");
    strcpy (p.actividad, "Editor de texto");
    p.tiempo = 10;
    p.contador = 0;
    Queue (c, p);

    strcpy (p.nombre, "atom");
    strcpy (p.actividad, "editor de codigo");
    p.tiempo = 5;
    p.contador = 0;
    Queue (c, p);

    strcpy (p.nombre, "ccleaner");
    strcpy (p.actividad, "Limpia basura");
    p.tiempo = 20;
    p.contador = 0;
    Queue (c, p);

    strcpy (p.nombre, "firefox");
    strcpy (p.actividad, "navegador de internet");
    p.tiempo = 30;
    p.contador = 0;
    Queue (c, p);
}

void
mostrarActual (programa p){
    puts ("Proceso actual");
    printf ("Nombre del programa: %s", p.nombre);
    printf ("ID: %d", p.id);
    printf ("Actividad: %s", p.actividad);
    printf ("Tiempo que lleva ejecutandose: %d", p.contador);
}

void
mostrarUltimo (programa p){
    puts ("Ultimo proceso");
    printf ("ID: %d \t Nombre: %s", p.id, p.nombre);
}

void
mostrarSiguiente (programa p){
    puts ("Proceso siguiente");
    printf ("ID: %d \t Nombre: %s \t Tiempo restante: %d", p.id, p.tiempo - p.contador);
}

void
mostrarTerminado (programa p){
    printf ("El programa %s se ha acabado de ejecutar", p.nombre);
}

void
procesar (cola *c){
    programa p, aux;
    int seg = 1e9;

    if (!Empty (c)){
        while (!Empty (c)){
            Sleep (seg);
            p = Dequeue (c);
            mostrarActual (p);
            aux = p;
            p = Dequeue (c);
            mostrarUltimo (p);

        }

    }
    else
        puts ("No hay nada que procesar.");
}

int
main (void){
    cola c;
    int n_programas = 4;
    Initialize (&c);
    prueba (&c);

    procesar (&c);

    Destroy (&c);
    return 0;
}
