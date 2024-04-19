//Mariana Graciela Gallardo Garibay
#include <stdlib.h> //Contiene los prototipos de funciones de C para gestión de memoria dinámica, control de procesos y otras
#include <stdio.h>// es el archivo de cabecera que contiene las definiciones de las macros, las constantes, las declaraciones de funciones de la biblioteca estándar del lenguaje de programación C para hacer operaciones, estándar, de entrada y salida, así como la definición de tipos necesarias para dichas operaciones
//#include <iostream.h> // es utilizado para operaciones de entrada/salida.
#include <conio.h>//Esta cabecera declara varias funciones útiles para mejorar el rendimiento de la «entrada y salida por consola» desde un programa
#include <ctype.h> //Contiene los prototipos de las funciones y macros para clasificar caracteres. 
#include "articulo.h" //llama al header artículo
#include "indexado.h" //llama al hearder indexado
#define MXAR 200 //define el limite de la variable en 200


Indice tabla[MXAR]; //Tabla de indice toma el valor de MXAR
void escribeTabla(Indice *tab, int nreg); //llama a la función
int main ( ) //menu principal
{
int numReg; //entero
char opcion; //caracter
if ((fix = fopen("mitienda.dat", "rb+")) == NULL) //si el txt en modo de leer binario es nulo
{
fix = fopen("mitienda.dat", "wb+"); //el puntero fix toma el valor de el txt para escribir en binario
findices = fopen("inxtienda.dat", "wb"); //el puntero findices toma el valor del segundo txt para escribir en binario
numReg = 0; //inicializado en 0
}
else /* archivos ya existen. Se vuelcan los índices a tabla */ //segunda condicion
recuperaIndice (tabla, &numReg); //se llama a la funcion
escribeTabla(tabla, numReg); //se llama a la funcion
do //hacer mientras, menú de las opciones
{
puts("1. Alta "); //imprime en pantalla 
puts("2. Baja "); //imprime en pantalla
puts("3. Consulta "); //imprime en pantalla
puts("5. Salir "); //imprime en pantalla
do { //hacer mientras
printf("Elige una opción "); //imprime en pantalla
scanf("%c%*c", &opcion); //lee la variable que se teclea
} while (opcion < '1' || opcion > '5' || opcion =='4'); //compara la opcion teclada mientras sea mayor que 1 o menor que 5 o igual a 4 entra en la condición
switch (opcion) //caso de las opciones
{
case '1': //si opción es uno
Altas(tabla, &numReg); break; //llama a la función, termina la función
case '2': //si opción es dos
Bajas(tabla, &numReg); break; //llama a la función, termina la función
case '3': //si opción es tres
Consulta(tabla, numReg); break; //llama a la función, termina la función
case '5': //si opción es cinco
grabaIndice (tabla, numReg); break; //llama a la función, termina la función
}
} while (opcion != '5'); //mientras la opción sea diferente de 5 
if (fix!= NULL) fclose(fix); //si el puntero es diferente de nulo, se cierra el puntero
}
void escribeTabla(Indice *tab, int nreg) //llama a la función
{
int i = 0; //entero inicializado en 0
if (nreg > 0) //si variable es mayor que 0
{
puts("Tabla de índices actual"); //imrpime en pantalla
for (i < nreg; i++;){ //para i hasta que i sea menor que variable, i va de uno en uno
	printf ("%s %d\n",tabla[i].nombre,tabla[i].posicion); //imprime en pantalla el nombre y la posición
}
system("Pause"); //pausa el sistema
system("cls"); //limpia la pantalla
}
}
