#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <conio.h>
#include <time.h>

int calcularEdad(int year, int mes, int dia);
void quitarespacio(char palabra[]);
void validarAP(char ApPat[]);
void palabras_incovenientes(char cuadro1[]);
void tresnombre(char parte2[], char ap[], char am[], char nom[]);
int calcularHomoclave(char curp[]);
void cambiarene(char entrada[]);
int Bisiesto(int year);
int nacimientoaleatorios(int mes, int bis);
int generarNumeroAleatorio(int min, int max);


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
void quitarespacio(char palabra[])
{
    char *Apsinespacio = strrchr(palabra, ' ');

    if (Apsinespacio != NULL)
    {
        strcpy(palabra, Apsinespacio + 1);
    }
}
void validarAP(char ApPat[])
{
    int len, i;
    len = strlen(ApPat);
    for (i = 0; i < len - 1; i++)
    {

        if (ApPat[i] == 'F' && ApPat[i + 1] == 'A')
        {
            ApPat[i + 1] = 'X';
        }
        if (ApPat[i] == 'P' && ApPat[i + 1] == 'U')
        {
            ApPat[i + 1] = 'X';
        }
        if (ApPat[i] == 'J' && ApPat[i + 1] == 'O')
        {
            ApPat[i + 1] = 'X';
        }
    }
}
void palabras_incovenientes(char cuadro1[])
{
    int i, encontrado = 0, lugar = -1;

    char palabrasInconvenientes[77][10] = {
        "BACA", "BAKA", "BUEI", "BUEY", "CACA", "CACO", "CAGA", "CAGO", "CAKA", "CAKO", "COGE", "COGI",
        "COJA", "COJE", "COJI", "COJO", "COLA", "CULO", "FALO", "FETO", "GETA", "GUEI", "GUEY", "JETA",
        "JOTO", "KACA", "KACO", "KAGA", "KAGO", "KAKA", "KAKO", "KOGE", "KOGI", "KOJA", "KOJE", "KOJI",
        "KOJO", "KOLA", "KULO", "LOCA", "MAME", "MAMO", "MEAR", "MEAS", "MEON", "MIAR", "MION", "MOCO",
        "MOKO", "MULA", "MULO", "NACA", "NACO", "PEDA", "PEDO", "PENE", "PIPI", "PITO", "POPO", "PUTA",
        "PUTO", "QULO", "RATA", "ROBA", "ROBE", "ROBO", "RUIN", "SENO", "TETA", "VACA", "VAGA", "VAGO",
        "VAKA", "VUEI", "VUEY", "WUEI", "WUEY"};

    char palabrasArregladas[77][10] = {
        "BXCA", "BXKA", "BXEI", "BXEY", "CXCA", "CXCO", "CXGA", "CXGO", "CXKA", "CXKO", "CXGE", "CXGI",
        "CXJA", "CXJE", "CXJI", "CXJO", "CXLA", "CXLO", "FXLO", "FXTO", "GXTA", "GXEI", "GXEY", "JXTA",
        "JXTO", "KXCA", "KXCO", "KXGA", "KXGO", "KXKA", "KXKO", "KXGE", "KXGI", "KXJA", "KXJE", "KXJI",
        "KXJO", "KXLA", "KXLO", "LXCA", "MXME", "MXMO", "MXAR", "MXAS", "MXON", "MXAR", "MXON", "MXCO",
        "MXKO", "MXLA", "MXLO", "NXCA", "NXCO", "PXDA", "PXDO", "PXNE", "PXPI", "PXTO", "PXPO", "PXTA",
        "PXTO", "QXLO", "RXTA", "RXBA", "RXBE", "RXBO", "RXIN", "SXNO", "TXTA", "VXCA", "VXGA", "VXGO",
        "VXKA", "VXEI", "VXEY", "WXEI", "WXEY"};

    for (i = 0; i < 77; i++)
    {
        if (strcmp(cuadro1, palabrasInconvenientes[i]) == 0)
        {
            encontrado = 1;
            lugar = i;
            i = 77;
        }
    }
    if (encontrado == 1)
    {
        strcpy(cuadro1, palabrasArregladas[lugar]);
    }
}
void tresnombre(char parte2[], char ap[], char am[], char nom[])
{
    int enco = 0;
    char Ap = '1', Am = '0', Nom = '0';
    for (int i = 0; ap[i] != '\0'; i++)
    {
        if (ap[0] == 'X')
        {
            Ap = ap[0];
            enco = 1;
            break;
        }
    }
    if (enco == 0)
    {
        for (int i = 1; ap[i] != '\0'; i++)
        {
            if (ap[i] != 'A' && ap[i] != 'E' && ap[i] != 'I' && ap[i] != 'O' && ap[i] != 'U')
            {
                Ap = ap[i];
                break;
            }
        }
    }
    enco = 0;
    for (int i = 0; am[i] != '\0'; i++)
    {
        if (am[0] == 'X')
        {
            Am = am[0];
            enco = 1;
            break;
        }
    }
    if (enco == 0)
    {
        for (int i = 1; am[i] != '\0'; i++)
        {
            if (am[i] != 'A' && am[i] != 'E' && am[i] != 'I' && am[i] != 'O' && am[i] != 'U')
            {

                Am = am[i];
                break;
            }
        }
    }

    for (int i = 1; nom[i] != '\0'; i++)
    {
        if (nom[i] != 'A' && nom[i] != 'E' && nom[i] != 'I' && nom[i] != 'O' && nom[i] != 'U')
        {
            Nom = nom[i];
            break;
        }
    }

    sprintf(parte2, "%c%c%c", Ap, Am, Nom);
}
int calcularHomoclave(char curp[])
{
    int i;
    int nom, ap1, ap2, am, sexo;
    int year1, year2, mes1, mes2, dia1, dia2;
    int esta1, esta2, ap3, am2, nom2, siglo;
    int suma;
    char equivalenciaLetras[] = "0123456789ABCDEFGHIJKLMN OPQRSTUVWXYZ";
    for (i = 0; equivalenciaLetras[i] != '\0'; i++)
    {
        if (curp[0] == equivalenciaLetras[i])
        {
            ap1 = i;
        }
        if (curp[1] == equivalenciaLetras[i])
        {
            ap2 = i;
        }
        if (curp[2] == equivalenciaLetras[i])
        {
            am = i;
        }
        if (curp[3] == equivalenciaLetras[i])
        {
            nom = i;
        }
        if (curp[4] == equivalenciaLetras[i])
        {
            year1 = i;
        }
        if (curp[5] == equivalenciaLetras[i])
        {
            year2 = i;
        }
        if (curp[6] == equivalenciaLetras[i])
        {
            mes1 = i;
        }
        if (curp[7] == equivalenciaLetras[i])
        {
            mes2 = i;
        }
        if (curp[8] == equivalenciaLetras[i])
        {
            dia1 = i;
        }
        if (curp[9] == equivalenciaLetras[i])
        {
            dia2 = i;
        }
        if (curp[10] == equivalenciaLetras[i])
        {
            sexo = i;
        }
        if (curp[11] == equivalenciaLetras[i])
        {
            esta1 = i;
        }
        if (curp[12] == equivalenciaLetras[i])
        {
            esta2 = i;
        }
        if (curp[13] == equivalenciaLetras[i])
        {
            ap3 = i;
        }
        if (curp[14] == equivalenciaLetras[i])
        {
            am2 = i;
        }
        if (curp[15] == equivalenciaLetras[i])
        {
            nom2 = i;
        }
        if (curp[16] == equivalenciaLetras[i])
        {
            siglo = i;
        }
    }

    suma = ((ap1 * 18) + (ap2 * 17) + (am * 16) + (nom * 15) + (year1 * 14) + (year2 * 13) + (mes1 * 12) + (mes2 * 11) + (dia1 * 10) + (dia2 * 9) + (sexo * 8) + (esta1 * 7) + (esta2 * 6) + (ap3 * 5) + (am2 * 4) + (nom2 * 3) + (siglo * 2)) % 10;
    if (suma != 0)
    {
        suma = 10 - suma;
    }
    return suma;
}
void cambiarene(char entrada[])
{
  for (int i = 0; entrada[i] != '\0'; i++)
  {
    if (!(isalnum(entrada[i]) || isalpha(entrada[i])))
    {
      entrada[i] = 'X';
    }
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
int nacimientoaleatorios(int mes, int bis)
{
  int dia;
  switch (mes)
  {
  case 1:
    dia = generarNumeroAleatorio(1, 31);
    break;
  case 2:
    if (bis == 1)
    {
      dia = generarNumeroAleatorio(1, 29);
    }
    else
    {
      dia = generarNumeroAleatorio(1, 28);
    }
    break;
  case 3:
    dia = generarNumeroAleatorio(1, 31);

    break;
  case 4:
    dia = generarNumeroAleatorio(1, 30);

    break;
  case 5:
    dia = generarNumeroAleatorio(1, 31);

    break;
  case 6:
    dia = generarNumeroAleatorio(1, 30);

    break;
  case 7:
    dia = generarNumeroAleatorio(1, 31);

    break;
  case 8:
    dia = generarNumeroAleatorio(1, 30);

    break;
  case 9:
    dia = generarNumeroAleatorio(1, 30);

    break;
  case 10:
    dia = generarNumeroAleatorio(1, 31);

    break;
  case 11:
    dia = generarNumeroAleatorio(1, 31);

    break;
  case 12:
    dia = generarNumeroAleatorio(1, 31);
    break;
  }
  return dia;
}
int generarNumeroAleatorio(int min, int max)
{
  return rand() % (max - min + 1) + min;
}