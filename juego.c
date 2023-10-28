#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROWS 10
#define COLS 10
#define WORD_COUNT 5
#define WORD_MAX_LENGTH 15

char words[WORD_COUNT][WORD_MAX_LENGTH] = {
    "PROGRAMAR",
    "JUEGOS",
    "COMPUTADORA",
    "ENTRETENIMIENTO",
    "APRENDER"
};

char puzzle[ROWS][COLS];

void initializePuzzle() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            puzzle[i][j] = 'A' + rand() % 26; // Llenar con letras aleatorias
        }
    }
}

void placeWord(char word[]) {
    int wordLength = strlen(word);
    int row, col, direction;
    int validPlacement;

    do {
        validPlacement = 1;
        row = rand() % ROWS;
        col = rand() % COLS;
        direction = rand() % 8;

        int r = row, c = col;
        for (int i = 0; i < wordLength; i++) {
            if (r >= ROWS || c >= COLS || puzzle[r][c] != 'A' + word[i] - 'A') {
                validPlacement = 0;
                break;
            }
            r += direction / 3 - 1;
            c += direction % 3 - 1;
        }
    } while (!validPlacement);

    for (int i = 0; i < wordLength; i++) {
        puzzle[row][col] = word[i];
        row += direction / 3 - 1;
        col += direction % 3 - 1;
    }
}

void displayPuzzle() {
    system("clear");  // Limpia la consola (para sistemas Unix o Linux)
    // system("cls");  // Utiliza esto en sistemas Windows

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            char c = puzzle[i][j];
            if (c >= 'A' && c <= 'Z') {
                printf("\033[1;32m%c\033[0m ", c); // Resaltar letras encontradas
            } else {
                printf("%c ", c);
            }
        }
        printf("\n");
    }
}

int isWordFound(char word[]) {
    for (int i = 0; i < WORD_COUNT; i++) {
        if (strcmp(word, words[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));
    initializePuzzle();

    for (int i = 0; i < WORD_COUNT; i++) {
        placeWord(words[i]);
    }

    int wordsFound = 0;

    while (wordsFound < WORD_COUNT) {
        displayPuzzle();
        printf("Palabras encontradas: %d/%d\n", wordsFound, WORD_COUNT);

        char guess[WORD_MAX_LENGTH];
        printf("Ingresa una palabra: ");
        scanf("%s", guess);

        if (isWordFound(guess)) {
            printf("¡Encontraste la palabra '%s'!\n", guess);
            wordsFound++;
        } else {
            printf("La palabra '%s' no se encuentra en la sopa de letras.\n", guess);
        }
    }

    printf("¡Felicidades! Has encontrado todas las palabras.\n");

    return 0;
}
