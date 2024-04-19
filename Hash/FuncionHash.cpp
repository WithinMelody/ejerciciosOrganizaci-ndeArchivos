#include <stdio.h> //es el archivo de cabecera que contiene las definiciones de las macros, las constantes, las declaraciones de funciones de 
//la biblioteca est�ndar del lenguaje de programaci�n C para hacer operaciones, est�ndar, de entrada y salida,
// as� como la definici�n de tipos necesarias para dichas operaciones
#include <stdlib.h> //biblioteca que contiene los prototipos de funciones de C para gesti�n de memoria din�mica, control de procesos, etc.
#include <ctype.h> //biblioteca que contiene los prototipos de las funciones y macros para clasificar caracteres. 
#include <string.h> //biblioteca que contiene la definici�n de macros, constantes, funciones y tipos y algunas operaciones de manipulaci�n de memoria. 
#define principal 199 //variable principal=199
#define total 240 //variable total=240
const char fich [12] = "fichash.dat"; //archivo de caracteres fich es igual al archivo de txt 
FILE *fh = NULL; //crea el archivo fh y tiene valor nilo
typedef struct //creacion de la estructura
{
char codigo [7]; //vector de 7 caracteres con nombre codigo
char autor [41]; //vector de 41 caracteres con nombre autor
char titulo [41]; //vector de 41 caracteres con nombre titulo
} Libro; //estructura llamada libro

