#include <stdio.h>
#include <stdlib.h>
#include "TDA_carga/TDA_carga.h"
#include "TDA_proceso/TDA_proceso.h"
#include "TDA_planificacion/TDA_planificacion.h"
/*
Para ejecutar el main, se debe usar esta linea en la consola de comandos:
gcc procesamiento_cargas.c TDA_carga/TDA_carga_implementacion.c TDA_proceso/TDA_proceso_implementacion.c TDA_planificacion/TDA_planificacion_implementacion.c -o cargas
*/

int main() {
    
    carga *c1_1 = crea_carga(1, 1, 3);
    carga *c1_2 = crea_carga(1, 2, 3);
    carga *c1_3 = crea_carga(1, 3, 3);
    
    /*
    carga *c2_1 = crea_carga(2, 1, 2);
    carga *c2_2 = crea_carga(2, 3, 3);
    carga *c2_3 = crea_carga(2, 2, 4);

    carga *c3_1 = crea_carga(3, 2, 3);
    carga *c3_2 = crea_carga(3, 1, 2);
    carga *c3_3 = crea_carga(3, 3, 1);
    */
    proceso *p1 = crea_proceso(1, 3);
    agregar_carga(p1, c1_1);
    agregar_carga(p1, c1_2);
    agregar_carga(p1, c1_3);

    planificacion *pl = crea_planificacion(3);

    agregar_proceso(pl, p1);

    mostrar_planificacion(pl);

    destruye_planificacion(pl);

    destruye_proceso(p1);


    return 0;
}
