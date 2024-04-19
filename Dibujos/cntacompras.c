#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "Dibujos.h"

	void main()
	{
		Local l;
		int compras[3] = {0,0,0};

		pf = fopen(archivo, "rb");
		if (pf == NULL)
		{
			puts("No se puede leer el archivo.");
			exit(-1);
		}

		fread(&d, sizeof(Local),1, pf);
		while (!feof(pf))
		{
			compras[0] += l.dib1;
			compras[1] += l.dib2;
			compras[2] += l.dib3;
			fread(&d, sizeof(Local),1, pf);
		}
		fclose(pf);

		puts("\n\tNUMERO DE PINTURAS COMPRADAS\n");
		printf (" %s %ld: \n", l.opcion1, compras[0]);
		printf (" %s %ld: \n", l.opcion2, compras[1]);
		printf (" %s %ld: \n", l.opcion3, compras[2]);

	}

