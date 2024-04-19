//Mariana Graciela Gallardo Garibay
#include <stdio.h>// es el archivo de cabecera que contiene las definiciones de las macros, las constantes, las declaraciones de funciones de la biblioteca est�ndar del lenguaje de programaci�n C para hacer operaciones, est�ndar, de entrada y salida, as� como la definici�n de tipos necesarias para dichas operaciones
#include <stdlib.h>//Contiene los prototipos de funciones de C para gesti�n de memoria din�mica, control de procesos y otras
#include <conio.h>//Esta cabecera declara varias funciones �tiles para mejorar el rendimiento de la �entrada y salida por consola� desde un programa
#include <string.h>//ontiene la definici�n de macros, constantes, funciones y tipos y algunas operaciones de manipulaci�n de memoria. 

int posicionTabla(Indice *tab, int n, const char* cl) //funcion posici�n tabla con sus parametros
{
int bajo, alto, central; //enteros
bajo = 0; //variable inicializada en 0
alto = n - 1; /* N�mero de claves en la tabla */ //alto depende de (n-1)
while (bajo <= alto) //mientras bajo sea menor o igual a alto
{
central = (bajo + alto)/2; //central es bajo + alto/2
if (strcmp(cl, tab[central].nombre) == 0) //compara las variables, si son iguales
return central; /* encontrado, devuelve posici�n */ 
else if (strcmp(cl, tab[central].nombre) < 0) //segunda condici�n,compara las variables, si son diferentes
alto = central -1; /* ir a sublista inferior */ //alto es igual a central -1
else //tercera condici�n, si no se cumplen ninguna de las dos anteriores
bajo = central + 1; /* ir a sublista superior */ // //bajo es igual a central+1
}
return -1; //regresa -1
}
/*
Inserci�n ordenada. Inserta, manteniendo el orden ascendente, una nueva clave y
la direcci�n del registro.
*/
void inserOrden(Indice *tab, int *totreg, Indice nv) //funcion InserOrden con sus parametros
{
int i, j; //entero i, j
int parada; //entero parada
parada = 0; //parada inicializado en 0
/* busqueda de posici�n de inserci�n, es decir,
el elemento mayor m�s inmediato */
i = 0;//inicializa a i en 0
while (!parada && (i < *totreg)) //mientras para sea diferente de 0 e i sea mayor que el puntero
{
if (strcmp(nv.nombre , tab[i].nombre) < 0) //compara que las variables sean diferentes 
parada = 1; //parada toma el valor de 1
else //segunda condici�n
i++; //i aumenta de uno en uno
}
(*totreg)++; //puntero/variable aumenta de uno en uno
if (parada)
{
/* mueve elementos desde posici�n de inserci�n hasta el final*/
for (j = *totreg -1; j >= i+1; j--) //para j del valor del puntero-1, hasta que j sea mayor que i+1, j se disminuye
{
strcpy(tab[j].nombre, tab[ j-1].nombre);//asigna la primera variable a una posicion anterior
tab[j].posicion = tab[ j-1].posicion; //posicion se reduce en un lugar 
}
}
/* se inserta el �ndice en el "hueco" */
strcpy(tab[i].nombre, nv.nombre); //asigna de la tabla.nombre a la variable nv.nombre
tab[i].posicion = nv.posicion; //el vector toma el valor de la variable 
}
void leeReg(Articulo* at) //funcion leeReg
{
printf(" Nombre del art�culo: "); //imprime en pantalla
gets (at -> nombre); //imprime en pantalla el nombre
printf(" Identificador: "); //imprime en pantalla
gets(at -> identificador);//imprime en pantalla el identificador
printf(" Precio: ");//imprime en pantalla
scanf("%lf", &(at -> precio)); //imprime en pantalla el precio
printf(" Unidades: ");//imprime en pantalla
scanf("%d%*c", &(at -> unidades));//imprime en pantalla las unidades
}
void Altas(Indice* tab, int* nreg) //funci�n Altas con sus parametros
{
Articulo nuevo;//variable nuevo de Articulo
int p; //entero
if (fix == NULL) fix = fopen("mitienda.dat", "rb+");//si el puntero es nulo, se abre el txt para leer en binario
leeReg(&nuevo);//llama a la funcion
nuevo.estado = 1; /* estado del registro: alta */ //la variable toma el valor de 1
/* busca si est� en la tabla de �ndices */
p = posicionTabla(tab, *nreg, nuevo.nombre);
if (p == -1) /* registro nuevo, se graba en el archivo */ //si p es nulo
{
int dsp;//entero
Indice nv; //variable nv de Indice
nv.posicion = dsp = desplazamiento(*nreg +1); //nv toma el valor de desplazamiento
strcpy(nv.nombre, nuevo.nombre); //asigna la informacion de nv a nuevo
inserOrden(tab, nreg, nv); /* inserta e incrementa el n�mero
de registros */
fseek(fix, dsp, SEEK_SET);//busca al puntero fix desde el inicio del archivo
fwrite(&nuevo, sizeof(Articulo), 1, fix); //escribe las variables nuevo del tama�o Articulo en el puntero
}
else //segunda condici�n
puts("Registro ya dado de alta");//imprime en pantalla
}
/*
Elimina entrada. Borra una entrada de la tabla de �ndices moviendo a la
izquierda los �ndices, a partir del �ndice p que se da de baja.
*/
void quitaTabla(Indice *tab, int *totreg, int p)//funci�n con sus parametros
{
int j;//entero j
for (j = p; j < *totreg - 1; j++)//para j con valor de p, hasta que j sea mayor que la variable -1, j aumenta de uno en uno
{
strcpy(tab[j].nombre, tab[j+1].nombre);//asigna la informaci�n de tabj a la la siguiente posicion
tab[j].posicion = tab[j+1].posicion;//la variable aumenta se recorre un espacio
}
(*totreg) --;//disminuye la variable
}
void escribeReg(Articulo a) //funcion con sus parametros
{
printf("Art�culo: ");//imprime en pantalla
printf("%s, %s, precio: %.1f\n", a.nombre, a.identificador, a.precio);//imprime en pantalla, muestra el nombre, identificador y precio
}
void Bajas(Indice* tab, int* nreg) //funcion baja con sus parametros
{
Articulo q; //variable q de Art�culo
char nomArt[21] ;//vector caracter de 21 
int p;//entero p
if (fix == NULL) fix = fopen("mitienda.dat", "rb+");//mientras el puntero sea nulo  se abre para leer en binario
printf("Nombre del art�culo: ");//imprime en pantalla
gets(nomArt);//imprime el nombre del articulp
p = posicionTabla(tab, *nreg, nomArt); //posicion toma el valor de posicion
if (p != -1) /* encontrado en la tabla */ 
{
char r; //caracter r
fseek(fix, tab[p].posicion, SEEK_SET); //desde el inicio del archivo se busca
fread(&q, sizeof(Articulo), 1, fix); //se lee la variable q desde el puntero
escribeReg(q); //llama a la funcion
printf("Pulsa S para confirmar la baja: "); //imprime en pantalla
scanf("%c%*c", &r); //lee el caracter r
if (toupper(r) == 'S') //convierte a mayuscula el caracter y si es S
{
q.estado = 0;//inicializado en 0
fseek(fix,sizeof(Articulo), SEEK_CUR); //busqu�da desde la posici�n actual
fwrite(&q, sizeof(Articulo), 1, fix); //se empieza a escribir en el puntero
quitaTabla(tab, nreg, p);//llama a la funci�n
}
else //segunda condici�n
puts("Acci�n cancelada. "); //imprime en pantalla
}
else //tercera condici�n
puts("No se encuentra un registro con ese c�digo.");//imprime en pantalla
}
void Consulta(Indice* tab, int nreg) //funci�n con sus parametros
{
Articulo q; //variable q de Art�culo
char nomArt[21];//vector caracter de 21 posiciones
int p; //variable p
if (fix == NULL) fix = fopen("mitienda.dat", "rb+");//si el puntero es nulo se abre para leer en binario
printf("Nombre del art�culo: "); //imrpime en pantalla
gets(nomArt); //imprime el nombre del articulo
p = posicionTabla(tab, nreg, nomArt); //p toma el valor de posicion
if (p != -1) /* encontrado en la tabla */ 
{
fseek(fix, tab[p].posicion, SEEK_SET);//se busca desde el inicio del archivo
fread(&q, sizeof(Articulo), 1, fix); //se lee desde el archivo la variable
escribeReg(q); //llama a la funcion
}
else //segunda condicion
puts("No se encuentra un registro con ese c�digo."); //imprime en pantalla
}
void grabaIndice(Indice *tab, int nreg) //funci�n con sus parametros
{
int i; //entero
findices = fopen("inxtienda.dat", "wb");//el puntero se abre para escribir en binario
fwrite(&nreg, sizeof(int), 1, findices); //se escribe el numero de regiones en findices
for (i = 0; i < nreg; i++) //para i=0 hasta que sea mayor que el numero de regiones
fwrite(tab++, sizeof(Indice), 1, findices); //escribe en el archivo
fclose (findices); //cierra el archivo
}
void recuperaIndice(Indice *tab, int *nreg) { //funcion con sus parametros
int i; //entero
findices = fopen("inxtienda.dat", "rb"); //se abre el archivo para leer en binario
fread(nreg, sizeof (int), 1, findices); //se lee el numero de regiones del archivo
for (i = 0; i < *nreg; i++) //desde i=0 hasta que i sea mayor que el puntero
fread(tab++, sizeof (Indice), 1, findices); //se lee informacion del archivo
fclose(findices); //se cierra el archivo
}
