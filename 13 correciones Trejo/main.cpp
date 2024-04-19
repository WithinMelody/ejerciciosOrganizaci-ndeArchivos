#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define true 1
#define false 0

typedef struct {
    int codigo;
    char nombre[1000];
    float precio;
    int unidades;
    int alerta;
} Refaccion;
Refaccion piezas[1000];
int registros = 0;
char dato[1000];

void merge(Refaccion *v, int i, int m, int f);
void mergesort(Refaccion *v, int i, int f) {
 if(i!=f) {
  int m = (i+f)/2;
  mergesort(v, i, m);
  mergesort(v, m+1, f);
  merge(v, i, m, f);
 }
}
void merge(Refaccion *v, int i, int m, int f)
{
    Refaccion *aux = new Refaccion[m-i+1];
    for(int j=i; j<=m; j++)
        aux[j-i] = v[j];

    int c1=0, c2=m+1;
    for(int j=i; j<=f; j++)
    {
        if(aux[c1].codigo < v[c2].codigo)
        {
            v[j] = aux[c1++];
            if(c1==m-i+1)
                for(int k=c2; k<=f; k++)
                    v[++j] = v[k];
        }
        else
        {
            v[j] = v[c2++];
            if(c2==f+1)
                for(int k=c1; k<=m-i; k++)
                    v[++j] = aux[k];
        }
    }
}
void guardarenArchivo()
{
    int registrosAuxiliares = 0;
    Refaccion piezasAux[1000];
    if(registros>0)
        mergesort(piezas, 0, registros-1);
    FILE *archivo;
    Refaccion pieza;
    archivo=fopen("auxiliar.dat","wb");
    if (archivo==NULL)
    {
        printf("Error fatal: No se pudo crear el archivo.\n");
        exit(1);
    }
    else
    {
        for(int i = 0; i<=registros-1; i++)
        {
            if(piezas[i].codigo!=-1){
                pieza = piezas[i];
                piezasAux[registrosAuxiliares]=piezas[i];
                fwrite(&pieza, sizeof(Refaccion), 1, archivo);
                registrosAuxiliares++;
            }
        }
        registros = registrosAuxiliares;
        for(int i = 0; i<=registros-1;i++){
            piezas[i]=piezasAux[i];
        }
    }
    fclose(archivo);
    if(remove("piezas.dat")!=0)
        printf("No se pudo eliminar el archivo\n");
    if(rename("auxiliar.dat","piezas.dat")!=0)
        printf("No se pudo renombrar el archivo\n");
}
void continuar()
{
    char opcion;
    printf("Presione enter para continuar\n\n");
    do{
        opcion = getch();
    }while(opcion!=13);
}

void recuperarRefacciones(){
    FILE *archivo;
    Refaccion pieza;
    archivo=fopen("piezas.dat","rb");
    if (archivo!=NULL)
    {
        fread(&pieza, sizeof(Refaccion), 1, archivo);
        while(!feof(archivo))
        {
            piezas[registros] = pieza;
            registros++;
            fread(&pieza, sizeof(Refaccion), 1, archivo);
        }
        printf("registros: %i\n",registros);
        printf("Datos recuperados exitosamente.\n");
    }
    fclose(archivo);
    continuar();
}
void imprimirRefacciones(){
    printf("Inventario de piezas registradas:\n");
    for(int i=0;i<=registros-1;i++){
        printf("Codigo: %i Nombre: %s Precio: %0.2f Piezas disponibles: %i Minimo de piezas: %i\n", piezas[i].codigo, piezas[i].nombre, piezas[i].precio, piezas[i].unidades, piezas[i].alerta);
    }
    guardarenArchivo();
    continuar();
}

