/*
CONVERSIÓN DE EXPRESIONES INFIJAS A POSTFIJAS Y EVALUACIONES
Compilación usando pila dinámica: gcc InfijaAPostFija.c PilaDin.c -o InfijaAPostFija.exe
Compilación usando pila dinámica: gcc InfijaAPostFija.c PilaEst.c -o InfijaAPostFija.exe
*/

//LIBRERIAS
#include "PilaDin.h"
//#include "PilaEst.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

//FUNCIONES PROPUESTAS

/*
Descripción: Devuelve la precedencia de los operadores
aritméticos "+", "-", "*", "/", "("
Recibe: char operador
Devuelve: int, indicando la precedencia del operador
*/
int PrecedenciaOperador(char operador);

/*
Descripción: Verifica si una expresión
aritmética tiene emparejados correctamente
sus paréntesis.
Recibe: char * cadena (expresión a verificar)
Devuelve: int (1 si la expresión es correcta,
0 si un parentesis cierra sin haber abierto,
-1 si un parentesis abre y no cierra)
*/
int VerificarParentesis(char * cadena);

/*
Descripción: Convierte una expresión aritmética
de su forma infija a su forma postfija.
Recibe: char * expresion_infija (expresión en su forma
infija), char * expresion_postfija (apuntador a char
para guardar la expresión en su forma postfija),
boolean * variables_introducidas (arreglo de booleanos
para guardar la ocurrencia de las variables en la
expresion)
Devuelve: 
Observaciones: Se asume que la expresión pasó el test
de los paréntesis
*/
void ConvierteInfijaAPostFija(char * expresion_infija, char * expresion_postfija, boolean * variables_introducidas);

/*
Descripción: Evalua el resultado numérico de una expresión
en su forma postfija, dados los valores de sus incógnitas
Recibe: char * expresion_postfija (expresión en su forma
postfija), double * valores_variables (arreglo con los
valores numéricos de todas las incógnitas)
Devuelve: double (la evaluación de la expresión)
*/
double EvaluaExpresionPostFija(char * expresion_postfija, double * valores_variables);

//PROGRAMA PRINCIPAL
int main(){
  return 0;
}
