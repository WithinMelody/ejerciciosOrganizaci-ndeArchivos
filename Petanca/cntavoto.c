#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "Petanca.h"

	void main()
	{
		Distrito d;
		int votos[3] = {0,0,0};

		pf = fopen(archivo, "rb");
		if (pf == NULL)
		{
			puts("No se puede leer el archivo.");
			exit(-1);
		}

		fread(&d, sizeof(Distrito),1, pf);
		while (!feof(pf))
		{
			votos[0] += d.vot1;
			votos[1] += d.vot2;
			votos[2] += d.vot3;
			fread(&d, sizeof(Distrito),1, pf);
		}
		fclose(pf);

		puts("\n\tVOTOS DE CADA CANDIDATO\n");
		printf (" %s %ld: \n", d.candidato1, votos[0]);
		printf (" %s %ld: \n", d.candidato2, votos[1]);
		printf (" %s %ld: \n", d.candidato3, votos[2]);

	}

