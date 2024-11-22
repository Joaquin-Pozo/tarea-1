#include <stdio.h>
#include <stdlib.h>
#include "../TDA_planificacion/TDA_planificacion.h"
proceso *leerArchivo (const char* nombreArchivo, int *cantidadCargas, int *cantidadProcesos) {
    FILE *archivo = fopen(nombreArchivo, "r");

    // Lee la cantidad de cargas y procesos
    fscanf(archivo, "%d %d", cantidadCargas, cantidadProcesos);

    // Limpia el salto de linea en el bufer
    fgetc(archivo);

    // Crea un arreglo dinámico para la planificación de procesos
    planificacion *pl = crea_planificacion(cantidadProcesos);
    char linea[256];
    for (int i = 0; i < *cantidadCargas; i++) {
        
        fgets(linea, sizeof(linea), archivo);
        sscanf(linea,"",);
    }

    fclose(archivo);
    return arregloTemperaturas;
}