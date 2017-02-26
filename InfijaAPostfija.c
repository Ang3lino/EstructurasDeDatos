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
aritméticos "+", "-", "*", "/"
Recibe: char operador
Devuelve: int, indicando la precedencia del operador
*/
int PrecedenciaOperador(char operador);

/*
Descripción: Indica si un caracter específico
es alguno de los cinco operadores: +, -, *, /, ^
Recibe: char operador (el operador a revisar)
Devuelve: boolean, TRUE si el caracter es operador,
FALSE en caso contrario 
*/
boolean EsOperador(char operador);

/*  Solo retorna TRUE si se es uno de los operadores especificados  */
boolean
EsOperador (char c){
    switch (c){
        case '+': case '-': case '*': 
        case '/': case '^': return TRUE;
        default: return FALSE;
    }
}

/*Descripción: Indica si un caracter específico
es alguna letra de la A a la Z
Recibe: char operador (el operador a revisar)
Devuelve: boolean, TRUE si el caracter es una
letra, FALSE en caso contrario 
*/
boolean EsCaracter(char operador);

/* Esta funcion se aprovecha de los valores ASCII y retorna TRUE si el caracter se encuentra en el rango    */
boolean
EsCaracter (char c){
    if (c >= 'A' && c <= 'Z')
        return TRUE;
    return FALSE;
}
  

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

/*	Dado un caracter, esta funcion retornara su correspondiente 
 *	posicion
 *	A = 0, B = 1, ..., Z = 25 
 */

int hash (char c){ return c - 'A'; }

double
EvaluaExpresionPostFija (char *postf, double *var){
	int i = 0, lim = strlen (postf), indice = 0;
	elemento e, aux;
	pila *p;
	double acum = 0;

	Initialize (p);


	for (i = 0; i < lim; i++){
		if (EsCaracter (postf[i])){
			indice = hash (postf[i]);
			e.doble = var[indice];
			Push (e, p);
		}
		else{
			switch (postf[i]){
				case '+': case '-':
					aux = Pop (p); e = Pop (p);	e.doble = aux.doble + e.doble; break;
				case '*': 
					aux = Pop (p); e = Pop (p); e.doble = aux.doble * e.doble; break;
				case '/': 
					aux = Pop (p); e = Pop (p); e.doble = e.doble / aux.doble; break;
				case '^': 
					aux = Pop (p); e = Pop (p); e.doble = pow (e.doble, aux.doble); break;
			}
		
			Push (e, p);
		}
	}

	aux = Pop (p);
	acum = aux.doble;
	Destroy (p);

	return acum;
}

//PROGRAMA PRINCIPAL
int main(){
  return 0;
}
