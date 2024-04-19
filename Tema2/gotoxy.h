#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
using namespace std;
void limpiar()
{
    system("cls");
    fflush(stdin);
    cin.clear();
}
void texcolor(int x)
{
    SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),x);
}
void gotoxy(int x, int y)
{
    COORD Cursor_Pos = {x,y};
    SetConsoleCursorPosition(GetStdHandle (STD_OUTPUT_HANDLE), Cursor_Pos);
}
int construirMenu(char *opciones[], int can, int seleccion=2, int X=15, int Y=3)
{
    bool ban=true;
    int i,lim, tecla, opc=seleccion;
    limpiar();
    do
    {
        //-- Buscar la frase más larga --//
        for(lim=i=0; i<can && ban; i++)
        {
            if(strlen(opciones[i])>lim)
                lim=strlen(opciones[i]);
        }
        for(i=Y; i<=(can + Y + 1) && ban; i++)
        {
            gotoxy(X, i);
            //-- Esquinas y lineas verticales del lado izquierdo. --//
            if(i==Y)
                cout<<"É";
            else if(i!=can + Y + 1)
                cout<<"º";
            else
                cout<<"È";
            //-- Lineas horizontales y las opciones.--//
            if(i==Y || i==can + Y + 1)
            {
                for(int j=0; j<lim + 6; j++)
                    cout<<"Í";
            }
            else
            {
                //-- Cambio de Color --//
                if(opc==i- Y)
                    texcolor(4);
                //-- Las letras --//
                if(i- (Y + 1) == 0)
                    gotoxy(X + 1 +(lim + 1 - strlen(opciones[i- (Y + 1)]))/2,i); // Centrado
                else
                    gotoxy(X + 1, i);
                cout<<"   "<<opciones[i- (Y + 1)];
                texcolor(7);
            }
            //-- Esquinas y lineas verticales del lado derecho. --//
            gotoxy(X + lim + 6 + 1, i);
            if(i==Y)
                cout<<"»";
            else if(i!=can + Y + 1)
                cout<<"º";
            else
                cout<<"¼";
        }
        //-- Funciones de reconocer las teclas --//
        if(can==1)
        {
            gotoxy(X, i);
            return 0;
        }
        else
            tecla = getch();
        if(tecla==72)
        {
            if(opc!=2)//-- Flecha Arriba del teclado
                opc--;
            else
                opc=can;
            ban=true;
        }
        else if(tecla==80)  //-- Flecha Abajo del teclado
        {
            if(opc!=can)
                opc++;
            else
                opc=2;
            ban=true;
        }
        else
            ban=false;
    }
    while(tecla!=13);
    return opc - 1;
}
