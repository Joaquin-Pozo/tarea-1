#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PROCESOS 3
#define NUM_CARGAS 3

// Datos de tiempos por proceso para cada carga.
int tiempos[NUM_CARGAS][NUM_PROCESOS] = {
    {3, 3, 3},  // Carga 1
    {2, 4, 3},  // Carga 2
    {2, 3, 1}   // Carga 3
};

// Generar todas las permutaciones de las cargas.
void permutar(int *arr, int l, int r, int **resultados, int *index) {
    if (l == r) {
        memcpy(resultados[*index], arr, NUM_CARGAS * sizeof(int));
        (*index)++;
    } else {
        for (int i = l; i <= r; i++) {
            // Intercambiar
            int temp = arr[l];
            arr[l] = arr[i];
            arr[i] = temp;
            permutar(arr, l + 1, r, resultados, index);
            // Revertir intercambio
            temp = arr[l];
            arr[l] = arr[i];
            arr[i] = temp;
        }
    }
}

// Función para calcular el makespan dado un orden de cargas y procesos.
int calcularMakespan(int *orden) {
    int tiemposProceso[NUM_PROCESOS] = {0}; // Disponibilidad de cada proceso.
    int tiemposCarga[NUM_CARGAS] = {0};    // Tiempo acumulado de cada carga.

    for (int i = 0; i < NUM_CARGAS; i++) {
        int cargaActual = orden[i];
        for (int j = 0; j < NUM_PROCESOS; j++) {
            int tiempoInicio = tiemposProceso[j] > tiemposCarga[cargaActual] ? tiemposProceso[j] : tiemposCarga[cargaActual];
            tiemposCarga[cargaActual] = tiempoInicio + tiempos[cargaActual][j];
            tiemposProceso[j] = tiemposCarga[cargaActual];
        }
    }

    // El makespan es el tiempo máximo en todos los procesos.
    int makespan = 0;
    for (int j = 0; j < NUM_PROCESOS; j++) {
        if (tiemposProceso[j] > makespan) {
            makespan = tiemposProceso[j];
        }
    }
    return makespan;
}

int main() {
    int cargas[NUM_CARGAS] = {0, 1, 2}; // Identificadores de cargas.
    int numPermutaciones = 1;
    for (int i = 1; i <= NUM_CARGAS; i++) numPermutaciones *= i;

    // Arreglo para almacenar todas las permutaciones.
    int **permutaciones = (int **)malloc(numPermutaciones * sizeof(int *));
    for (int i = 0; i < numPermutaciones; i++) {
        permutaciones[i] = (int *)malloc(NUM_CARGAS * sizeof(int));
    }

    // Generar permutaciones.
    int index = 0;
    permutar(cargas, 0, NUM_CARGAS - 1, permutaciones, &index);

    // Evaluar cada permutación.
    int mejorMakespan = __INT_MAX__;
    int mejorPermutacion[NUM_CARGAS];

    for (int i = 0; i < numPermutaciones; i++) {
        int makespan = calcularMakespan(permutaciones[i]);
        printf("Permutación %d: Makespan = %d\n", i + 1, makespan);
        if (makespan < mejorMakespan) {
            mejorMakespan = makespan;
            memcpy(mejorPermutacion, permutaciones[i], NUM_CARGAS * sizeof(int));
        }
    }

    // Imprimir la mejor solución.
    printf("Mejor makespan: %d con permutación: ", mejorMakespan);
    for (int i = 0; i < NUM_CARGAS; i++) {
        printf("%d ", mejorPermutacion[i] + 1);
    }
    printf("\n");

    // Liberar memoria.
    for (int i = 0; i < numPermutaciones; i++) {
        free(permutaciones[i]);
    }
    free(permutaciones);

    return 0;
}
