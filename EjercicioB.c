#include <stdio.h>
#include <stdlib.h>
#include <omp.h>  // Necesario para usar OpenMP.

#define ROWS_M1 1000
#define COLS_M1 1000
#define ROWS_M2 1000
#define COLS_M2 1000

// Función para multiplicar dos matrices.
void multiplyMatrix(int **m1, int **m2, int **result) {
    // Verificar que se puedan multiplicar las matrices.
    if (COLS_M1 != ROWS_M2) {
        fprintf(stderr, "Error: El número de columnas de la primera matriz debe ser igual al número de filas de la segunda matriz.\n");
        exit(EXIT_FAILURE);
    }

    // Paralelización de la multiplicación de matrices usando OpenMP.
    #pragma omp parallel for
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
    // Asignación dinámica de memoria para las matrices.
    int **m1 = (int **)malloc(ROWS_M1 * sizeof(int *));
    int **m2 = (int **)malloc(ROWS_M2 * sizeof(int *));
    int **result = (int **)malloc(ROWS_M1 * sizeof(int *));

    // Inicializar la matriz m1 con todos los elementos en 1.
    for (int i = 0; i < ROWS_M1; i++) {
        m1[i] = (int *)malloc(COLS_M1 * sizeof(int));
        result[i] = (int *)malloc(COLS_M2 * sizeof(int));
        
        for (int j = 0; j < COLS_M1; j++) {
            m1[i][j] = 1;
        }
    }

    // Inicializar la matriz m2 con todos los elementos en 2.
    for (int i = 0; i < ROWS_M2; i++) {
        m2[i] = (int *)malloc(COLS_M2 * sizeof(int));
        
        for (int j = 0; j < COLS_M2; j++) {
            m2[i][j] = 2;
        }
    }

    // Llamada a la función de multiplicación.
    multiplyMatrix(m1, m2, result);

    // (Opcional) Imprimir el resultado. Puede ser muy extenso, así que está comentado.
    // for (int i = 0; i < ROWS_M1; i++) {
    //     for (int j = 0; j < COLS_M2; j++) {
    //         printf("%d\t", result[i][j]);
    //     }
    //     printf("\n");
    // }

    // Liberar la memoria asignada dinámicamente.
    for (int i = 0; i < ROWS_M1; i++) {
        free(m1[i]);
        free(result[i]);
    }

    for (int i = 0; i < ROWS_M2; i++) {
        free(m2[i]);
    }

    free(m1);
    free(m2);
    free(result);

    return 0;
}
