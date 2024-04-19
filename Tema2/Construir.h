#include <string.h>
#include "gotoxy.h"
#include "Clase_Mezcla_Directa.h"
#include "Menu_Mezcla_Directa.h"
char autora[] = "Mariana Graciela Gallardo Garibay. ";

void construir(){
    Menu_Mezcla_Directa();
}

int trabajar(int id, int clave)
{
    if(autora[34]!=32||strlen(autora)*clave!=id)
    {
        return 0;
    }
    return 1;
}
