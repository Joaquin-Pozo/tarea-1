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

// Función que genera los procesos con las permutaciones de las cargas
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
/*

// Función que aplica las restricciones y genera una solución optimizada
void aplicarRestricciones(Proceso *procesos, int cantidadCargas, int cantidadProcesos) {
    int tiemposFinales[cantidadCargas];
    for (int i = 0; i < cantidadCargas; i++) {
        tiemposFinales[i] = 0;
    }
    int tiempoTotal = 0;
    printf("\nSolución Optimizada:\n");
    // Recorre todos los procesos primero
    for (int p = 0; p < cantidadProcesos; p++) {
        printf("Proceso %d:\n", p + 1);

        // Dentro de cada proceso, recorre las cargas en el orden definido
        for (int c = 0; c < cantidadCargas; c++) {
            int cargaActual = procesos[p].cargas[0][c];  // Obtiene la carga actual
            int tiempoInicio = tiemposFinales[cargaActual - 1]; // Tiempo de inicio para esta carga
            int tiempoDuracion = procesos[p].tiempos[cargaActual - 1]; // Duración de la carga
            int tiempoDuracion = procesos[p].tiempos[cargaActual - 1][p]; // Duración de la carga
            int tiempoFin = tiempoInicio + tiempoDuracion; // Calcula el tiempo final
            tiemposFinales[cargaActual - 1] = tiempoFin; // Actualiza el tiempo de fin

            // Actualiza el tiempo total si el tiempo de fin de esta carga es el mayor hasta ahora
            if (tiempoFin > tiempoTotal) {
                tiempoTotal = tiempoFin;
            }

            printf("  Carga %d: Inicio=%d, Duración=%d, Fin=%d\n", 
                   cargaActual, tiempoInicio, tiempoDuracion, tiempoFin);
        }
    }

    // Muestra el tiempo total
    printf("\nTiempo total de procesamiento: %d\n", tiempoTotal);
}
*/

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
        for (int i = 0; i < permutaciones; i++){ 
            free(procesos[p].cargas[i]); 
        }
        free(procesos[p].orden);
        free(procesos[p].tiempos);
        free(procesos[p].cargas);
    }
    free(procesos);
}

