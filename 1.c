/*
Lizeth Barrios Retana 372813
24-oct-23
PRÁCTICA 11
Realiza el programa que contenga el siguiente menú
    MENÚ
    1.- Agregar
    a) manual (1)
    b) Automatico (100)
    c) Reegresar
    2.- Eliminar Registro
    3.- Buscar
    4.- Ordenar
    5.- Imprimir
    6.- Archivo Texto
    0.- Salir
BRL_act11_1_932
*/
#include <stdio.h>
#include "RRD.h"

int main()
{
    int rep, opc;
    do
    {
        rep = 0;
        opc = validarNumeros("Ingrese el numero de lo que desea hacer\n--MENU--\n1.- Agregar\n2.- Eliminar registro\n3.- Buscar\n4.- Ordenar\n5.- Imprimir\n6.Archivo texto\n0.-salir\n", 0, 6);
        switch (opc)
        {
        case 0:
            system("cls");
            printf("FIN DEL PROGRAMA");
            return 0;
            break;
        case 1:
            
            break;
        case 2:

            break;
        case 3:

            break;

        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        }

    } while (!rep);
}
