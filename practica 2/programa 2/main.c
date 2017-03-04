/* Parte 2 */

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ColaDin.h"

typedef elemento programa;

/* Funcion que uso para hacer prebas.
    encola en una cola c.*/
void
prueba (cola *c){
    programa p;

    strcpy (p.nombre, "word");
    strcpy (p.actividad, "Editor de texto");
    strcpy (p.id, "43246");
    p.tiempo = 10;
    p.contador = 0;
    Queue (c, p);

    strcpy (p.nombre, "atom");
    strcpy (p.actividad, "editor de codigo");
    strcpy (p.id, "43246");
    p.tiempo = 5;
    p.contador = 0;
    Queue (c, p);

    strcpy (p.nombre, "ccleaner");
    strcpy (p.actividad, "Limpia basura");
    strcpy (p.id, "43246");
    p.tiempo = 20;
    p.contador = 0;
    Queue (c, p);

    strcpy (p.nombre, "firefox");
    strcpy (p.actividad, "navegador de internet");
    strcpy (p.id, "43246");
    p.tiempo = 30;
    p.contador = 0;
    Queue (c, p);
}

void
mostrarActual (programa p, int espera){
    puts ("\nProceso actual");
    printf ("Nombre del programa: %s \n", p.nombre);
    printf ("ID: %s \n", p.id);
    printf ("Actividad: %s \n", p.actividad);
    printf ("Tiempo total que lleva ejecutandose: %d \n", p.contador + espera);
}

void
mostrarUltimo (programa p){
    puts ("\nUltimo proceso");
    printf ("ID: %s \t Nombre: %s \n", p.id, p.nombre);
    printf ("Tiempo restante: %d \n", p.tiempo - p.contador);
}

void
mostrarSiguiente (programa p){
    puts ("\nProceso siguiente");
    printf ("ID: %s \t Nombre: %s \n", p.id, p.nombre);
    printf ("Tiempo restante: %d \n", p.tiempo - p.contador);
}

void
mostrarTerminado (programa p){
    printf ("\nEl programa %s se ha acabado de ejecutar. \n", p.nombre);
}

void
mostrarFinalizados (cola *c){
    programa p;

    puts ("\nProgramas ejecutados exitosamente :D");

    while (!Empty (c)){
        p = Dequeue (c);
        printf ("\nNombre: %s \t ID: %s \n", p.nombre, p.id);
        printf ("Tiempo usado para finalizar el programa: %d \n", p.tiempo);
    }

    Destroy (c);
}

void
procesar (cola *c){
    programa p, aux;
    cola acabados;
    int seg = 1e3, tiempo_espera = 0;

    Initialize (&acabados);

    while (!Empty (c)){
        p = Dequeue (c);
        mostrarActual (p, tiempo_espera);

        if (Size (c) >= 1){
            mostrarUltimo (Final (c));
            mostrarSiguiente (Front (c));
        }
        p.contador++;

        if (p.contador < p.tiempo)
            Queue (c, p);
        else {
            mostrarTerminado (p);
            p.tiempo += tiempo_espera;
            Queue (&acabados, p);
        }
        tiempo_espera++;
        Sleep (1 * seg);
        system ("cls");
    }

    mostrarFinalizados (&acabados);
    return;
}


int
main (void){
    cola c;
    int n_programas = 4;
    Initialize (&c);
    prueba (&c);

    if (Empty (&c)){
        puts ("No hay nada que mostrar.");
        Destroy (&c);
        return 0;
    }

    procesar (&c);

    Destroy (&c);
    return 0;
}
