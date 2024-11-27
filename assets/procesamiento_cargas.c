#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "johnson-trotter.c"

// Estructura para representar un proceso
typedef struct {
    int **cargas;  // permutaciones de cargas
    int *tiempos;  // tiempos asociados a las cargas
    int cantidadCargas;
} Proceso;

// Función que genera los procesos con las permutaciones de las cargas
Proceso *generarProcesos(int cantidadCargas, int cantidadProcesos, int **conjuntoInicial) {
    int permutaciones = factorial(cantidadCargas);

    // Asigna memoria para un arreglo de procesos
    Proceso *procesos = (Proceso *)malloc(cantidadProcesos * sizeof(Proceso));

    // Genera las permutaciones mediante el algoritmo Johnson-Trotter
    int **permutacionesCargas = generarPermutaciones(cantidadCargas);

    // Asigna memoria a los procesos
    for (int p = 0; p < cantidadProcesos; p++) {
        procesos[p].cargas = (int **)malloc(permutaciones * sizeof(int *));
        procesos[p].tiempos = (int *)malloc(cantidadCargas * sizeof(int));
        procesos[p].cantidadCargas = cantidadCargas;

        // Copia las permutaciones y los tiempos de cada carga
        for (int i = 0; i < permutaciones; i++) {
            procesos[p].cargas[i] = (int *)malloc(cantidadCargas * sizeof(int));
            memcpy(procesos[p].cargas[i], permutacionesCargas[i], cantidadCargas * sizeof(int));
        }

        // Copia  los tiempos para cada carga del conjunto inicial
        for (int c = 0; c < cantidadCargas; c++) {
            procesos[p].tiempos[c] = conjuntoInicial[c][1];
        }
    }

    // Libera memoria de las permutaciones
    for (int i = 0; i < permutaciones; i++) {
        free(permutacionesCargas[i]);
    }
    free(permutacionesCargas);

    return procesos;
}

// Aplica las restricciones y genera la solución optimizada
void aplicarRestricciones(Proceso *procesos, int cantidadProcesos, int cantidadCargas) {
    // Inicializa los tiempos finales para cada carga
    int tiemposFinales[cantidadCargas];
    for (int i = 0; i < cantidadCargas; i++) {
        tiemposFinales[i] = 0;
    }

    int tiempoTotal = 0; // almacena el tiempo total de procesamiento

    // Genera la solución optimizada de acuerdo a las restricciones
    printf("\nSolución Optimizada:\n");
    // Recorre todas las cargas
    for (int c = 0; c < cantidadCargas; c++) {
        // Recorre todos los procesos
        for (int p = 0; p < cantidadProcesos; p++) {
            int cargaActual = procesos[p].cargas[0][c];  // obtiene la carga actual
            int tiempoInicio = tiemposFinales[cargaActual - 1]; // el tiempo inicio es el fin de la carga anterior
            int tiempoDuracion = procesos[p].tiempos[cargaActual - 1]; // obtiene el tiempo de duración de esta carga en el proceso
            int tiempoFin = tiempoInicio + tiempoDuracion; // calcula el tiempo final de la carga
            tiemposFinales[cargaActual - 1] = tiempoFin; // actualiza el tiempo de fin para la carga

            // Actualiza el tiempo total si el tiempo de fin de esta carga es el mayor hasta el momento
            if (tiempoFin > tiempoTotal) {
                tiempoTotal = tiempoFin;
            }

            printf("Proceso %d - Carga %d: Inicio=%d, Duración=%d, Fin=%d\n", 
                   p + 1, cargaActual, tiempoInicio, tiempoDuracion, tiemposFinales[cargaActual - 1]);
        }
    }
    // Muestra el tiempo total
    printf("\nTiempo total de procesamiento: %d\n", tiempoTotal);
}

// Libera memoria de los procesos
void liberarProcesos(Proceso *procesos, int cantidadProcesos) {
    for (int p = 0; p < cantidadProcesos; p++) {
        for (int i = 0; i < factorial(procesos[p].cantidadCargas); i++) {
            free(procesos[p].cargas[i]);
        }
        free(procesos[p].cargas);
        free(procesos[p].tiempos);
    }
    free(procesos);
}
