//Mariana Graciela Gallardo Garibay
#include <stdio.h> // es el archivo de cabecera que contiene las definiciones de las macros, las constantes, las declaraciones de funciones de la biblioteca estándar del lenguaje de programación C para hacer operaciones, estándar, de entrada y salida, así como la definición de tipos necesarias para dichas operaciones
#include <stdlib.h> //Contiene los prototipos de funciones de C para gestión de memoria dinámica, control de procesos y otras
#include <conio.h> //Esta cabecera declara varias funciones útiles para mejorar el rendimiento de la «entrada y salida por consola» desde un programa
#define desplazamiento(n) ((n - 1)*sizeof(Articulo)) //definición de una macro que depende de n y de artículo
FILE *fix; //apuntador de tipo FILE llamado fix
FILE *findices; //apuntadir de tipo FILE llamado findices
int numReg = 0; //entero inicializado en 0
typedef struct //definición de estructura
{
char nombre[21]; //vector cadena de 21 "nombre"
char identificador[14]; //vector de cadenas "identificador" 
double precio; //precio almacena números con decimales
int unidades; //entero 
int estado; //entero
} Articulo; //nombre de la estructura
typedef struct //definicion de la estructura
{char nombre[21]; //vector cadena de 21 "nombre"
long posicion; //acepta tamaños grandes de caracteres
} Indice; //nombre de la estructura


