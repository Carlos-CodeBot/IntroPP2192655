#include <stdio.h>
#include <stdlib.h>

// Definición de las dimensiones de las matrices.
// Esto facilita el cambio de dimensiones en un solo lugar.
#define ROWS_M1 3
#define COLS_M1 2
#define ROWS_M2 2
#define COLS_M2 3

/*
 * Función para multiplicar dos matrices.
 * Las matrices son pasadas como argumentos junto con una matriz resultante.
 * La matriz resultante se modificará con el resultado de la multiplicación.
 */
void multiplyMatrix(int m1[ROWS_M1][COLS_M1], int m2[ROWS_M2][COLS_M2], int result[ROWS_M1][COLS_M2]) {
    // Verificar que el número de columnas de m1 es igual al número de filas de m2.
    if (COLS_M1 != ROWS_M2) {
        fprintf(stderr, "Error: El número de columnas de la primera matriz debe ser igual al número de filas de la segunda matriz.\n");
        exit(EXIT_FAILURE);
    }

    // Multiplicación de matrices.
    for (int i = 0; i < ROWS_M1; i++) {
        for (int j = 0; j < COLS_M2; j++) {
            result[i][j] = 0;  // Inicializar el elemento resultante.
            
            // Calcular el valor de result[i][j] como el producto punto de la fila i de m1 y la columna j de m2.
            for (int k = 0; k < COLS_M1; k++) {
                result[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }
}

int main() {
    // Declarar e inicializar las matrices m1 y m2.
    int m1[ROWS_M1][COLS_M1] = {
        {1, 1},
        {2, 2},
        {3, 3}
    };

    int m2[ROWS_M2][COLS_M2] = {
        {1, 1, 1},
        {2, 2, 2}
    };

    // Declarar una matriz para almacenar el resultado.
    int result[ROWS_M1][COLS_M2];
    
    // Llamar a la función de multiplicación de matrices.
    multiplyMatrix(m1, m2, result);

    // Imprimir la matriz resultante.
    for (int i = 0; i < ROWS_M1; i++) {
        for (int j = 0; j < COLS_M2; j++) {
            printf("%d\t", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}

