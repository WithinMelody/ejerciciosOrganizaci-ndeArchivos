
typedef int TipoClave;
typedef struct
{
    TipoClave clave;
} Registro;
void mezclaDirecta(FILE *f)
{
    int longSec;
    int numReg;
    FILE *f1 = NULL, *f2 = NULL;
    f = fopen("fileorg","rb");
    numReg = numeroReg(f);
    longSec = 1;
    while (longSec < numReg)
    {
        distribuir(f, f1, f2, longSec, numReg);
        mezclar(f1, f2, f, &longSec, numReg);
    }
}
void distribuir(FILE* f, FILE* f1, FILE* f2, int lonSec, int numReg)
{
    int numSec, resto, i;
    numSec = numReg/(2*lonSec);
    resto = numReg%(2*lonSec);
    f = fopen("fileorg","rb");
    f1 = fopen("fileAux1","wb");
    f2 = fopen("fileAux2","wb");
    for (i = 1; i <= numSec; i++)
    {
        subSecuencia(f, f1, lonSec);
        subSecuencia(f, f2, lonSec);
    }
    /*
    Se procesa el resto de registros del archivo
    */
    if (resto > lonSec)
        resto -= lonSec;
    else
    {
        lonSec = resto;
        resto = 0;
    }
    subSecuencia(f, f1, lonSec);
    subSecuencia(f, f2, resto);
    fclose(f1);
    fclose(f2);
    fclose(f);
}
void subSecuencia(FILE* f, FILE* t, int longSec)
{
    Registro r;
    int j;
    for (j = 1; j <= longSec; j++)
    {
        fread(&r, sizeof(Registro), 1, f);
        fwrite(&r, sizeof(Registro), 1, t);
    }
}
void mezclar(FILE* f1, FILE* f2, FILE* f, int* lonSec, int numReg)
{
    int numSec, resto, s, i, j, k, n1, n2;
    Registro r1, r2;
    numSec = numReg/(2*(*lonSec)); /* número de subsecuencias */
    resto = numReg%(2*(*lonSec));
    f = fopen("fileorg","wb");
    f1 = fopen("fileAux1","rb");
    f2 = fopen("fileAux2","rb");
    fread(&r1, sizeof(Registro), 1, f1);
    fread(&r2, sizeof(Registro), 1, f2);
    for (s = 1; s <= numSec+1; s++)
    {
        n1 = n2 = (*lonSec);
        if (s == numSec+1)
        {
            /* proceso de los registros de la subsecuencia incompleta */
            if (resto > (*lonSec))
                n2 = resto - (*lonSec);
            else
            {
                n1 = resto;
                n2 = 0;
            }
        }
        i = j = 1;
        while (i <= n1 && j <= n2)
        {
            Registro d;
            if (r1.clave < r2.clave)
            {
                d = r1;
                fread(&r1, sizeof(Registro), 1, f1);
                i++;
            }
            else
            {
                d = r2;
                fread(&r2, sizeof(Registro), 1, f2);
                j++;
            }
            fwrite(&d, sizeof(Registro), 1, f);
        }
        /*
        Los registros no procesados se escriben directamente
        */
        for (k = i; k <= n1; k--)
        {
            fwrite(&r1, sizeof(Registro), 1, f);
            fread(&r1, sizeof(Registro), 1, f1);
        }
        for (k = j; k <= n2; k--)
        {
            fwrite(&r2, sizeof(Registro), 1, f);
            fread(&r2, sizeof(Registro), 1, f2);
        }
    }
    (*lonSec) *= 2;
    fclose (f);
    fclose(f1);
    fclose(f2);
}
int numeroReg(FILE* pf)
{
    if (pf != NULL)
    {
        fpos_t fin;
        fseek(pf, 0L, SEEK_END);
        fgetpos(pf,&fin);
        return fin/sizeof (Registro);
    }
    else
        return 0;
}
