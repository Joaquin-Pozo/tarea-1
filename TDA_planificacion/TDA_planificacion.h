#pragma once
#include "../TDA_proceso/TDA_proceso.h"
/*------------- TDA planificacion -------------*/

/*------------- estructura de datos -------------*/

typedef struct { 
	int total_segundos;
    int max_procesos;
    int cardinalidad;
    proceso *procesos;

}planificacion;


/*------------- operaciones -------------*/

// crea_planificacion() retorna una nueva planificacion con un tiempo en segundos y un arreglo de procesos
planificacion* crea_planificacion(int max_procesos);

// agrega_proceso() agrega un nuevo proceso a una planificacion
void agregar_proceso(planificacion *pl, proceso *p);

// mostrar_planificacion()
void mostrar_planificacion(planificacion *pl);

// destruye_planificacion() libera la memoria asignada a la planificacion
void destruye_planificacion(planificacion *pl);

