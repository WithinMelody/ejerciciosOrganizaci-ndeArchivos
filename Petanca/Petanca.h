#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
typedef struct
	{
		char candidato1[41];
		long vot1;
		char candidato2[41];
		long vot2;
		char candidato3[41];
		long vot3;
	} Distrito;

	char* archivo = "Petanca.dat";
	FILE *pf = NULL;

