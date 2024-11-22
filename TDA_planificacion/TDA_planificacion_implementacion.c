#include <stdlib.h>
#include <stdio.h>
#include "TDA_planificacion.h"

planificacion* crea_planificacion(int max_procesos) {
    planificacion *nueva_planificacion = malloc(sizeof(planificacion));
    nueva_planificacion->total_segundos = 0;
    nueva_planificacion->max_procesos = max_procesos;
    nueva_planificacion->cardinalidad = 0;
    nueva_planificacion->procesos = (proceso*)malloc(max_procesos * sizeof(proceso));
    return nueva_planificacion;
}

void agregar_proceso(planificacion *pl, proceso *p) {
    if (pl->cardinalidad < pl->max_procesos) {
        pl->procesos[pl->cardinalidad] = *p;
        pl->cardinalidad++;
        for (int i = 0; i < p->cardinalidad; i++) {
            pl->total_segundos = pl->total_segundos + p->cargas[i].tiempo;
        }
    }
}

void mostrar_planificacion(planificacion *pl) {
    printf("Total segundos: %d\n", pl->total_segundos);
    printf("Maximo de procesos: %d\n", pl->max_procesos);
    printf("Cardinalidad: %d\n", pl->cardinalidad);
}

void destruye_planificacion(planificacion *pl) {
    free(pl->procesos);
    free(pl);
}