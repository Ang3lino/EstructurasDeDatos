/*
Autor: Edgardo Adrián Franco Martínez
Versión 1.1 (02 de Octubre de 2013)
Descripción: Cabecera de la libreria para recrear presentaciones más agradables al usuario en el modo consola bajo Linux
Observaciones: Esta implementación de la libreria solo es compatible con Linux y el compilador GNU gcc  de UNIX ya que utiliza la libreria "unistd.h", la cuál no es estandar.
Compilación de la libreria: Linux (gcc -c presentacionLin.c)
*/
//LIBRERIAS
#include <stdio.h>			
#include <unistd.h>  		//Libreria no ANSI C
#include"presentacion.h"

//DEFINICIÓN DE FUNCIONES

//Función para mover el cursor de escritura de pantalla, simulación de la función gotoxy() que se tenia en borland 3.0 en la libreria conio.h
void MoverCursor( int x, int y ) 
{
	printf("%c[%d;%df",0x1B,y,x);
	return;
};

//Función para esperar un tiempo en milisegundos, simulación de la función delay() que se tenia en borland 3.0 en la libreria conio.h
void EsperarMiliSeg(int t)
{
	usleep(t*1000);
	return;
}

//Función para borrar la pantalla de la consola, simulación de la función clrscr() que se tenia en borland 3.0 en la libreria conio.h
void BorrarPantalla(void)
{
	system("clear");
	return;
}
