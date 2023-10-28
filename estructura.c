#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "RRD.h"

struct curp_registro
{
    char Nombre[20];
    char Nombre2[20];
    char ApPat[20];
    char ApMat[20];
    char Lugar[20];
    char CURP[19];
    int Matricula;
    char Fecha[11];
    int Edad;
    char sexo[10];
};

void pedirdatos(struct curp_registro registros[], int *num_registros);
void datosautomaticos(struct curp_registro registros[], int *num_registros);
int calcularEdad(int year, int mes, int dia);
void quitarespacio(char palabra[]);
void validarAP(char ApPat[]);
void palabras_incovenientes(char cuadro1[]);
void tresnombre(char parte2[], char ap[], char am[], char nom[]);
int calcularHomoclave(char curp[]);
void cambiarene(char entrada[]);
int nacimiento(int mes, int bis);
int Bisiesto(int year);
int generarNumeroAleatorio(int min, int max);
int nacimientoaleatorios(int mes, int bis);
void eliminarregistro(struct curp_registro registros[], int *num_registros);
void imprimir(struct curp_registro registros[], int num_registros);
void ordenar(struct curp_registro registros[], int *num_registros);
void ordenarinseccion(struct curp_registro registros[], int *num_registros);

int main()
{
    struct curp_registro registro[2000];
    int opc, opc2, menu, num_registros = 0;
    do
    {
        menu = 0;
        opc = validarnumeros("\n--MENU--\n1.- Agregar\n2.- Eliminar registro\n3.- Buscar\n4.- Ordenar\n5.- Imprimir\n6.Archivo texto\n0.-salir\n", 0, 6);
        switch (opc)
        {
        case 0:
            system("cls");
            printf("FIN DEL PROGRAMA");
            return 0;
            break;
        case 1:
            opc2 = validarnumeros("\n--MENU--\n1.- MANUAL (1)\n2.- AUTOMATICO (100)\n3.-REGRESAR\n", 1, 3);
            switch (opc2)
            {
            case 1:
                pedirdatos(registro, &num_registros);
                menu = repetir();
                break;
            case 2:
                datosautomaticos(registro, &num_registros);
                menu = repetir();

                break;
            case 3:
                menu = 1;

                break;
            }

            break;
        case 2:
            eliminarregistro(registro, &num_registros);
            menu = repetir();

            break;
        case 3:

            menu = repetir();

            break;
        case 4:
            if (num_registros < 20)
            {
                ordenarinseccion(registro, &num_registros);
                printf("ORDENADO POR METODO DE INSECCION");
            }
            else
            {
                ordenar(registro, &num_registros);
                printf("ORDENADO POR METODO DE SELECCIOM");
            }
            menu = repetir();

            break;
        case 5:
            imprimir(registro, num_registros);
            menu = repetir();

            break;
        case 6:
            menu = repetir();

            break;
        }

    } while (menu == 1);
}
void datosautomaticos(struct curp_registro registros[], int *num_registros)
{
    char hombres[20][10] = {"JUAN", "PEDRO", "CARLOS", "LUIS", "JAVIER", "ANDRES", "ALEJANDRO", "MIGUEL", "JOSE", "ADAN", "JORGE", "GABRIEL", "ROBERTO", "DAVID", "FERNANDO", "RAUL", "EDUARDO", "SERGIO", "ANTONIO", "FRANCISCO"};
    char mujeres[20][10] = {"DANIELA", "LAURA", "ANA", "CARMEN", "SOFIA", "ISABEL", "MARTA", "PAULA", "ELENA", "PATRICIA", "LUCIA", "CLARA", "ROSA", "BEATRIZ", "CAROLINA", "JULIA", "TERESA", "SARA", "IRENE", "ADRIANA"};
    char apellidos_paternos[20][10] = {"BARRIOS", "RODRIGUEZ", "LOPEZ", "PEREZ", "MARTINEZ", "SANCHEZ", "FERNANDEZ", "GONZALEZ", "RAMIREZ", "TORRES", "MARTIN", "JIMENEZ", "RUIZ", "DIAZ", "SOTO", "GOMEZ", "LOZANO", "CASTRO", "HERRERA", "GARCIA"};
    char apellidos_maternos[20][10] = {"SUAREZ", "VILLEGAS", "GUERRERO", "PALACIOS", "FARIAS", "AVILA", "MOLINA", "SALAZAR", "DELGADO", "SANCHEZ", "FLORES", "MORALES", "ROMERO", "OROZCO", "RIVERA", "CASTILLO", "CHAVEZ", "SUAREZ", "VILLEGAS", "GUERRERO"};
    char gener_sexo[2][10] = {"HOMBRE", "MUJER"};
    int i, j, k;

    for (k = 0; k < 100; k++)
    {

        struct curp_registro *registro = &registros[*num_registros];
        char nom[15], nom2[10], AP[20], AM[20];
        int year = 0, mes = 0, dia = 0, edad = 0, numsexo = 0, matricula = 0, lugar = 0;
        char tem1[20], tem2[15];
        char consonantes[21] = "BCDFGHJKLMNPQRSTVWXYZ";
        char fecha[11], diferenciador[] = "0", validadorchar[1], abreviacion[2], cuadro1[5], finalnombre[4], sexo[2], curp[20], date[12];
        int dosfinales, bis, validadorint, numero_nombre2;

        // matricula
        matricula = numerorandom(300000, 400000);
        registro->Matricula = matricula;
        // nombres y apellidos
        numsexo = generarNumeroAleatorio(1, 2);
        strcpy(registro->sexo, gener_sexo[numsexo - 1]);
        if (numsexo == 1)
        {
            strcpy(nom, hombres[rand() % 20]);
            strcpy(registro->Nombre, nom);
            numero_nombre2 = rand() % 2;
            if (numero_nombre2 == 0)
            {
                strcpy(nom2, hombres[rand() % 20]);
                strcpy(registro->Nombre2, nom2);
            }
        }
        else
        {
            strcpy(nom, mujeres[rand() % 20]);
            strcpy(registro->Nombre, nom);
            if (numero_nombre2 == 0)
            {
                strcpy(nom2, mujeres[rand() % 20]);
                strcpy(registro->Nombre2, nom2);
            }
        }
        quitarespacio(nom);
        strcpy(tem2, nom);

        if (strcmp(nom, "MARIA") == 0 || strcmp(nom, "JOSE") == 0)
        {
            strcpy(nom, nom2);
        }
        strcpy(AP, apellidos_paternos[rand() % 20]);
        strcpy(registro->ApPat, AP);
        validarAP(AP);
        quitarespacio(AP);
        strcpy(tem1, AP);
        if (strlen(AP) == 0)
        {
            strcpy(AP, "X");
        }
        strcpy(AM, apellidos_maternos[rand() % 20]);
        strcpy(registro->ApMat, AM);
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
        sprintf(cuadro1, "%c%c%c%c", AP[0], AP[1], AM[0], nom[0]);
        if (strcmp(tem2, "MARIA") == 0 || strcmp(tem2, "JOSE") == 0)
        {
            strcpy(tem2, nom2);
        }
        tresnombre(finalnombre, tem1, AM, tem2);

        palabras_incovenientes(cuadro1);
        // fecha
        year = rand() % (2004 - 1983 + 1) + 1983;
        bis = Bisiesto(year);
        dosfinales = year % 100;
        mes = rand() % 12 + 1;
        dia = nacimientoaleatorios(mes, bis);
        sprintf(fecha, "%02d%02d%02d", dosfinales, mes, dia);
        sprintf(date, "%02d/%02d/%02d", dia, mes, year);
        strcpy(registro->Fecha, date);
        if (year < 2000)
        {
            strcpy(diferenciador, "0");
        }
        else
        {
            strcpy(diferenciador, "A");
        }
        // edad
        edad = calcularEdad(year, mes, dia);
        registro->Edad = edad;
        // sexo
        char genero[2][10] = {"H", "M"};
        strcpy(sexo, genero[numsexo - 1]);
        strcpy(registro->sexo, gener_sexo[numsexo - 1]);
        // lugar
        char estadosMexico[33][30] = {
            "AGUASCALIENTES", "BAJA CALIFORNIA", "BAJA CALIFORNIA SUR", "CAMPECHE", "COAHUILA", "COLIMA", "CHIAPAS",
            "CHIHUAHUA", "CIUDAD DE MEXICO", "DURANGO", "GUANAJUATO", "GUERRERO", "HIDALGO", "JALISCO",
            "ESTADO DE MEXICO", "MICHOACAN", "MORELOS", "NAYARIT", "NUEVO LEON", "OAXACA", "PUEBLA",
            "QUERETARO", "QUINTANA ROO", "SAN LUIS POTOSI", "SINALOA", "SONORA", "TABASCO", "TAMAULIPAS",
            "TLAXCALA", "VERACRUZ", "YUCATAN", "ZACATECAS", "NACIDO EN EL EXTRANJERO"};

        lugar = (rand() % 33) + 1;
        strcpy(registro->Lugar, estadosMexico[lugar - 1]);
        char abreviacionesEstadosMexico[33][4] = {
            "AS", "BC", "BS", "CC", "CL", "CM", "CS", "CH", "DF", "DG", "GT", "GR", "HG", "JC",
            "MC", "MN", "MS", "NT", "NL", "OC", "PL", "QT", "QR", "SP", "SL", "SR", "TC", "TS",
            "TL", "VZ", "YN", "ZS", "NE"};

        strcpy(abreviacion, abreviacionesEstadosMexico[lugar - 1]);
        // curp
        sprintf(curp, "%s%s%s%s%s%s", cuadro1, fecha, sexo, abreviacion, finalnombre, diferenciador);
        validadorint = calcularHomoclave(curp);
        sprintf(validadorchar, "%d", validadorint);
        strcat(curp, validadorchar);
        strcpy(registro->CURP, curp);

        strcpy(registro->CURP, curp);
        (*num_registros)++;
    }
}
void pedirdatos(struct curp_registro registros[], int *num_registros)
{
    struct curp_registro *registro = &registros[*num_registros];
    char nom[15], nom2[10], AP[20], AM[20];
    int year = 0, mes = 0, dia = 0, edad = 0, numsexo = 0, matricula = 0, lugar = 0;
    char tem1[20], tem2[15];
    int i, j;
    char consonantes[21] = "BCDFGHJKLMNPQRSTVWXYZ";
    char fecha[11], diferenciador[] = "0", validadorchar[1], abreviacion[2], cuadro1[5], finalnombre[4], sexo[2], curp[20], date[12];
    int num, dosfinales, bis, validadorint;

    // matricula
    matricula = validarnumeros("INGRESE SU MATRICULA\n", 100000, 400000);
    registro->Matricula = matricula;
    // nombres y apellidos
    validarletras("ESCRIBA SU NOMBRE: ", nom);
    strcpy(registro->Nombre, nom);
    quitarespacio(nom);
    strcpy(tem2, nom);
    num = validarnumeros("TIENE SEGUNDO NOMBRE?\n1.-SI\n2.-NO\n", 1, 2);
    if (num == 1)
    {
        validarletras("ESCRIBA SU NOMBRE: ", nom2);
        strcpy(registro->Nombre2, nom2);
    }
    if (strcmp(nom, "MARIA") == 0 || strcmp(nom, "JOSE") == 0)
    {
        strcpy(nom, nom2);
    }
    validarletras("ESCRIBA SU PRIMER APELLIDO: ", AP);
    strcpy(registro->ApPat, AP);
    validarAP(AP);
    quitarespacio(AP);
    strcpy(tem1, AP);
    if (strlen(AP) == 0)
    {
        strcpy(AP, "X");
    }
    validarletras("ESCRIBA SU SEGUNDO APELLIDO: ", AM);
    strcpy(registro->ApMat, AM);
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
    sprintf(cuadro1, "%c%c%c%c", AP[0], AP[1], AM[0], nom[0]);
    if (strcmp(tem2, "MARIA") == 0 || strcmp(tem2, "JOSE") == 0)
    {
        strcpy(tem2, nom2);
    }
    tresnombre(finalnombre, tem1, AM, tem2);

    palabras_incovenientes(cuadro1);
    // fecha
    year = validarnumeros("INGRESE SU AÑO DE NACIMIENTO\n", 0, 2023);
    bis = Bisiesto(year);
    dosfinales = year % 100;
    mes = validarnumeros("INGRESE SU MES DE NACIMIENTO\n", 0, 12);
    dia = nacimiento(mes, bis);
    sprintf(fecha, "%02d%02d%02d", dosfinales, mes, dia);
    sprintf(date, "%02d/%02d/%02d", dia, mes, year);
    strcpy(registro->Fecha, date);
    if (year < 2000)
    {
        strcpy(diferenciador, "0");
    }
    else
    {
        strcpy(diferenciador, "A");
    }
    // edad
    edad = calcularEdad(year, mes, dia);
    registro->Edad = edad;
    // sexo
    numsexo = validarnumeros("INGRESE SU GENERO:\n1.-HOMBRE\n2.-MUJER\n", 1, 2);
    char gener_sexo[2][10] = {"HOMBRE", "MUJER"};
    char genero[2][10] = {"H", "M"};
    strcpy(sexo, genero[numsexo - 1]);
    strcpy(registro->sexo, gener_sexo[numsexo - 1]);
    // lugar
    printf("+--------+---------------------+--------+--------------------+--------+--------------------+\n");
    printf("| Numero |      Estado         | Numero |      Estado        | Numero |      Estado        |\n");
    printf("+--------+---------------------+--------+--------------------+--------+--------------------+\n");
    printf("|   1    | AGUASCALIENTES      |   12   | GUANAJUATO         |   23   | QUERETARO          |\n");
    printf("|   2    | BAJA CALIFORNIA     |   13   | GUERRERO           |   24   | QUINTANA ROO       |\n");
    printf("|   3    | BAJA CALIFORNIA SUR |   14   | HIDALGO            |   25   | SAN LUIS POTOSI    |\n");
    printf("|   4    | CAMPECHE            |   15   | JALISCO            |   26   | SINALOA            |\n");
    printf("|   5    | CHIAPAS             |   16   | MEXICO             |   27   | SONORA             |\n");
    printf("|   6    | CHIHUAHUA           |   17   | MICHOACAN          |   28   | TABASCO            |\n");
    printf("|   7    | COAHUILA            |   18   | MORELOS            |   29   | TAMAULIPAS         |\n");
    printf("|   8    | COLIMA              |   19   | NAYARIT            |   30   | TLAXCALA           |\n");
    printf("|   9    | CIUDAD DE MEXICO    |   20   | NUEVO LEON         |   31   | VERACRUZ           |\n");
    printf("|  10    | DURANGO             |   21   | OAXACA             |   32   | YUCATAN            |\n");
    printf("|  11    | GUANAJUATO          |   22   | PUEBLA             |   33   | ZACATECAS          |\n");
    printf("|  33    | NACIDO EN EL EXTRA  |   0    |                    |   0    |                    |\n");
    printf("+--------+---------------------+--------+--------------------+--------+--------------------+\n");
    char estadosMexico[33][30] = {
        "AGUASCALIENTES", "BAJA CALIFORNIA", "BAJA CALIFORNIA SUR", "CAMPECHE", "COAHUILA", "COLIMA", "CHIAPAS",
        "CHIHUAHUA", "CIUDAD DE MEXICO", "DURANGO", "GUANAJUATO", "GUERRERO", "HIDALGO", "JALISCO",
        "ESTADO DE MEXICO", "MICHOACAN", "MORELOS", "NAYARIT", "NUEVO LEON", "OAXACA", "PUEBLA",
        "QUERETARO", "QUINTANA ROO", "SAN LUIS POTOSI", "SINALOA", "SONORA", "TABASCO", "TAMAULIPAS",
        "TLAXCALA", "VERACRUZ", "YUCATAN", "ZACATECAS", "NACIDO EN EL EXTRANJERO"};

    lugar = validarnumeros("CUAL ES SU LUGAR DE NACIMIENTO\n", 1, 33);
    strcpy(registro->Lugar, estadosMexico[lugar - 1]);
    char abreviacionesEstadosMexico[33][4] = {
        "AS", "BC", "BS", "CC", "CL", "CM", "CS", "CH", "DF", "DG", "GT", "GR", "HG", "JC",
        "MC", "MN", "MS", "NT", "NL", "OC", "PL", "QT", "QR", "SP", "SL", "SR", "TC", "TS",
        "TL", "VZ", "YN", "ZS", "NE"};

    strcpy(abreviacion, abreviacionesEstadosMexico[lugar - 1]);
    // curp
    sprintf(curp, "%s%s%s%s%s%s", cuadro1, fecha, sexo, abreviacion, finalnombre, diferenciador);
    validadorint = calcularHomoclave(curp);
    sprintf(validadorchar, "%d", validadorint);
    strcat(curp, validadorchar);
    strcpy(registro->CURP, curp);

    strcpy(registro->CURP, curp);
    (*num_registros)++;
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
void imprimir(struct curp_registro registros[], int num_registros)
{
    int i, acu = 1;
    if (num_registros == 0)
    {
        printf("No hay registros para imprimir.\n");
        return;
    }

    printf("Registros almacenados:\n");
    printf("============================\n");

    for (i = 0; i < num_registros; i++)
    {
        printf("Registro %d:\n", i + 1);
        printf("Matricula: %d\n", registros[i].Matricula);
        printf("Nombre: %s\n", registros[i].Nombre);
        printf("Nombre2: %s\n", registros[i].Nombre2);
        printf("Apellido Paterno: %s\n", registros[i].ApPat);
        printf("Apellido Materno: %s\n", registros[i].ApMat);
        printf("Fecha de Nac: %s\n", registros[i].Fecha);
        printf("Edad: %d\n", registros[i].Edad);
        printf("Sexo: %s\n", registros[i].sexo);
        printf("Lugar de Nac: %s\n", registros[i].Lugar);
        printf("CURP: %s\n", registros[i].CURP);
        printf("============================\n");
        if (acu == 40)
        {
            getch();
            acu = 0;
        }
        acu++;
    }
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
void eliminarregistro(struct curp_registro registros[], int *num_registros)
{
    int i, j, matricula, encontrado = 0;
    matricula = validarnumeros("INGRESE LA MATRICULA DEL REGISTRO PARA ELIMINAR SU REGISTRO\n", 0, 400000);
    for (i = 0; i <= *num_registros; i++)
    {
        if (registros[i].Matricula == matricula)
        {
            for (j = i; j <= *num_registros; j++)
            {
                registros[j] = registros[j + 1];
                encontrado = 1;
            }
            (*num_registros)--;
        }
    }
    if (encontrado == 0)
    {
        printf("NO SE ENCONTRO MATRICULA\n");
    }
}
void ordenar(struct curp_registro registros[], int *num_registros)
{
    struct curp_registro temp;
    int i, j;
    for (i = 0; i < *num_registros; i++)
    {
        for (j = 0; j < *num_registros - 1; j++)
        {
            if (registros[j].Matricula > registros[j + 1].Matricula)
            {
                temp = registros[j];
                registros[j] = registros[j + 1];
                registros[j + 1] = temp;
            }
        }
    }
}

void ordenarinseccion(struct curp_registro registros[], int *num_registros)
{
    struct curp_registro temp;
    int i, j;
    for (i = 1; i < *num_registros; i++)
    {
        j = i;
        temp = registros[i];

        while (j > 0 && strcmp(registros[j - 1].Matricula, temp.Matricula) > 0)
        {
            registros[j] = registros[j - 1];
            j--;
        }

        registros[j] = temp;
    }
}