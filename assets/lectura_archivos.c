#include <stdio.h>
#include <stdlib.h>
#include "../TDA_planificacion/TDA_planificacion.h"
void *leerArchivo (const char* nombreArchivo, int *cantidadCargas, int *cantidadProcesos) {
    FILE *archivo = fopen(nombreArchivo, "r");

    // Lee la cantidad de cargas y procesos
    fscanf(archivo, "%d %d", cantidadCargas, cantidadProcesos);

    // Limpia el salto de linea en el bufer
    fgetc(archivo);

    for (int i = 0; i < *cantidadCargas; i++) {
        fgets(linea, sizeof(linea), archivo);
        sscanf(linea,"%d %d %d %d %d %d",[i]);
    }

    // Crea un arreglo dinámico para procesos
    for (int i = 0; i < cantidadProcesos; i++) {
        proceso *p_i = crea_proceso(i, cantidadCargas);
    }
    char linea[256];
    
    

    fclose(archivo);

}