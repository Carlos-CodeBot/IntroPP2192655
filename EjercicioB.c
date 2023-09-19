#include <stdio.h>
#include <stdlib.h>

// Definición de las dimensiones de las matrices
#define ROWS_M1 3
#define COLS_M1 2
#define ROWS_M2 2
#define COLS_M2 3

void multiplyMatrix(int m1[ROWS_M1][COLS_M1], int m2[ROWS_M2][COLS_M2], int result[ROWS_M1][COLS_M2]) {
    if (COLS_M1 != ROWS_M2) {
        fprintf(stderr, "Error: El número de columnas de la primera matriz debe ser igual al número de filas de la segunda matriz.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ROWS_M1; i++) {
        for (int j = 0; j < COLS_M2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < COLS_M1; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

int main() {
    int m1[ROWS_M1][COLS_M1] = {
        {1, 1},
        {2, 2},
        {3, 3}
    };

    int m2[ROWS_M2][COLS_M2] = {
        {1, 1, 1},
        {2, 2, 2}
    };

    int result[ROWS_M1][COLS_M2];
    multiplyMatrix(m1, m2, result);

    for (int i = 0; i < ROWS_M1; i++) {
        for (int j = 0; j < COLS_M2; j++) {
            printf("%d\t", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}

