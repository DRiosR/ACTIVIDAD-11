// RiosRodriguezDaniel 372800
// 12-oct-23
/*
ACTIVIDAD CURP
Realiza un programa que sirva para generar el CURP de una persona.
El programa debe pedir los datos al usuario, generar, almacenar en una cadena y desplegar el CURP.
El programa deberá repetirse cuantas veces desee el usuario
Nota: el programa deberá estar 100% validado, de datos entrada así como las reglas que e deben cuplir al generar el curp
Instructivo:
DATOS PARA PROBAR FUNCIONAMIENTO DE CURP
FRAIRE
LOPEZ
JOSE
OMAR
1997
31
ENERO
HOMBRE
GUERRERO
CURP: FXLO970131HGRRPM02

CHAN
CWEN
2002
MARZO
28
HOMBRE
NACIDO EN EL EXTRANJERO
CURP: CAXC020328HNEHXWA2

DE LA LOMA
XIU
JOSE
ANDRES
2007
DICIEMBRE
28
HOMBRE
YUCATAN
CURP: LOXA071228HYNMXNA3
*/
// R.R.D_act10_1_932
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "RRD.h"

void estados(char abreviacion[]);
void fechadenacimiento(char fecha[], char diferenciador[]);
void nombres(char cuadro1[], char cuadro2[]);
void palabras_incovenientes(char cuadro1[]);
void validarAP(char ApPat[]);
void tresnombre(char parte2[], char nom[], char ap[], char am[]);
void genero(char sexo[]);
char siglo(int year);
int calcularHomoclave(char curp[]);
int nacimiento(int mes, int bis);
int Bisiesto(int year);
void quitarespacio(char palabra[]);
void cambiarene(char entrada[]);

int main()
{
    char curp[] = "0", nombre[5], finalnombre[5], fecha[9], estado[30], sexo[2], diferenciador;
    int validador;
    nombres(nombre, finalnombre);
    fechadenacimiento(fecha, &diferenciador);
    cambiarene(nombre);
    cambiarene(finalnombre);
    estados(estado);
    genero(sexo);
    sprintf(curp, "%s%s%s%s%s%c", nombre, fecha, sexo, estado, finalnombre, diferenciador);
    validador = calcularHomoclave(curp);
    sprintf(curp, "%s%s%s%s%s%c%d", nombre, fecha, sexo, estado, finalnombre, diferenciador, validador);
    printf("CURP=%s", curp);
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
void fechadenacimiento(char fecha[], char diferenciador[])
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
}
void genero(char sexo[])
{
    int num;
    char genero[2][10] = {"H", "M"};
    num = validarnumeros("INGRESE SU GENERO:\n0.-HOMBRE\n1.-MUJER\n", 0, 1);
    strcpy(sexo, genero[num]);
}
void estados(char abreviacion[])
{
    char estado[20];
    int i, encontrado = 0, lugar = -1;
    char estadosMexico[32][30] = {
        "AGUASCALIENTES", "BAJA CALIFORNIA", "BAJA CALIFORNIA SUR", "CAMPECHE", "COAHUILA", "COLIMA", "CHIAPAS",
        "CHIHUAHUA", "CIUDAD DE MEXICO", "DURANGO", "GUANAJUATO", "GUERRERO", "HIDALGO", "JALISCO",
        "ESTADO DE MEXICO", "MICHOACAN", "MORELOS", "NAYARIT", "NUEVO LEON", "OAXACA", "PUEBLA",
        "QUERETARO", "QUINTANA ROO", "SAN LUIS POTOSI", "SINALOA", "SONORA", "TABASCO", "TAMAULIPAS",
        "TLAXCALA", "VERACRUZ", "YUCATAN", "ZACATECAS"};

    char abreviacionesEstadosMexico[32][4] = {
        "AS", "BC", "BS", "CC", "CL", "CM", "CS", "CH", "DF", "DG", "GT", "GR", "HG", "JC",
        "MC", "MN", "MS", "NT", "NL", "OC", "PL", "QT", "QR", "SP", "SL", "SR", "TC", "TS",
        "TL", "VZ", "YN", "ZS"};
    validarletras("INGRESE SU ESTADO: ", estado);

    for (i = 0; i < 32; i++)
    {
        if (strcmp(estado, estadosMexico[i]) == 0)
        {
            encontrado = 1;
            lugar = i;
            i = 32;
        }
    }
    if (encontrado == 1)
    {
        strcpy(abreviacion, abreviacionesEstadosMexico[lugar]);
    }
    else
    {
        strcpy(abreviacion, "NE");
    }
}
void nombres(char cuadro1[], char finalnombre[])
{
    char nom[15], nom2[15], AP[20], AM[20], tem1[20], tem2[15]; // OEDL020826MBCJZZA9
    int segundo, i, j;
    char consonantes[21] = "BCDFGHJKLMNPQRSTVWXYZ";
    validarletras("ESCRIBA SU NOMBRE: ", nom);
    quitarespacio(nom);
    strcpy(tem2, nom);

    segundo = validarnumeros("TIENE SEGUNDO NOMBRE?\n1.-SI\n2.-NO\n", 1, 2);
    if (segundo == 1)
    {
        validarletras("ESCRIBA SU NOMBRE: ", nom2);
    }

    if (strcmp(nom, "MARIA") == 0 || strcmp(nom, "JOSE") == 0)
    {
        strcpy(nom, nom2);
    }

    validarletras("ESCRIBA SU PRIMER APELLIDO: ", AP);
    validarAP(AP);
    quitarespacio(AP);
    strcpy(tem1, AP);

    if (strlen(AP) == 0)
    {
        strcpy(AP, "X");
    }
    validarletras("ESCRIBA SU SEGUNDO APELLIDO: ", AM);
    quitarespacio(AM);
    if (strlen(AM) == 0)
    {
        strcpy(AM, "X");
    }
    for (i = 0; i < 21; i++)
    {
        for (j = 1; AP[j] != '\0'; j++)
        {
            if (AP[j] == consonantes[i])
            {
                AP[j] = AP[j + 1];
                cuadro1[1] = AP[j];
            }
        }
    }
    cuadro1[0] = AP[0];
    cuadro1[1] = AP[1];
    cuadro1[2] = AM[0];
    cuadro1[3] = nom[0];
    cuadro1[4] = '\0';
    if (strcmp(tem2, "MARIA") == 0 || strcmp(tem2, "JOSE") == 0)
    {
        strcpy(tem2, nom2);
    }
    tresnombre(finalnombre, tem1, AM, tem2);

    palabras_incovenientes(cuadro1);
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
