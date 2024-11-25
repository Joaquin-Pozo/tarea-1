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

    printf("Datos de las cargas:\n");
    imprimirCargas(cargasIniciales, cantidadCargas, cantidadProcesos);

    liberarMemoria(cargasIniciales, cantidadCargas);


    // crear conjunto con todas las soluciones



    // aplicar restricciones al conjunto de soluciones


    return 0;
}
