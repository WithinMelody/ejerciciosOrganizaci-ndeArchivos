#include<stdio.h>
#include<stdlib.h>

#define true 1
#define false 0

typedef struct {
    int codigo;
    char nombre[100];
    float precio;
    int unidades;
} Refaccion;

Refaccion piezas[1000];
int registros = 0;
void recuperarPiezas(){
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
void imprimirPiezas(){
    printf("Inventario de piezas registradas:\n");
    for(int i=0;i<=registros-1;i++){
        printf("Clave: %i Nombre: %s Precio: %0.2f Unidades: %i\n", piezas[i].codigo, piezas[i].nombre, piezas[i].precio, piezas[i].unidades);
    }
    guardarenArchivo();
    continuar();
}
void continuar()
{
    printf("Presione una tecla para continuar\n\n");
    getch();
}
int validarClave(char *clave)
{
    int tam = 0;
    int validarNumero;
    if(clave[0] == NULL){
        printf("Debes introducir un codigo de maximo 10 digitos.\n");
        return false;
    }
    tam = strlen(clave);
    if(tam>10)
    {
        printf("El codigo de la pieza deber tener maximo 10 numeros.\n");
        return false;
    }
    for(int i=0; i<tam; i++)
    {
        validarNumero = false;
        for(int j=48; j<57; j++)
        {
            if(clave[i]==j)
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
        if(atoi(clave)==piezas[i].codigo){
            printf("La clave ingresada ya existe en el sistema.\n");
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
void Altas(){
    Refaccion pieza;
    char clave[100];
    do
    {
        memset(clave,100,'\n');
        printf("Ingrese el codigo de la pieza:");
        gets (clave); //imprime en pantalla el identificador
    }
    while(validarClave(clave)==false);
    pieza.codigo = atoi(clave);
    printf("Ingrese el nombre de la pieza:");
    fflush(stdin);
    gets(pieza.nombre);
    printf("Ingrese el precio:");
    scanf("%f",&pieza.precio);
    printf("Ingrese unidades disponibles:");
    scanf("%i",&pieza.unidades);
    piezas[registros]=pieza;
    registros++;
    guardarenArchivo();
    continuar();
}
void consultar(int cod,int accion){
    int existe=0;
    for(int i=0;i<=registros-1;i++){
        if(piezas[i].codigo==cod){
            existe=1;
            printf("Clave: %i Nombre: %s Precio: %0.2f Unidades: %i\n", piezas[i].codigo, piezas[i].nombre, piezas[i].precio, piezas[i].unidades);
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
void modificar(){
    printf("Ingrese el codigo de la pieza a modificar:");
    int cod;
    scanf("%i", &cod);
    Refaccion pieza;
    int existe=0;
    for(int i=0;i<=registros-1;i++){
        if (cod==piezas[i].codigo)
        {
            printf("Clave: %i Nombre: %s Precio: %0.2f Unidades: %i\n", piezas[i].codigo, piezas[i].nombre, piezas[i].precio, piezas[i].unidades);
            printf("Ingrese el nombre de la pieza:");
            fflush(stdin);
            gets(piezas[i].nombre);
            printf("Ingrese precio:");
            scanf("%f",&piezas[i].precio);
            printf("Ingrese unidades disponibles:");
            scanf("%i",&piezas[i].unidades);
           printf("Se modificaron los datos de la pieza.\n");
           existe=1;
           break;
        }
    }
    if (existe==0)
        printf("No existe una pieza con dicho codigo\n");
    guardarenArchivo();
    continuar();
}

void eliminar(){
    printf("Ingrese el codigo de la pieza a eliminar:");
    int cod;
    scanf("%i", &cod);
    Refaccion pieza;
    int existe=0;
    for(int i=0;i <= registros-1;i++){
        if (cod==piezas[i].codigo)
        {
            printf("Información de la pieza a eliminar: \n");
            printf("Clave: %i Nombre: %s Precio: %0.2f Unidades: %i\n", piezas[i].codigo, piezas[i].nombre, piezas[i].precio, piezas[i].unidades);
           printf("Desea continuar con la baja del producto? Presione s para confirmar: ");
           char op;
           op = getch();
           printf("\n");
           if(op == 'S' || op == 's'){
                piezas[i].codigo = -1;
                printf("Pieza eliminada satisfactoriamente.\n");
           }else{
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
void guardarenArchivo()
{
    int registrosAuxiliares = 0;
    Refaccion piezasAux[1000];
    burbuja(piezas,registros);
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
void burbuja(){
	int i,j;
	Refaccion temp;
	for(i=0;i<registros;i++){
		for(j=0;j<registros-1;j++){
			if (piezas[j].codigo > piezas[j+1].codigo){
    	      	temp = piezas[j];
    			piezas[j] = piezas[j+1];
    			piezas[j+1] = temp;
    		}
		}
	}
}
void ordenar(){
    burbuja(piezas,registros);
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
        printf("Hice esto\n");
        for(int i = 0; i<=registros-1; i++)
        {
            pieza = piezas[i];
            fwrite(&pieza, sizeof(Refaccion), 1, archivo);
        }
    }
    fclose(archivo);
    if(remove("piezas.dat")!=0)
        printf("No se pudo eliminar el archivo\n");
    if(rename("auxiliar.dat","piezas.dat")!=0)
        printf("No se pudo renombrar el archivo\n");
}
void pruebas()
{
    continuar();
}
int main()
{
    char opcion; //caracter
    printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    printf("°°°°°°°°°°°°°°°°°°° Hecho por °°°°°°°°°°°°°°°°°°°\n");
    printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    printf("°       Mariana Graciela Gallardo Garibay       °\n");
    printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
    crear();
    recuperarPiezas();
    do {
        system("cls");
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("°°°°°°°°°°°°°°°°°°°°°° Menu °°°°°°°°°°°°°°°°°°°°°\n");
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("° 1 - Alta de una pieza.                        °\n");
        printf("° 2 - Consulta de una pieza.                    °\n");
        printf("° 3 - Reporte completo de piezas.               °\n");
        printf("° 4 - Modificacion de informacion de una pieza. °\n");
        printf("° 5 - Baja de una pieza.                        °\n");
        printf("° 6 - Salir.                                    °\n");
        printf("°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°°\n");
        printf("Ingrese su opcion: ");
        opcion=getch();
        printf("\n");
        switch (opcion) {
            case '1':Altas();
                   break;
            case '2':
            printf("Ingrese el codigo de la pieza a consultar:");
            int cod;
            scanf("%i", &cod);
            consultar(cod,true);
            break;
        case '3':
            imprimirPiezas();
            break;
            case '4':modificar();
                   break;
            case '5':eliminar();
                   break;
            case '7':pruebas();
        }
    } while (opcion != '6');
    return 0;
}
