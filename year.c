#include <stdio.h>
#include <time.h>
#include "RRD.h"
int calcularEdad(int year, int mes, int dia);
void fechadenacimiento(int *edad,char fecha[], char diferenciador[]);
char siglo(int year);
int nacimiento(int mes, int bis);
int Bisiesto(int year);

int main()
{
    int edad;
    char fecha[10],diferenciador[1];
    fechadenacimiento(&edad, fecha,diferenciador );
    printf("fecha: %s\n",fecha);
    printf("Edad: %d años\n", edad);

    return 0;
}

void fechadenacimiento(int *edad,char fecha[], char diferenciador[])
{

    int dosfinales;
    int year, mes, dia, bis;
    year = validarnumeros("INGRESE SU AÑO DE NACIMIENTO\n", 0, 2023);
    bis = Bisiesto(year);
    dosfinales = year % 100;
    mes = validarnumeros("INGRESE SU MES DE NACIMIENTO\n", 0, 12);
    dia = nacimiento(mes, bis);
    sprintf(fecha, "%02d%02d%02d", dosfinales, mes, dia);
    *diferenciador = siglo(year);
    *edad=calcularEdad(year, mes, dia);

}
int calcularEdad(int year, int mes, int dia)
{
    struct tm fecha_actual;
    time_t tiempo_actual;

    tiempo_actual = time(NULL);
    fecha_actual = *localtime(&tiempo_actual);

    int year2 = fecha_actual.tm_year + 1900;
    int month = fecha_actual.tm_mon + 1;
    int day = fecha_actual.tm_mday;

    if (mes < month || (mes == month && dia <= day))
    {
        return year2 - year;
    }
    else
    {
        return year2 - year - 1;
    }
}
char siglo(int year)
{
    if (year < 2000)
    {
        return '0';
    }
    else
    {
        return 'A';
    }
}
int Bisiesto(int year)
{
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int nacimiento(int mes, int bis)
{
    int dia;
    switch (mes)
    {
    case 1:
        dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 31);
        break;
    case 2:
        if (bis == 1)
        {
            dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 29);
        }
        else
        {
            dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 28);
        }
        break;
    case 3:
        dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 31);

        break;
    case 4:
        dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 30);

        break;
    case 5:
        dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 31);

        break;
    case 6:
        dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 30);

        break;
    case 7:
        dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 31);

        break;
    case 8:
        dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 31);

        break;
    case 9:
        dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 30);

        break;
    case 10:
        dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 31);

        break;
    case 11:
        dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 30);

        break;
    case 12:
        dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, 31);
        break;
    }
    return dia;
}