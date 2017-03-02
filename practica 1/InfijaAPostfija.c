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
Descripción: Indica si un caracter específico
es alguno de los cinco operadores: +, -, *, /, ^
Recibe: char operador (el operador a revisar)
Devuelve: boolean, TRUE si el caracter es operador,
FALSE en caso contrario 
*/
boolean EsOperador (char c){
    switch (c){
        case '+': case '-': case '*': 
        case '/': case '^': return TRUE;
        default: return FALSE;
    }
}

/*
Descripción: Devuelve la precedencia de los operadores
aritméticos "+", "-", "*", "/", "^"
Recibe: char operador
Devuelve: int, indicando la precedencia del operador
*/
int PrecedenciaOperador(char operador){
	switch(operador){
		case '^': return 3;
		case '*': case '/': return 2;
		case '+': case '-': return 1;
		default: return 0;
	}
}

/*Descripción: Indica si un caracter específico
es alguna letra de la A a la Z
Recibe: char operador (el operador a revisar)
Devuelve: boolean, TRUE si el caracter es una
letra, FALSE en caso contrario.
Esta funcion se aprovecha de los valores ASCII
y retorna TRUE si el caracter se encuentra en el rango
*/
boolean EsCaracter (char c){
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
int VerificarParentesis (char *cadena){
	int i = 0, lim = strlen (cadena);
	elemento e;
	pila p;

	Initialize (&p);

	for (i = 0; i < lim; i++){
		if (cadena[i] == '('){
			e.caracter = cadena[i];
			Push (e, &p);
		}
		if (cadena[i] == ')'){
			if(IsEmpty(&p)){
				Destroy(&p);
				return 0;
			}else{
				Pop (&p);
			}
		}
	}
	if(IsEmpty(&p)){
		Destroy(&p);
		return 1;
	}else{
		Destroy(&p);
		return -1;
	}
	
}

/*	Dado un caracter, esta funcion retornara su correspondiente 
 *	posicion
 *	A = 0, B = 1, ..., Z = 25 
 */
int hash (char c){ return c - 'A'; }

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
void ConvierteInfijaAPostFija(char * expresion_infija, char * expresion_postfija, boolean * variables_introducidas){
	
}

/*
Descripción: Evalua el resultado numérico de una expresión
en su forma postfija, dados los valores de sus incógnitas
Recibe: char * postfija (expresión en su forma
postfija), double * valores (arreglo con los
valores numéricos de todas las incógnitas)
Devuelve: double (la evaluación de la expresión)
*/

double EvaluaExpresionPostFija (char *postfija, double *valores){
	int i = 0, lim = strlen (postfija);
	elemento e;
	pila p;
	double primero, segundo;

	Initialize (&p);
	
	for (i = 0; i < lim; i++){
		if (EsCaracter (postfija[i])){
			e.doble = valores[hash (postfija[i])];
			Push (e, &p);
		}
		else if(EsOperador (postfija[i])){
			segundo = Pop (&p).doble;
			primero = Pop (&p).doble;
			switch (postfija[i]){
				case '+':
					e.doble = primero + segundo;
					break;
				case '-':
					e.doble = primero - segundo;
					break;
				case '*': 
					e.doble = primero * segundo;
					break;
				case '/': 
					e.doble = primero / segundo;
					break;
				case '^': 
					e.doble = pow(primero, segundo);
					break;
			}
			Push (e, &p);
		}
	}
	e = Pop(&p);
	Destroy (&p);
	return e.doble;
} 

//PROGRAMA PRINCIPAL
int main(){
	//Cadenas para guardar la expresión en su forma infija y postfija
	char expresion_infija[101];
	char expresion_postfija[101];
	
	//Arreglo de booleanos para marcar las variables que están contenidas en la expresión
	boolean variables_introducidas[26];
	
	//Arreglo de dobles para almacenar los valores de las variables de la expresion
	double valores_variables[26];
	
	//Entero que almacena el estado de la verificación de los paréntesis de la expresión infija
	int VerificacionParentesis;
	
	//El valor numérico luego de evaluar la expresión postfija con los valores numéricos
	double resultado;

	//Inicializamos el arreglo de variables introducidas a FALSE
	int i;
	for(i = 0; i < 26; i++)
		variables_introducidas[i] = FALSE;
	
	//Leemos la expresión infija
	printf("Introduce una expresion infija:\n");
	scanf("%s", expresion_infija);
	
	//Verificamos los paréntesis de la expresión infija
	VerificacionParentesis = VerificarParentesis(expresion_infija);
	
	if(VerificacionParentesis == 1){ //Expresión correcta
		//Convertimos la expresión en su forma infija a postfija
		ConvierteInfijaAPostFija(expresion_infija, expresion_postfija, variables_introducidas);
		
		//Leemos las diferentes variables contenidas en la expresión
		printf("\nLa expresion introducida es correcta, y su equivalente en postfijo es:\n%s\n\nAhora, introduce los valores numericos de cada una de las variables:\n", expresion_postfija);
		for(i = 0; i < 26; i++){
			if(variables_introducidas[i] == TRUE){
				printf("Valor de %c: ", i + 'A');
				scanf("%lf", &valores_variables[i]);
			}
		}
		
		//Evaluamos la expresión de acuerdo a los valores numéricos de las variables
		resultado = EvaluaExpresionPostFija(expresion_postfija, valores_variables);
		
		//Mostramos la evaluación
		printf("El resultado de la expresion es: %f\n", resultado);
	}else if(VerificacionParentesis == 0){ //Hay un parentesis que cierra pero nunca abre
		printf("\nExpresion incorrecta, hay un parentesis que cierra pero nunca abre.\n");
	}else{ //Hay un parentesis que abre pero nunca cerró
		printf("\nExpresion incorrecta, hay un parentesis que abre pero nunca cerro.\n");
	}
	return 0; //Terminamos
}