#define desplazamiento(n) ((n)*sizeof(Libro)) //desplazamiento de n= n*tama�o de libro
/* prototipo de las funciones */
void creacion (void); //llamado a funcion creacion
void compra (void); /* operaci�n dar de Alta */ //llamado a la funcion compra
void venta (void); /* operaci�n dar de Baja */ //llama a la funcion venta
void consulta (void); //llama a la funcion consulta
void colisiones (Libro lib); //llama a la funcion colisiones
int indexSinonimo (const char c [ ]); //creacion del entero que usa un vector c
int hash(char c [ ]); //creacion del entero que usa un vector c
long transformaClave (const char c [ ]); //variable que recibe tama�os grandes de caracteres
void escribir (Libro lib); //llama a funcion escribir
int main ( ) //menu principal
{
char opcion; //caracter  opcion
/* comprueba si el archivo ya ha sido creado */
fh = fopen (fich, "rb");
if (fh == NULL) //si el archivo no existe
{
puts ("EL ARCHIVO VA A SER CREADO"); //imprime en pantalla
creacion ( ); //llama a la funcion
}
else //si la condicion no se cumple
fh = NULL; //fh es nulo
do //condicion hacer
{
puts ("1. Compra "); //imprime en pantalla
puts ("2. Venta "); //imprime en pantalla
puts ("3. Consulta "); //imprime en pantalla
puts ("4. Salir "); //imprime en pantalla
do { //condicion hacer
printf ("Elige una opci�n "); //imprime en pantalla
scanf ("%c%*c", &opcion); //lee la opcion tecleada y almacena la informacion
} while (opcion < '1' || opcion > '4' || opcion == '4'); //mientras la opcion sea mayor que 1 y menor que 5, o que sea igual a 4
switch (opcion) //caso de opciones
{
case '1': //si la opcion es uno
compra ( );  //llama a la funcion compra
break; //termina la opcion uno
case '2': // si la opcion es dos
venta ( );  //llama a la funcion venta
break; //termina la opcion 2
case '3': //si la opcion es tres
consulta ( ); //llama a la funcion consulta
break; //termina la opcion tres
}
} while (opcion != '4'); //mientras la opcion sea diferente de 5
if (fh != NULL) fclose (fh); //si el archivo es distinto de nulo, se cierra
}
/*
Creaci�n: escribe consecutivamente total registros, todos con el campo c�digo
igual a '*' para indicar que est�n libres.
*/
void creacion (void) //funcion creacion
{
Libro lib; //variable lib de Libro
int i; //entero i
fh = fopen (fich, "wb+"); //fh toma el valor del archivo fich que va a escribir en binario
strcpy (lib.codigo, "*"); //asigna a lib en la parte de codigo, *
for (i = 1; i <= total; i++) //iteracion que va de uno hasta 240, de uno en uno
fwrite (&lib, sizeof (lib), 1, fh); //escribe en lib, de tama�o lib, de uno en uno en el archivo fh
fclose (fh); //cierra el archivo
fh = NULL; //el archivo es nulo
}
/*
Alta de un registro: pide al usuario los campos c�digo, t�tulo y autor. Llama a
la funci�n hash ( ) para obtener la posici�n en la cual leer el registro, si
est� libre graba el nuevo registro. Si est� ocupado busca en el �rea de
colisiones la primera posici�n libre que ser� donde escribe el registro.
*/
void compra (void) //funcion compra
{
Libro lib, libar; //libar y lib de Libro
long posicion; //variable que recibe grandes cantidades de caracteres llamado posicion
if (fh == NULL) fh = fopen (fich, "rb+"); //si el archivo es nulo lo abre para leer en binario
printf ("C�digo: ");
gets (lib.codigo); //imprime en pantalla y muestra el codigo
printf ("Autor: ");
gets (lib.autor); //imprime en pantalla y muestra al autor
printf ("T�tulo: ");
gets (lib.titulo); //imprime en pantalla y muestra el titulo
posicion = hash (lib.codigo); //posicion toma el valor de la funcion hash(lib.codigo)
posicion = desplazamiento(posicion); //posicion toma el valor de la macro desplazamiento de posicion
fseek(fh, posicion, SEEK_SET); //el puntero en el archivo fh se mueve desde el principio hasta la posicion
fread(&libar, sizeof(Libro), 1, fh); //se lee en fh, la variable libbar de tama�o Libro, una vez
if (strcmp(libar.codigo, "*") == 0) /* registro libre */ //si en la variable libar.codigo y * son iguales 
{
fseek(fh, sizeof(Libro), SEEK_CUR); //en el archivo fh se mueve el puntero dada la posicion
fwrite(&lib, sizeof(Libro), 1, fh); //se escribe en el archivo una vez, la variable lib de tama�o Libro
printf("Registro grabado en la direcci�n: %ld\n",posicion); //imprime en pantalla y llama a la variable 
}
else if (strcmp(lib.codigo, libar.codigo) == 0) /* duplicado */ //si lib.codigo es igual a si mismo
{
puts("C�digo repetido, revisar los datos."); //imprime en pantalla
return; //devuelve
}
else //si el if - else if no se cumplen
colisiones(lib); //se llama a la funcion colisiones
fflush(fh); //se limpia el archivo
}
/*
Baja de un registro: pide el c�digo del registro. Se lee el registro cuya
posici�n est� determinada por la funci�n hash ( ). Si los c�digos son iguales,
se da de baja escribiendo '*' en el campo c�digo. En caso contrario se busca en
el �rea de colisiones y se procede igual.
*/
void venta( ) //funcion venta
{
Libro libar; //libar de Libro
char codigo [7], r; //caracter vector de 7 y r
long posicion; // variable que recibe grandes caracteres posicion
if (fh == NULL) fh = fopen(fich, "rb+"); //si el fh es nulo, se abre el txt para leer en binario
printf("C�digo: "); //imprime en pantalla
gets(codigo); //llama e imprime la variable
posicion = hash(codigo); //posicion toma en valor de hash de codigo
posicion = desplazamiento(posicion); //posicion toma el valor de desplazamiento de posicion
fseek(fh, posicion, SEEK_SET); //desde fh se mueve el puntero desde el inicio del archivo hasta la posicion
fread(&libar, sizeof(Libro), 1, fh); //en el archivo fh se lee la variable libar de tama�o libro
if (strcmp(libar.codigo, codigo) != 0) //si la variable libar es diferente de codigo
posicion = indexSinonimo (codigo); //posicion toma el siguiente valor
if (posicion != -1) //si posicion es diferente de -1
{
escribir(libar); //llama a la funcion escribir 
printf("�Son correctos los datos? (S/N): "); //imprime en pantalla
scanf("%c%*c" ,&r); //lee la variable r
if (toupper(r) == 'S') //Convierte en mayusculas la variable R y si es igual a S
{
strcpy(libar. codigo, " *"); //en la variable libar.codigo se le asigna *
fseek(fh, sizeof(Libro), SEEK_CUR);  //desde donde se encuentre el puntero en el archivo se busca del tama�o Libro
fwrite(&libar, sizeof(Libro), 1, fh); //se escribe en el archivo
}
}
else //si no se cumple la priemra condicion
puts("No se encuentra un registro con ese c�digo."); //imprime en pantalla
fflush(fh); //se limpia el archivo
}
/*
Consulta de un registro: pide el c�digo del registro. Se lee el registro cuya
posici�n est� determinada por la funci�n hash ( ). Si los c�digos son iguales
se muestra por pantalla. En caso contrario se busca en el �rea de colisiones.
*/
void consulta( ) //funcion consulta
{
Libro lib; //variable lib de Libro
char codigo[7]; //vector codigo de 7, caracter
long posicion; //variable posicion que puede recibir muchos caracteres
if (fh == NULL) fh = fopen(fich, "rb+"); //si el archivo es nulo se abre el txt para leer en binario
printf("C�digo: ");gets(codigo); //imprime en pantalla, llama a la variable y la muestra
posicion = hash(codigo); //posicion toma el valor de hash
posicion = desplazamiento(posicion); //posicion toma el valor de desplazamiento
fseek(fh, posicion, SEEK_SET); //busca desde el inicio del archivo al puntero
fread(&lib, sizeof(Libro), 1, fh); //lee en el archivo la variable lib
if (strcmp(lib.codigo, codigo) == 0) //si lib es igual a codigo
escribir(lib); //llama a la funcion escribir
else //si la condicion no se cumple
{
int posicion; //entero posicion
posicion = indexSinonimo (codigo); //posicion toma ese valor
if (posicion != -1) //si posicion es diferente de -1
{
fseek(fh, sizeof(Libro), SEEK_CUR); //se busca el puntero desde la posicion en que se encuentre
fread(&lib, sizeof(Libro), 1, fh); //se lee la variable lib
escribir(lib); //llama a la funcion escribir 
}
else //si no se cumplen las anteriores condiciones
puts("No se encuentra un ejemplar con ese c�digo."); //imprime en pantalla
}
}
/*
Inserta en �rea de sin�nimos: busca secuencialmente el primer registro libre
(codigo=='*') para grabar el registro lib.
*/
void colisiones(Libro lib) //funcion colisiones
{
Libro libar; //variable libar de Libro
int pos = desplazamiento(principal); //entero pos toma el valor de desplazamiento
int j = principal; //entero j toma el valor de principa
int encontrado; //entero encontrado
fseek(fh, pos, SEEK_SET); /* se sit�a en �rea de sin�nimos */ //busca el puntero desde posicion inicial
encontrado = 0; //encotrado toma el valor de 0
while ((j < total) && !encontrado) //mientras j sea mayor que total y diferente de encontrado
{
fread(&libar, sizeof(Libro), 1, fh); //se lee libar
j++; //j se aumenta de uno en uno
if (strcmp(libar.codigo ,"*") == 0) /* libre */ //si en libar codigo es igual  a *
{
encontrado = 1; //encontrado vale uno
fseek(fh, sizeof(Libro), SEEK_CUR); //el puntero busca desde donde se encuentra 
fwrite(&lib, sizeof(Libro), 1, fh); //se escribe lib en el archivo
puts("Datos grabados en el �rea de sin�nimos."); //imprime en pantalla
}
}
if (!encontrado) puts("�rea de sin�nimos completa. "); //si encontrado es diferente de 1, imprime en pantalla
fflush(fh); //limpia el archivo
}
/*
B�squeda en �rea de sin�nimos: b�squeda secuencial, por c�digo, de un registro.
Devuelve la posici�n que ocupa, o bien -1 si no se encuentra.
*/
int indexSinonimo (const char c [ ]) //funcion indesSinonimo
{
Libro libar; //variable libar de Libro
int pos = desplazamiento(principal); //entero posicion toma el valor de desplazamiento
int j = principal; //j es igual a principal
int encontrado; //entero encontrado
fseek(fh, pos, SEEK_SET); /* se sit�a en �rea de sin�nimos */ //se busca el puntero desde el inicio del archivo
encontrado = 0; //encontrado vale uno
while ((j < total) && !encontrado) //si j es mayor que total y diferente de encontrado
{
fread(&libar, sizeof(Libro), 1, fh); //se lee del archivo la variable libar
j++; //j aumenta
if (strcmp(libar.codigo, c) == 0) //si libar y c son iguales
encontrado = 1; //encontrado vale 1
}
if (!encontrado) j = -1; //si encontrado es diferente, j vale -1
return j; //regresa el -1
}
/*
Aritm�tica modular: transforma cadena a un entero en el rango [0, principal).
En primer lugar pasa los caracteres del c�digo a may�sculas. A continuaci�n, llama
a la funci�n que convierte la cadena a entero largo. Por �ltimo, aplica el m�dulo
respecto a principal. El m�dulo produce un entero de 0 a principal-1.
*/
int hash(char c [ ]) //funcion hash
{
int i, suma = 0; //entero i, suma vale 0
for (i = 0; i < strlen(c); i++) //para i=0 hasta i que tenga el tama�o de c, va de uno en uno
c[i] = toupper(c[i]); //vector del tama�o i, se transforma en mayusculas
return transformaClave(c) % principal; //regresa la funcion
}
long transformaClave(const char* clave) //funcion transforma clave
{
int j; //entero j
long d; //variable d que recibe gran cantidad de caracteres
d = 0; //d vale 0
for (j = 0; j < strlen(clave); j++) //para j=0 hasta el tama�o de clave, j va de uno en uno
{
d = d * 27 + clave[j]; //d toma el valor de si mismo por 27 mas el vector clave de tama�o j
}
/*
Si d supera el m�ximo entero largo, genera n�mero negativo
*/
if (d < 0) d = -d; //si de es mayor que 0, d es negativo
return d; //regresa el valor de d
}
void escribir(Libro lib) //funcion escribir 
{
printf("C�digo: %s\t", lib.codigo); //imprime en pantalla variable codigo
printf("Autor: %s\t", lib.autor); //imprime en pantalla a la variable autor
printf("T�tulo: %s\n" ,lib.titulo); //imprime en pantalla a la variable titulo
}
