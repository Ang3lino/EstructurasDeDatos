/*   Programa que emula la gestion de programas de un sistema operativo.  */

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include "ColaDin.h"

/*  el elemento e esta conformado por su nombre, actividad (lo que hace), su ID,
    tiempo propuesto para la ejecucion del programa y un contador que se usara
    mas adelante (En la funcion procesar, para ser exactos).    */

/*  Se uso typedef para que el codigo sea mas legible.  */
typedef elemento programa;

/* Se puede usar para rellenar la cola (sin albur) con programas predeterminados. */
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

    return;
}

/*  Dado un programa p y un tiempo de espera, esta funcion imprime los campos del programa
    y su tiempo de espera.  */
void
mostrarActual (programa p, int espera){
    puts ("\nProceso actual");
    printf ("Nombre del programa: %s \n", p.nombre);
    printf ("ID: %s \n", p.id);
    printf ("Actividad: %s \n", p.actividad);
    printf ("Tiempo total que lleva ejecutandose: %d segundos \n", p.contador + espera);
    return;
}

/*  Muestra el ID y nombre del ultimo programa, junto con su tiempo restante para culminar
    su ejecucion. Recibe el ultimo programa formado en la cola.   */
void
mostrarUltimo (programa p){
    puts ("\nUltimo proceso");
    printf ("ID: %s \t Nombre: %s \n", p.id, p.nombre);
    printf ("Tiempo restante: %d segundos \n", p.tiempo - p.contador);
    return;
}

/*  Muestra el programa que esta en el frente de la cola, con su tiempo que hace falta para
    que se culmine su ejecucion.    */
void
mostrarSiguiente (programa p){
    puts ("\nProceso siguiente");
    printf ("ID: %s \t Nombre: %s \n", p.id, p.nombre);
    printf ("Tiempo restante: %d segundos \n", p.tiempo - p.contador);
    return;
}

/*  Imprime el nombre de el programa que ya finalizo.   */
void
mostrarTerminado (programa p){
    printf ("\nEl programa %s se ha acabado de ejecutar. \n", p.nombre);
    return;
}

/*  Dada una cola, en la cual se fueron formando los programas conforme se
    acabaron de ejecutar, esta funcion imprime sus campos y su tiempo total
    que se empleo para su ejecucion.    */
void
mostrarFinalizados (cola *c){
    programa p;

    puts ("\nProgramas ejecutados exitosamente :D");

    while (!Empty (c)){
        p = Dequeue (c);
        printf ("\nNombre: %s \t ID: %s \n", p.nombre, p.id);
        printf ("Tiempo usado para finalizar el programa: %d segundos \n", p.tiempo);
    }

    Destroy (c);
    return;
}

/*  Funcion que procesa una cola de programas conforme el siguiente criterio:
    Se desencolara el programa p y se incrementara su contador ya definido en
    su campo, si el contador es menor al tiempo propuesto por el usuario, se
    volvera a encolar el programa p, si no, se formara en la cola "acabados",
    la cual se enviara a la funcion de aqui arriba.     */
void
procesar (cola *c){
    programa p;
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
        tiempo_espera++;

        if (p.contador < p.tiempo)
            Queue (c, p);
        else {
            mostrarTerminado (p);
            p.tiempo += tiempo_espera;
            Queue (&acabados, p);
        }

        Sleep (1 * seg);
        system ("cls");
    }

    mostrarFinalizados (&acabados);
}

/*  Funcion parecida al fgets (), solo que esta funcion fue diseniada especificamente
    para recibir datos por el teclado. A diferencia de fgets (), esta funcion
    pone un fin de cadena al final del string.  */
void
strscan (char *s, int lim){
    char c;
    int i = 0;

    while ((c = getchar ()) != '\n' && i < lim){
        s[i++] = c;
    }

    s[i] = '\0';
}

/*  Funcion destinada a preguntar los campos del programa al usuario y formarlos
    en la cola c.   */
void
pedirDatos (cola *c){
    programa p;
    char aux[9];

    printf ("\nDesea encolar un programa? (s/n): ");
    strscan (aux, 9);
    if (aux[0] == 'n' || aux[0] == 'N')
        return;

    while (TRUE){
        printf ("\nNombre del programa: ");
        strscan (p.nombre, 45);
        printf ("Actividad del programa: ");
        strscan (p.actividad, 200);
        printf ("ID: ");
        strscan (p.id, 45);
        printf ("Tiempo: ");
        strscan (aux, 9);
        sscanf (aux, "%d", &p.tiempo);
        p.contador = 0;
        Queue (c, p);

        printf ("Desea encolar otro programa? (s/n): ");
        strscan (aux, 9);
        if (aux[0] == 'n' || aux[0] == 'N')
            return;
    }

    system ("cls");
}

/*  Manda a llamar a la funcion pedirDatos (), forma los programas en la cola c.
    Si la cola esta vacia, muetra un mensaje "No hay nada que mostrar", si no,
    procede a ejecutar el algoritmo propuesto para la practica 2, programa 2.   */
int
main (void){
    cola c;
    Initialize (&c);
    //prueba (&c);
    pedirDatos (&c);

    if (Empty (&c)){
        puts ("No hay nada que mostrar.");
        Destroy (&c);
        return 0;
    }

    procesar (&c);

    Destroy (&c);
    return 0;
}
