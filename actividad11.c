// RiosRodriguezDaniel 372800
// 24-oct-23
/*
PRÁCTICA 11
Realiza el programa que contenga el siguiente menú
M E N Ú
1.- Agregar
  a) manual (1)
 b) Automatico (100)
 c) Reegresar
2.- Eliminar R/egistro
3.- Buscar
4.- Ordenar
5.- Imprimir
6.- Archivo Texto
0.- Salir
El programa deberá poder almacenar en un arreglo (máximo 2,000 registros) los datos para generar el CURP la estructura debe contener 2 estructuras anidadas, nombre y fecha nacimiento y un campo donde se escribirá automáticamente el curp basado en los datos proporcionados
MENÚ DESCRIPCIÓN:
1.- Cargar: Se deberá agregar 100 registros en forma automáticamente y aleatorios (cuidar no se desborde Arreglo)
2.- Eliminar: La búsqueda se realizará por matrícula, Imprimir el registro encontrado en forma de registro y preguntar si quiere eliminar si o no. (Eliminado Lógico x campo status)
3.- Buscar: La búsqueda se realizará por matrícula, el programa deberá ser capaz de realizar la búsqueda secuencial o Binaria según sea el caso. Imprimir el registro encontrado en forma de registro.
4.- Ordenar: La ordenación será por MATRICULA usar función de ordenación más adecuada según sea el caso usar 2 métodos de ordenación y el programa decidirá cuál es el que usará dependiendo del estado y tamaño de registros dentro del arreglo.
Nota: (validar si el arreglo ya está ordenado no volver ordenar por el mismo campo)
5.- Imprimir: El programa deberá imprimir los datos del arreglo (solo registros activos ) en forma de tabla en pantallas de 40 registros y presionando la tecla de continuar en cada uno de los casos.
6.- Archivo de Texto: El programa deberá generar un archivo de texto con los datos del arreglo (solo registros activos ) formatear salida.
NOTA: forma de registro es de la siguiente manera:
 MATRICULA: 300523
 NOMBRE: YAREMI
 NOMBRE2: GHIZETH
 AP PATERNO: GARCIA
 AP MATERNO: GUERRERO
 FECHA NAC: 03-04-2010
 EDAD: 19
 SEXO: MUJER
 LUGAR NAC: BAJA CALIFORNIA SUR
 CURP: GAGY030410MBCRRRA5
NOTA : Librería Propia, Usar funciones, no se permiten variables global
*/
// R.R.D_act11_1_932
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "RRD.h"
#include "CURP.h"
#include <time.h>
#include <conio.h>

struct curp_registro
{
  char Nombre[30];
  char Nombre2[30];
  char ApPat[30];
  char ApMat[30];
  char Lugar[40];
  char CURP[19];
  int Matricula;
  char Fecha[11];
  int Edad;
  char sexo[10];
  int Status;
};

void pedirdatos(struct curp_registro registros[], int *num_registros);
void datosautomaticos(struct curp_registro registros[], int *num_registros);
int nacimiento(int mes, int bis);
void eliminarregistro(struct curp_registro registros[], int *num_registros, int matricula_a_eliminar);
void imprimir(struct curp_registro registros[], int num_registros);
void imprimirELIMINADOS(struct curp_registro registros[], int num_registros);
void ordenar(struct curp_registro registros[], int *num_registros);
int particion(struct curp_registro registros[], int ri, int rs);
void quicksort(struct curp_registro registros[], int ri, int rs);
void ordenarQuickSort(struct curp_registro registros[], int *num_registros);
void buscar(struct curp_registro registros[], int *num_registros);
void texto(struct curp_registro registros[], int num_registros, FILE *fa, char *nombre_archivo);
void eliminarRegistrotexto(struct curp_registro registros[], int *num_registros, FILE *fa, int matricula_a_eliminar, char *nombre_archivo);
int buscar2(struct curp_registro registros[], int *num_registros, int matricula);
void dar_de_alta_registro(struct curp_registro registros[], int *num_registros, int matricula_de_alta);
void agregarRegistroTexto(struct curp_registro registros[], int *num_registros, FILE *fa, int matricula_de_alta, char *nombre_archivo);