int validarClave()
{
    int tam = 0;
    int validarNumero;
    if(dato[0] == NULL){
        printf("Debes introducir un codigo de maximo 5 digitos.\n");
        return false;
    }
    tam = strlen(dato);
    if(tam>5)
    {
        printf("El codigo del pieza deber tener maximo 5 numeros.\n");
        return false;
    }
    for(int i=0; i<tam; i++)
    {
        validarNumero = false;
        for(int j=48; j<=57; j++)
        {
            if(dato[i]==j)
            {
                validarNumero = true;
                break;
            }
        }
        if(validarNumero==false)
        {
            printf("El codigo de la pieza debe contener solo numeros.\n");
            return false;
        }
    }
    for(int i=0;i<=registros-1;i++){
        if(atoi(dato)==piezas[i].codigo){
            printf("El codigo ingresado ya existe en el sistema.\n");
            return false;
        }
    }
    return true;
}
void crear()
{
    FILE *archivo;
    archivo=fopen("piezas.dat","rb");
    if (archivo==NULL)
    {
        fclose(archivo);
        archivo=fopen("piezas.dat","wb");
        if (archivo==NULL){
            printf("Error fatal: No se pudo crear el archivo.\n");
            exit(1);
        }else{
            printf("Archivo creado correctamente.\n");
        }
    }
    fclose(archivo);
}
int validarDato(int esEntero){
    int tam = 0;
    int validarNumero;
    int puntos = 0;
    if(dato[0] == NULL){
        printf("Este dato no puede quedar vacio.\n");
        return false;
    }
    tam = strlen(dato);
    if(tam>5)
    {
        printf("El dato es mayor al soportado.\n");
        return false;
    }
    for(int i=0; i<tam; i++)
    {
        validarNumero = false;
        for(int j=48; j<=57; j++)
        {
            if(dato[i]==j){
                validarNumero = true;
                break;
            }
            else
            {
                if(esEntero==false)
                {
                    if(dato[i]==46){
                        puntos++;
                        if(puntos<=1){
                            validarNumero = true;
                            break;
                        }
                    }
                }
            }
        }
        if(validarNumero==false)
        {
            printf("El dato debe ser un numero positivo.\n");
            return false;
        }
    }
    return true;
}
void pedirDato(char * mensaje)
{
    memset(dato,1000,'\n');
    printf("%s", mensaje);
    fflush(stdin);
    gets(dato);
}
void Altas(){
    Refaccion pieza;
    char op;
    do{
	
    do
    {
        memset(dato,1000,'\n');
        printf("Ingrese el codigo de la pieza:");
        gets (dato); //imprime en pantalla el identificador
    }
    while(validarClave()==false);
    pieza.codigo = atoi(dato);
    do
    {
        pedirDato("Ingrese el nombre de la pieza:");
    }while(dato[0]==NULL);
    strcpy(pieza.nombre, dato);
    do
    {
        pedirDato("Ingrese precio:");
    }while(validarDato(false)==false);
    pieza.precio = atof(dato);
    do
    {
        pedirDato("Ingrese numero de piezas disponibles:");
    }while(validarDato(true)==false);
    pieza.unidades = atoi(dato);
    do
    {
        pedirDato("Ingrese minimo de piezas:");
    }while(validarDato(true)==false);
    pieza.alerta = atoi(dato);
    
    piezas[registros]=pieza;
    registros++;
    guardarenArchivo();
    
     printf("Desea agregar otra pieza? S/N: ");
    do{
        op = getch();
    }while(op!='S'&&op!='s'&&op!='N'&&op!='n');
    printf("\n");
    }while(op!='N'&&op!='n');

    
    continuar();
}
void consultar(int cod,int accion){
    int existe=0;
    for(int i=0;i<=registros-1;i++){
        if(piezas[i].codigo==cod){
            existe=1;
            printf("Codigo: %i Nombre: %s Precio: %0.2f Piezas disponibles: %i Minimo de piezas: %i\n", piezas[i].codigo, piezas[i].nombre, piezas[i].precio, piezas[i].unidades, piezas[i].alerta);
        break;
        }
    }
    if (existe==0){
        if(accion== true)
            printf("No existe una pieza con dicho codigo\n");
    }
    guardarenArchivo();
    if(accion==true)
        continuar();
}
void modificar()
{
    char op;
    do{
    int cod;
    char opcion;
    do
    {
        pedirDato("Ingrese el codigo de la pieza a modificar:");
    }
    while(validarDato(true)==false);
    cod = atoi(dato);
    Refaccion pieza;
    int existe=0;
    for(int i=0; i<=registros-1; i++)
    {
        if (cod==piezas[i].codigo)
        {
            do
            {
                system("cls");
                printf("Codigo: %i Nombre: %s Precio: %0.2f Piezas disponibles: %i Minimo de piezas: %i\n", piezas[i].codigo, piezas[i].nombre, piezas[i].precio, piezas[i].unidades, piezas[i].alerta);
                printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
                printf("°°°°°°°°°°°°°°°°°°° Modificar °°°°°°°°°°°°°°°°°°°\n");
                printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
                printf("° 1 - Nombre.                                   °\n");
                printf("° 2 - Precio.                                   °\n");
                printf("° 3 - Piezas disponibles.                       °\n");
                printf("° 4 - Minimo de piezas    						°\n");
                printf("° 5 - Todo.                                     °\n");
                printf("° 6 - Salir.                                    °\n");
                printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
                printf("Ingrese su opcion: ");
                opcion=getch();
                printf("\n");
                if(opcion=='1'||opcion=='5')
                {
                    do
                    {
                        pedirDato("Ingrese el nombre de la pieza:");
                    }
                    while(dato[0]==NULL);
                    strcpy(piezas[i].nombre, dato);
                }
                if(opcion=='2'||opcion=='5')
                {
                    do
                    {
                        pedirDato("Ingrese precio:");
                    }
                    while(validarDato(false)==false);
                    piezas[i].precio = atof(dato);
                }
                if(opcion=='3'||opcion=='5')
                {
                    do
                    {
                        pedirDato("Ingrese nuevo numero de piezas disponibles:");
                    }
                    while(validarDato(true)==false);
                    piezas[i].unidades = atoi(dato);
                }
                if(opcion=='4'||opcion=='5')
                {
                    do
                    {
                        pedirDato("Ingrese cantidad minima para la pieza:");
                    }
                    while(validarDato(true)==false);
                    piezas[i].alerta = atoi(dato);
                }

                printf("Se modificaron los datos de la pieza.\n");
                existe=1;
                guardarenArchivo();
                continuar();
            }
            while (opcion != '6');
            break;
        }
    }
    if (existe==0){
            printf("No existe una pieza con dicho codigo\n");
        continuar();
    }
    printf("Desea modificar otra pieza? S/N: ");
    do{
        op = getch();
    }while(op!='S'&&op!='s'&&op!='N'&&op!='n');
    printf("\n");
    }while(op!='N'&&op!='n');
}

