#include <stdlib.h>
#include "TDA_proceso.h"

proceso* crea_proceso(int id, int max_cargas) {
    proceso *nuevo_proceso = malloc(sizeof(proceso));
    nuevo_proceso->id = id;
    nuevo_proceso->max_cargas = max_cargas;
    nuevo_proceso->cardinalidad = 0;
    nuevo_proceso->cargas = (carga*)malloc(max_cargas * sizeof(carga));
    return nuevo_proceso;
}

void agregar_carga(proceso *p, carga *c) {
    if (p->cardinalidad < p->max_cargas) {
        p->cargas[p->cardinalidad] = *c;
        p->cardinalidad++;
    }
}

void destruye_proceso(proceso *p) {
    free(p->cargas);
    free(p);
}