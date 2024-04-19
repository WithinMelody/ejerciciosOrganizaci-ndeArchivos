#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Dibujos.h"
int main()
	{
		Local l;
		int termina;

		pf = fopen(archivo, "ab");
		if (pf == NULL)
		{
			puts("No se puede crear el archivo.");
			exit(-1);
		}

		strcpy(l.opcion1,"Bocetos");
		strcpy(l.opcion2,"Pinturas al oleo");
		strcpy(l.opcion3,"Pinturas en acuarela");

		termina = 0;
		puts("Introducir cuantas veces han sido comprados cada dibujo, termina con 0 0 0");
		do {
			leeRegistro(&l);
			if ((l.dib1 == 0) && (l.dib2 == 0) && (l.dib3 == 0))
			{
				termina = 1;
				puts("Fin del proceso. Se cierra el archivo");
			}
			else
				fwrite(&d, sizeof(Local),1, pf);
		} while (!termina);
		fclose(pf);
	}

	void leeRegistro(Local* l)
	{
		printf ("Número de bocetos %s : ", l -> opcion1);
		scanf("%ld", &(l -> dib1));
		printf ("Número de pinturas al oleo %s : ", l -> opcion2);
		scanf("%ld", &(l -> dib2));
		printf ("Número de pinturas en acuarela %s : ", l -> opcion3);
		scanf("%ld", &(l -> dib3));
	}

