#include <iostream>
#include "Construir.h"
//Crea una portada con universidad, materia y nombre del autor, con tecla enter se manda a llamar a la mezcla directa
using namespace std;

int id=105;
int clave=3;

int main()
{
    if(trabajar(id, clave)==1)
    {
        printf("UAEM\nOrganizacion de Archivos\n%s\n",autora);
        system("pause");
        construir();
    }
    else
    {
        printf("Error Fatal!!!\n");
    }
    return 0;
}