int main()
{
  srand(time(NULL));
  struct curp_registro registro[2000];
  FILE *archivo;
  char nombre_archivo[20];
  int opc, opc2, opc3, opc4, menu, num_registros = 0;
  int matricula_a_eliminar, matricula_de_alta, num_matricula = 0, encontrado, ordenado;
  do
  {
    menu = 1;
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
        if (num_registros < 1999)
        {
          pedirdatos(registro, &num_registros);
          ordenado = 1;
        }
        else
        {
          printf("REGISTROS LLENOS");
          getch();
        }
        break;
      case 2:
        if (num_registros < 1999)
        {
          datosautomaticos(registro, &num_registros);
          ordenado = 1;
        }
        else
        {
          printf("REGISTROS LLENOS");
          getch();
        }
        break;
      case 3:
        menu = 1;

        break;
      }

      break;
    case 2:
      if (num_registros > 0)
      {
        opc3 = validarnumeros("\n--MENU--\n1.- DAR DE BAJA (1)\n2.- DAR DE ALTA (100)\n3.-REGRESAR\n", 1, 3);
        switch (opc3)
        {
        case 1:
          matricula_a_eliminar = validarnumeros("INGRESE LA MATRICULA DEL REGISTRO PARA ELIMINAR SU REGISTRO\n", 200000, 400000);
          encontrado = buscar2(registro, &num_registros, matricula_a_eliminar);
          if (encontrado == 1)
          {
            num_matricula = validarnumeros("QUIERES ELIMINAR ESTE REGISTRO?\n1.-SI\n2.-NO\n", 1, 2);
            if (num_matricula == 1)
            {
              eliminarregistro(registro, &num_registros, matricula_a_eliminar);
              eliminarRegistrotexto(registro, &num_registros, archivo, matricula_a_eliminar, nombre_archivo);
              ordenado = 1;
            }
          }
          break;
        case 2:
          matricula_de_alta = validarnumeros("INGRESE LA MATRICULA DEL REGISTRO PARA DAR DE ALTA SU REGISTRO\n", 200000, 400000);
          encontrado = buscar2(registro, &num_registros, matricula_a_eliminar);
          if (encontrado == 1)
          {
            num_matricula = validarnumeros("QUIERES DAR DE ALTA ESTE REGISTRO?\n1.-SI\n2.-NO\n", 1, 2);
            if (num_matricula == 1)
            {
              dar_de_alta_registro(registro, &num_registros, matricula_de_alta);
              eliminarRegistrotexto(registro, &num_registros, archivo, matricula_a_eliminar, nombre_archivo);

              ordenado = 1;
            }
          }
          break;
        case 3:
          menu = 1;

          break;
        }
      }
      else
      {
        printf("No hay registros para eliminar\n");
      }
      break;

    case 3:
      buscar(registro, &num_registros);
      break;
    case 4:
      if (ordenado == 1)
      {
        if (num_registros <= 500)
        {
          ordenar(registro, &num_registros);
          printf("ORDENADO POR METODO DE BURBUJA\n");
        }
        else
        {
          ordenarQuickSort(registro, &num_registros);
          printf("ORDENADO POR METODO QUICKSORT\n");
        }
        ordenado = 0;
      }
      else
      {
        printf("YA ESTA ORDENADO\n");
        getch();
      }
      break;
    case 5:
      if (num_registros > 0)
      {

        opc4 = validarnumeros("\n--MENU--\n1.-REGISTROS DE ALTA (1)\n2.-REGISTROS DADOS DE BAJA (100)\n3.-REGRESAR\n", 1, 3);
        switch (opc4)
        {
        case 1:
          imprimir(registro, num_registros);

          break;

        case 2:
          imprimirELIMINADOS(registro, num_registros);

          break;

        case 3:
          menu = 1;
          break;
        }
      }
      else
      {
        printf("No hay registros para imprimir.\n");
      }
      break;

    case 6:
      printf("INGRESE EL NOMBRE DEL ARCHIVO\n");
      gets(nombre_archivo);
      strcat(nombre_archivo, ".txt");
      archivo = fopen(nombre_archivo, "a");

      texto(registro, num_registros, archivo, nombre_archivo);
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

  for (k = 0; k < 4; k++)
  {
    struct curp_registro *registro = &registros[*num_registros];
    char nom[15], nom2[10], AP[20], AM[20];
    int year = 0, mes = 0, dia = 0, edad = 0, numsexo = 0, matricula = 0, lugar = 0;
    char tem1[20], tem2[15];
    char consonantes[21] = "BCDFGHJKLMNPQRSTVWXYZ";
    char fecha[11], diferenciador[] = "0", validadorchar[1], abreviacion[2], cuadro1[5], finalnombre[4], sexo[2], curp[20], date[12];
    int dosfinales, bis, validadorint, numero_nombre2;

    // matricula
    matricula = numerorandom(200000, 400000);
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
    char estadosMexico[33][40] = {
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
    // status
    registro->Status = 1;
    if (*num_registros > 1999)
    {
      printf("REGISTROS LLENOS");
      k = 100;
    }
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
  matricula = validarnumeros("INGRESE SU MATRICULA\n", 200000, 400000);
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
  year = validarnumeros("INGRESE SU AÑO DE NACIMIENTO\n", 1900, 2023);
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
  printf("+--------+---------------------+--------+---------------------+--------+---------------------+\n");
  printf("| Numero |      Estado         | Numero |      Estado         | Numero |      Estado         |\n");
  printf("+--------+---------------------+--------+---------------------+--------+---------------------+\n");
  printf("|   1    | AGUASCALIENTES      |   12   | GUERRERO            |   23   | QUINTANA ROO        |\n");
  printf("|   2    | BAJA CALIFORNIA     |   13   | HIDALGO             |   24   | SAN LUIS POTOSI     |\n");
  printf("|   3    | BAJA CALIFORNIA SUR |   14   | JALISCO             |   25   | SINALOA             |\n");
  printf("|   4    | CAMPECHE            |   15   | MEXICO              |   26   | SONORA              |\n");
  printf("|   5    | CHIAPAS             |   16   | MICHOACAN           |   27   | TABASCO             |\n");
  printf("|   6    | CHIHUAHUA           |   17   | MORELOS             |   28   | TAMAULIPAS          |\n");
  printf("|   7    | COAHUILA            |   18   | NAYARIT             |   29   | TLAXCALA            |\n");
  printf("|   8    | COLIMA              |   19   | NUEVO LEON          |   30   | VERACRUZ            |\n");
  printf("|   9    | CIUDAD DE MEXICO    |   20   | OAXACA              |   31   | YUCATAN             |\n");
  printf("|  10    | DURANGO             |   21   | PUEBLA              |   32   | ZACATECAS           |\n");
  printf("|  11    | GUANAJUATO          |   22   | QUERETARO           |   33   | NACIDO EN EL EXTRA  |\n");
  printf("+--------+---------------------+--------+---------------------+--------+---------------------+\n");
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
  // status
  registro->Status = 1;

  (*num_registros)++;
}

void imprimir(struct curp_registro registros[], int num_registros)
{
  int i, acu = 1;
  printf("Registros almacenados:\n");
  printf("========================================================================================================================================================================\n");
  printf("|  No. | Matricula |    Nombre    |    Nombre 2   | Apellido Pat.   | Apellido Mat.   | Fecha de Nac. | Edad |  Sexo  |   Lugar de Nacimiento     |        CURP        |\n");
  printf("========================================================================================================================================================================\n");

  for (i = 0; i <= num_registros; i++)
  {
    if (registros[i].Status == 1)
    {
      printf("| %-4d | %-9d | %-12s | %-13s | %-15s | %-15s | %-13s | %-4d | %-6s | %-25s | %-18s |\n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].Nombre2, registros[i].ApPat, registros[i].ApMat, registros[i].Fecha, registros[i].Edad, registros[i].sexo, registros[i].Lugar, registros[i].CURP);
      printf("========================================================================================================================================================================\n");

      if (acu == 40)
      {
        getch();
        acu = 0;
      }
      acu++;
    }
  }
}
void imprimirELIMINADOS(struct curp_registro registros[], int num_registros)
{
  int i, acu = 1;
  int dadoDbaja = 0;
  for (i = 0; i <= num_registros; i++)
  {
    if (registros[i].Status == 0)
    {
      dadoDbaja = 1;
    }
  }

  if (dadoDbaja == 0)
  {
    printf("Registros almacenados:\n");
    printf("========================================================================================================================================================================\n");
    printf("|  No. | Matricula |    Nombre    |    Nombre 2   | Apellido Pat.   | Apellido Mat.   | Fecha de Nac. | Edad |  Sexo  |   Lugar de Nacimiento     |        CURP        |\n");
    printf("========================================================================================================================================================================\n");

    for (i = 0; i <= num_registros; i++)
    {
      if (registros[i].Status == 0)
      {

        printf("| %-4d | %-9d | %-12s | %-13s | %-15s | %-15s | %-13s | %-4d | %-6s | %-25s | %-18s |\n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].Nombre2, registros[i].ApPat, registros[i].ApMat, registros[i].Fecha, registros[i].Edad, registros[i].sexo, registros[i].Lugar, registros[i].CURP);
        printf("========================================================================================================================================================================\n");
        dadoDbaja = 1;
        if (acu == 40)
        {
          getch();
          acu = 0;
        }
        acu++;
      }
    }
  }
  else
  {
    printf("No hay registros dados de baja\n");
  }
}
int nacimiento(int mes, int bis)
{
  int m, dia;
  int day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  m = day[mes];
  if (bis == 1 && mes == 3)
  {
    m = 29;
  }
  if (bis == 0 && mes == 3)
  {
    m = 28;
  }
  dia = validarnumeros("INGRESE SU DIA DE NACIMIENTO\n", 1, m);
  return dia;
}
void eliminarregistro(struct curp_registro registros[], int *num_registros, int matricula_a_eliminar)
{
  int i;
  for (i = 0; i <= *num_registros; i++)
  {
    if (registros[i].Matricula == matricula_a_eliminar)
    {
      if (registros->Status == 1)
      {
        registros[i].Status = 0;
        printf("REGISTRO DADO DE BAJA\n");

        (*num_registros)--;
      }
      else
      {
        printf("EL REGSITRO YA ESTA DADO DE BAJA");
      }
    }
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
int particion(struct curp_registro registros[], int ri, int rs)
{
  int tem2;
  int i, j;

  tem2 = registros[rs].Matricula;
  i = (ri - 1);

  for (j = ri; j < rs; j++)
  {
    if (registros[j].Matricula < tem2)
    {
      i++;
      struct curp_registro temp = registros[i];
      registros[i] = registros[j];
      registros[j] = temp;
    }
  }

  struct curp_registro temp = registros[i + 1];
  registros[i + 1] = registros[rs];
  registros[rs] = temp;

  return (i + 1);
}
void quicksort(struct curp_registro registros[], int ri, int rs)
{
  int pi;
  if (ri < rs)
  {
    pi = particion(registros, ri, rs);

    quicksort(registros, ri, pi - 1);
    quicksort(registros, pi + 1, rs);
  }
}
void ordenarQuickSort(struct curp_registro registros[], int *num_registros)
{
  quicksort(registros, 0, *num_registros - 1);
}
void buscar(struct curp_registro registros[], int *num_registros)
{
  int numero_matricula, encoontrado = 0;
  numero_matricula = validarnumeros("INRESE LA MATRICULA\n", 300000, 400000);

  for (int i = 0; i < *num_registros; i++)
  {
    if (registros[i].Matricula == numero_matricula)
    {
      printf("Registros almacenados:\n");
      printf("========================================================================================================================================================================\n");
      printf("|  No. | Matricula |    Nombre    |    Nombre 2   | Apellido Pat.   | Apellido Mat.   | Fecha de Nac. | Edad |  Sexo  |   Lugar de Nacimiento     |        CURP        |\n");
      printf("========================================================================================================================================================================\n");

      printf("| %-4d | %-9d | %-12s | %-13s | %-15s | %-15s | %-13s | %-4d | %-6s | %-25s | %-18s |\n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].Nombre2, registros[i].ApPat, registros[i].ApMat, registros[i].Fecha, registros[i].Edad, registros[i].sexo, registros[i].Lugar, registros[i].CURP);
      printf("========================================================================================================================================================================\n");

      encoontrado = 1;
    }
  }
  if (encoontrado == 0)
  {
    printf("NO SE ENCONTRO LA MATRICULA\n\n");
  }
}
void texto(struct curp_registro registros[], int num_registros, FILE *fa, char *nombre_archivo)
{

  fa = fopen(nombre_archivo, "w");
  for (int i = 0; i < num_registros; i++)
  {
    if (fa != NULL)
    {
      fprintf(fa, " ");
    }
  }
  if (num_registros == 0)
  {
    fprintf(fa, "No hay registros para imprimir.\n");
    fclose(fa);
    return;
  }

  fprintf(fa, "\nRegistros almacenados:\n");
  fprintf(fa, "========================================================================================================================================================================\n");
  fprintf(fa, "|  No. | Matricula |    Nombre    |    Nombre 2   | Apellido Pat.   | Apellido Mat.   | Fecha de Nac. | Edad |  Sexo  |   Lugar de Nacimiento     |        CURP        |\n");
  fprintf(fa, "========================================================================================================================================================================\n");

  for (int i = 0; i < num_registros; i++)
  {
    fprintf(fa, "| %-4d | %-9d | %-12s | %-13s | %-15s | %-15s | %-13s | %-4d | %-6s | %-25s | %-18s |\n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].Nombre2, registros[i].ApPat, registros[i].ApMat, registros[i].Fecha, registros[i].Edad, registros[i].sexo, registros[i].Lugar, registros[i].CURP);
    fprintf(fa, "========================================================================================================================================================================\n");
  }

  fclose(fa);
}
void eliminarRegistrotexto(struct curp_registro registros[], int *num_registros, FILE *fa, int matricula_a_eliminar, char *nombre_archivo)
{
  fa = fopen(nombre_archivo, "w");
  fprintf(fa, "\nRegistros almacenados:\n");
  fprintf(fa, "========================================================================================================================================================================\n");
  fprintf(fa, "|  No. | Matricula |    Nombre    |    Nombre 2   | Apellido Pat.   | Apellido Mat.   | Fecha de Nac. | Edad |  Sexo  |   Lugar de Nacimiento     |        CURP        |\n");
  fprintf(fa, "========================================================================================================================================================================\n");

  for (int i = 0; i <= *num_registros; i++)
  {
    if (registros[i].Status == 1)
    {
      fprintf(fa, "| %-4d | %-9d | %-12s | %-13s | %-15s | %-15s | %-13s | %-4d | %-6s | %-25s | %-18s |\n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].Nombre2, registros[i].ApPat, registros[i].ApMat, registros[i].Fecha, registros[i].Edad, registros[i].sexo, registros[i].Lugar, registros[i].CURP);
      fprintf(fa, "========================================================================================================================================================================\n");
    }
  }
  fclose(fa);
}
int buscar2(struct curp_registro registros[], int *num_registros, int matricula)
{
  int i;

  for (i = 0; i < *num_registros; i++)
  {
    if (registros[i].Matricula == matricula)
    {
      printf("\nRegistros almacenados:\n");
      printf("========================================================================================================================================================================\n");
      printf("|  No. | Matricula |    Nombre    |    Nombre 2   | Apellido Pat.   | Apellido Mat.   | Fecha de Nac. | Edad |  Sexo  |   Lugar de Nacimiento     |        CURP        |\n");
      printf("========================================================================================================================================================================\n");

      printf("| %-4d | %-9d | %-12s | %-13s | %-15s | %-15s | %-13s | %-4d | %-6s | %-25s | %-18s |\n", i + 1, registros[i].Matricula, registros[i].Nombre, registros[i].Nombre2, registros[i].ApPat, registros[i].ApMat, registros[i].Fecha, registros[i].Edad, registros[i].sexo, registros[i].Lugar, registros[i].CURP);
      printf("========================================================================================================================================================================\n");

      return 1;
    }
  }

  printf("NO SE ENCONTRO LA MATRICULA\n\n");
  return 0;
}
void dar_de_alta_registro(struct curp_registro registros[], int *num_registros, int matricula_de_alta)
{
  int i;
  for (i = 0; i <= *num_registros; i++)
  {
    if (registros[i].Matricula == matricula_de_alta)
    {
      if (registros[i].Status == 0)
      {
        registros[i].Status = 1;
        printf("REGISTRO DADO DE ALTA\n");

        (*num_registros)++;
      }
      else
      {
        printf("EL REGSITRO NO ESTA DADO DE BAJA");
      }
    }
  }
}
