#include <stdio.h>
#include <string.h>

struct curp_registro
{
    char matricula[20]; // Agrega el campo de matrícula
    // Otros campos de la estructura si es necesario
};

void ordenarinse(struct curp_registro registros[], int num_registros)
{
    struct curp_registro actual;
    for (int i = 1; i < num_registros; i++)
    {
        int j = i;
        actual = registros[i]; // Copia toda la estructura

        while (j > 0 && strcmp(registros[j - 1].matricula, actual.matricula) > 0)
        {
            registros[j] = registros[j - 1]; // Copia toda la estructura
            j--;
        }

        registros[j] = actual; // Copia toda la estructura
    }
}

int main()
{
    struct curp_registro registros[] = {
        {"7242", /* otros campos si los hay */},
        {"6421", /* otros campos si los hay */},
        {"1234", /* otros campos si los hay */},
        {"9173", /* otros campos si los hay */},
    };
    int num_registros = sizeof(registros) / sizeof(registros[0]);

    printf("Arreglo original:\n");
    for (int i = 0; i < num_registros; i++)
    {
        printf("Matrícula: %s\n", registros[i].matricula);
    }

    ordenarinseccion(registros, num_registros);

    printf("\nArreglo ordenado:\n");
    for (int i = 0; i < num_registros; i++)
    {
        printf("Matrícula: %s\n", registros[i].matricula);
    }
    printf("\n");

    return 0;
}
