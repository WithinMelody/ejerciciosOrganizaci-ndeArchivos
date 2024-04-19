//Mariana Graciela Gallardo Garibay
#include <stdio.h> // es el archivo de cabecera que contiene las definiciones de las macros, las constantes, las declaraciones de funciones de la biblioteca est�ndar del lenguaje de programaci�n C para hacer operaciones, est�ndar, de entrada y salida, as� como la definici�n de tipos necesarias para dichas operaciones
#include <stdlib.h> //Contiene los prototipos de funciones de C para gesti�n de memoria din�mica, control de procesos y otras
#include <conio.h> //Esta cabecera declara varias funciones �tiles para mejorar el rendimiento de la �entrada y salida por consola� desde un programa
#define desplazamiento(n) ((n - 1)*sizeof(Articulo)) //definici�n de una macro que depende de n y de art�culo
FILE *fix; //apuntador de tipo FILE llamado fix
FILE *findices; //apuntadir de tipo FILE llamado findices
int numReg = 0; //entero inicializado en 0
typedef struct //definici�n de estructura
{
char nombre[21]; //vector cadena de 21 "nombre"
char identificador[14]; //vector de cadenas "identificador" 
double precio; //precio almacena n�meros con decimales
int unidades; //entero 
int estado; //entero
} Articulo; //nombre de la estructura
typedef struct //definicion de la estructura
{char nombre[21]; //vector cadena de 21 "nombre"
long posicion; //acepta tama�os grandes de caracteres
} Indice; //nombre de la estructura


