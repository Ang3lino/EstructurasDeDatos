//LIBRERIA: Cabecera del TAD Pila Estática

//Definiciones de constantes
#define TRUE 1
#define FALSE 0
#define MAX_ELEMENTS 10000

//Definiciones de tipos de dato

//Definimos un boolean modelado como un char
typedef char boolean;

//Definimos un elemento, que dentro puede tener lo que sea
typedef struct{
	int entero;
	char caracter;
	float flotante;
	double doble;
	int x;
	int y;
} elemento;

//Definimos la pila, incluye un arreglo de elementos y el indice del tope
typedef struct{
	elemento A[MAX_ELEMENTS];
	int tope;
} pila;

//Declaración de funciones
void Initialize(pila *p);          //Inicializar pila para su uso normal
void Destroy(pila *p);             //Eliminar la pila
int Size(pila *p);                 //Obtener el número de elementos en la pila
boolean IsEmpty(pila *p);          //Verificar si la pila está vacía
boolean Push(elemento e, pila *p); //Empilar, introducir un elemento a la pila
elemento Pop(pila *p);             //Desempilar, sacar un elemento de la pila
elemento Top(pila *p);             //Consultar el elemento del tope de la pila sin sacarlo
