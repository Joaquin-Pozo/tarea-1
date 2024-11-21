#pragma once
#include "../TDA_carga/TDA_carga.h"
/*------------- TDA proceso -------------*/

/*------------- estructura de datos -------------*/

typedef struct { 
	int id;
    int max_cargas;
    int cardinalidad;
    carga *cargas;
}proceso;


/*------------- operaciones -------------*/

// crea_proceso() retorna un nuevo proceso con un numero identificador y espacio para n cargas
proceso* crea_proceso(int id, int n_cargas);

// agrega_carga() agrega una nueva carga a un proceso
void agregar_carga(proceso *p, carga *c);

// destruye_proceso(max_cargas) libera la memoria asignada al proceso p
void destruye_proceso(proceso *p);