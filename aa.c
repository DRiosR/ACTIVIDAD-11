#include <stdio.h>

struct registro {
    int numero_persona;
    // Agrega otros campos de la estructura aquí
};

void ordenar(struct registro personas[], int numero_persona) {
    for (int i = 0; i < numero_persona - 1; i++) {
        for (int j = i + 1; j < numero_persona; j++) {
            if (personas[j].numero_persona < personas[i].numero_persona) {
                // Intercambia directamente los elementos
                struct registro temp = personas[i];
                personas[i] = personas[j];
                personas[j] = temp;
            }
        }
    }
}

int main() {
    struct registro personas[] = {
        {3},  // Reemplaza estos valores con los datos reales
        {1},
        {2},
        // Agrega más estructuras aquí
    };

    int numero_persona = sizeof(personas) / sizeof(personas[0]);

    printf("Arreglo desordenado:\n");
    for (int i = 0; i < numero_persona; i++) {
        printf("%d ", personas[i].numero_persona);
    }

    ordenar(personas, numero_persona);

    printf("\nArreglo ordenado:\n");
    for (int i = 0; i < numero_persona; i++) {
        printf("%d ", personas[i].numero_persona);
    }

    return 0;
}
