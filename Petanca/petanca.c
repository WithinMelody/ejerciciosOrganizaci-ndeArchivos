#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Petanca.h"
int main()
	{
		Distrito d;
		int termina;

		pf = fopen(archivo, "ab");
		if (pf == NULL)
		{
			puts("No se puede crear el archivo.");
			exit(-1);
		}

		strcpy(d.candidato1,"Lis Alebuche");
		strcpy(d.candidato2,"Pasionis Cabitorihe");
		strcpy(d.candidato3,"Gulius Martaria");

		termina = 0;
		puts("Introducir los votos de cada candidato, termina con 0 0 0");
		do {
			leeRegistro(&d);
			if ((d.vot1 == 0) && (d.vot2 == 0) && (d.vot3 == 0))
			{
				termina = 1;
				puts("Fin del proceso. Se cierra el archivo");
			}
			else
				fwrite(&d, sizeof(Distrito),1, pf);
		} while (!termina);
		fclose(pf);
	}

	void leeRegistro(Distrito* d)
	{
		printf ("Votos para %s : ", d -> candidato1);
		scanf("%ld", &(d -> vot1));
		printf ("Votos para %s : ", d -> candidato2);
		scanf("%ld", &(d -> vot2));
		printf ("Votos para %s : ", d -> candidato3);
		scanf("%ld", &(d -> vot3));
	}


