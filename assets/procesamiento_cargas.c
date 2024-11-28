#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "johnson-trotter.c"

// estructura para representar un proceso
typedef struct {
    int **cargas;  // permutaciones de cargas
    int **orden;    // orden de procesamiento de las cargas
    int **tiempos;  // tiempos asociados a las cargas
    int cantidadCargas;
} Proceso;

// Función que genera un arreglo de procesos con el conjunto de permutaciones de las cargas, orden, tiempo y cantidad de cargas del conjunto inicial.
Proceso *generarProcesos(int cantidadCargas, int cantidadProcesos, int **conjuntoInicial, int permutaciones) {
    // Asigna memoria para un arreglo de procesos
    Proceso *procesos = (Proceso *)malloc(cantidadProcesos * sizeof(Proceso));

    // Genera las permutaciones mediante el algoritmo Johnson-Trotter
    int **permutacionesCargas = generarPermutaciones(cantidadCargas, permutaciones);

    // Asigna memoria a los procesos
    for (int p = 0; p < cantidadProcesos; p++) {
        procesos[p].cargas = (int **)malloc(permutaciones * sizeof(int *));
        procesos[p].orden = (int **)malloc(cantidadCargas * sizeof(int *));
        procesos[p].tiempos = (int **)malloc(cantidadCargas * sizeof(int *));
        procesos[p].cantidadCargas = cantidadCargas;

        // Copia las permutaciones de cada carga
        for (int i = 0; i < permutaciones; i++) {
            procesos[p].cargas[i] = (int *)malloc(cantidadCargas * sizeof(int));
            if (!procesos[p].cargas[i]) {
                printf("Error al asignar memoria para cargas[%d] en proceso %d\n", i, p);
                exit(1);
            }
            memcpy(procesos[p].cargas[i], permutacionesCargas[i], cantidadCargas * sizeof(int));
        }

        // Copia el orden y tiempo para cada carga del conjunto inicial
        for (int c = 0; c < cantidadCargas; c++) {
            procesos[p].orden[c] = (int *)malloc(cantidadCargas * sizeof(int));
            procesos[p].tiempos[c] = (int *)malloc(cantidadCargas * sizeof(int));
            for (int t = 0; t < cantidadProcesos; t++) {
                procesos[p].orden[c][t] = conjuntoInicial[c][2 * t];
                procesos[p].tiempos[c][t] = conjuntoInicial[c][2 * t + 1];

            }
        }
    }

    // Libera memoria de las permutaciones
    for (int i = 0; i < permutaciones; i++) {
        free(permutacionesCargas[i]);
    }
    free(permutacionesCargas);

    return procesos;
}

void aplicarRestricciones(Proceso *procesos, int cantidadCargas, int cantidadProcesos) {
    
}


void mostrarProcesos(Proceso *procesos, int cantidadCargas, int cantidadProcesos, int permutaciones) {
    for (int p = 0; p < cantidadProcesos; p++) {
        printf("Proceso %d:\n", p + 1);
        printf("=========================\n");

        // Mostrar todas las permutaciones de cargas
        printf("Permutaciones de cargas:\n");
        for (int c = 0; c < permutaciones; c++) {
            printf("  Permutación %d: ", c + 1);
            for (int i = 0; i < cantidadCargas; i++) {
                printf("%d ", procesos[p].cargas[c][i]);
            }
            printf("\n");
        }

        // Mostrar los tiempos asociados a cada carga
        printf("Tiempos de procesamiento:\n");
        for (int i = 0; i < cantidadCargas; i++) {
            printf("  Carga %d: ", i + 1);
            for (int j = 0; j < cantidadProcesos; j++) {
                printf("%d ", procesos[p].tiempos[i][j]);
            }
            printf("\n");
        }

        // Mostrar el orden de procesamiento de las cargas
        printf("Orden de procesamiento:\n");
        for (int i = 0; i < cantidadCargas; i++) {
            printf("  Carga %d: ", i + 1);
            for (int j = 0; j < cantidadProcesos; j++) {
                printf("%d ", procesos[p].orden[i][j]);
            }
            printf("\n");
        }
        printf("=========================\n\n");
    }
}


// Libera memoria de los procesos
void liberarProcesos(Proceso *procesos, int cantidadProcesos, int cantidadCargas, int permutaciones) {
    for (int p = 0; p < cantidadProcesos; p++) {
        free(procesos[p].orden);
        free(procesos[p].tiempos);
        free(procesos[p].cargas);
    }
    free(procesos);
}