void eliminar()
{
    int cod;
    do
    {
        pedirDato("Ingrese el codigo de la pieza a eliminar:");
    }
    while(validarDato(true)==false);
    cod = atoi(dato);
    Refaccion pieza;
    int existe=0;
    for(int i=0; i <= registros-1; i++)
    {
        if (cod==piezas[i].codigo)
        {
            printf("Información de la pieza a eliminar: \n");
            printf("Codigo: %i Nombre: %s Precio: %0.2f Piezas disponibles: %i Minimo de piezas: %i\n", piezas[i].codigo, piezas[i].nombre, piezas[i].precio, piezas[i].unidades, piezas[i].alerta);
            printf("Desea continuar con la baja del producto? Presione s para confirmar: ");
            char opcion;
            opcion = getch();
            printf("\n");
            if(opcion == 'S' || opcion == 's')
            {
                piezas[i].codigo = -1;
                printf("Pieza eliminada satisfactoriamente.\n");
            }
            else
            {
                printf("Baja cancelada.\n");
            }
            guardarenArchivo();
            existe=1;
            break;
        }
    }
    if (existe==0)
        printf("No existe una pieza con dicho codigo\n");
    continuar();
}
void servicios(int esPrestamo)
{
    int cod, cantidad;
    do
    {
        pedirDato("Ingrese el codigo de la pieza:");
    }
    while(validarDato(true)==false);
    cod = atoi(dato);
    Refaccion pieza;
    int existe=0;
    for(int i=0; i<=registros-1; i++)
    {
        if (cod==piezas[i].codigo)
        {
            printf("Codigo: %i Nombre: %s Precio: %0.2f Piezas disponibles: %i Minimo de piezas: %i\n", piezas[i].codigo, piezas[i].nombre, piezas[i].precio, piezas[i].unidades, piezas[i].alerta);
            int esValido;
            do{
                esValido = true;
            do
            {
                if(esPrestamo==true)
                {
                    pedirDato("Ingrese numero de piezas a prestar:");
                }
                else
                {
                    pedirDato("Ingrese numero de piezas a devolver:");
                }
            }
            while(validarDato(true)==false);
            cantidad = atoi(dato);
            if(esPrestamo==true)
            {

                if(cantidad > piezas[i].unidades){
                    printf("No se puede prestar esa cantidad de piezas.\n");
                    esValido = false;
                }

                else
                {
                    piezas[i].unidades = piezas[i].unidades - cantidad;
                    printf("Prestamo realizado.\n");
                }
            }
            else
            {
                piezas[i].unidades = piezas[i].unidades + cantidad;
                printf("Devolucion realizada.\n");
            }
            existe=1;
            }while(esValido==false);

    guardarenArchivo();
    continuar();
            break;
        }
    }
    if (existe==0)
        printf("No existe una pieza con dicho codigo\n");
}
void escasez()
{
    int imprimir=false;
    system("cls");
    for(int i=0; i<=registros-1; i++)
    {
        if(piezas[i].unidades<=piezas[i].alerta)
        {
            if(imprimir==false)
            {
                printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
                printf("°°°°°°°°°°°°°°°°°°°° Aviso °°°°°°°°°°°°°°°°°°°°°°\n");
                printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
                printf("Piezas por agotarse: \n");
                imprimir=true;
            }
            printf("Codigo: %i Nombre: %s Precio: %0.2f Piezas disponibles: %i Minimo de piezas: %i\n", piezas[i].codigo, piezas[i].nombre, piezas[i].precio, piezas[i].unidades, piezas[i].alerta);
        }
    }
    if(imprimir==true)
    {
        guardarenArchivo();
    }else{
        printf("No existen piezas por agotarse en este momento!!!\n");
    }
    continuar();
}
void subMenuServicios()
{
    char opcion; //caracter
    do
    {
        system("cls");
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("°°°°°°°°°°°°°°°°°° Servicios °°°°°°°°°°°°°°°°°°°°\n");
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("° 1 - Prestamo                                  °\n");
        printf("° 2 - Devolucion                                °\n");
        printf("° 3 - Salir.                                    °\n");
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("Ingrese su opcion: ");
        fflush(stdin);
        opcion=getch();
        printf("\n");
        switch (opcion)
        {
        case '1':
            servicios(true);
            break;
        case '2':
            servicios(false);
            break;
        default:
            break;
        }
    }
    while (opcion != '3');
}
int main()
{
    char opcion; //caracter
    printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    printf("°°°°°°°°°°°° Laboratorio de Robotica °°°°°°°°°°°°°°°\n");
    printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    printf("°      		 Control de piezas                     °\n");
    printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    crear();
    recuperarRefacciones();
    do
    {
        system("cls");
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("°°°°°°°°°°°°°°°°°°°°°° Menu °°°°°°°°°°°°°°°°°°°°°\n");
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("° 1 - Registrar pieza.                          °\n");
        printf("° 2 - Consultar  informacion de una pieza.      °\n");
        printf("° 3 - Inventario de piezas registradas.         °\n");
        printf("° 4 - Modificar informacion una pieza.          °\n");
        printf("° 5 - Eliminar una pieza.                       °\n");
        printf("° 6 - Servicios de prestamos y devoluciones.    °\n");
        printf("° 7 - Piezas por agotarse.                      °\n");
        printf("° 8 - Salir.                                    °\n");
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("Ingrese su opcion: ");
        opcion=getch();
        printf("\n");
        switch (opcion)
        {
        case '1':
            Altas();
            break;
        case '2':
            int cod;
            do
            {
                pedirDato("Ingrese el codigo de la pieza a consultar:");
            }
            while(validarDato(true)==false);
            cod = atoi(dato);
            consultar(cod,true);
            break;
        case '3':
            imprimirRefacciones();
            break;
        case '4':
            modificar();
            break;
        case '5':
            eliminar();
            break;
        case '6':
            subMenuServicios();
            break;
        case '7':
            escasez();
            break;
        default:
            break;
        }
    }
    while (opcion != '8');
    return 0;
}
