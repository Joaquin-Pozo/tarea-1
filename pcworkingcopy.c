#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDA_carga/TDA_carga.h"
#include "TDA_proceso/TDA_proceso.h"
#include "TDA_planificacion/TDA_planificacion.h"
#include "assets/lectura_archivos.c"
/*
Para ejecutar el main, se debe usar esta linea en la consola de comandos:
gcc procesamiento_cargas.c TDA_carga/TDA_carga_implementacion.c TDA_proceso/TDA_proceso_implementacion.c TDA_planificacion/TDA_planificacion_implementacion.c -o cargas
*/

// nombre archivo, nombre archivo que desea leer
int main(int argc, char *argv[]) {
    
    char nombreArchivo[256];

    snprintf(nombreArchivo, sizeof(nombreArchivo), "assets/%s", argv[1]);

    int cantidadCargas, cantidadProcesos;

    int **cargasIniciales = leerArchivo(nombreArchivo, &cantidadCargas, &cantidadProcesos);

    printf("test:\n");
    int i,j;
    planificacion *p1 = crea_planificacion(cantidadProcesos);
    for(i=0;i<cantidadCargas;i++){
    proceso *proceso1 = crea_proceso(i, cantidadCargas);
        for(j=0;j<cantidadProcesos;j++){
                carga *carga1 = crea_carga(cargasIniciales[i][2 * j], j, cargasIniciales[i][2 * j+1]);
                agregar_carga(proceso1, carga1);
            }   
        agregar_proceso(p1, proceso1);
        }

    for(i=0;i<cantidadCargas;i++){
        for(j=0;j<cantidadProcesos;j++){
            printf(" (id proceso: %d, t: %d)", p1->procesos[i].cargas[j].id, p1->procesos[i].cargas[j].tiempo);
        }
        printf("\n");
    }        


    // crear conjunto con todas las soluciones
    // aplicar restricciones al conjunto de soluciones

    liberarMemoria(cargasIniciales, cantidadCargas);
    return 0;

}