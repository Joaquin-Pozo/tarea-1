#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assets/lectura_archivos.c"
/*
Para ejecutar el main, se debe usar esta linea en la consola de comandos:
gcc procesamiento_cargas.c -o cargas
*/

// nombre archivo, nombre archivo que desea leer
int main(int argc, char *argv[]) {
    
    char nombreArchivo[80];

    // Concatena la ruta del archivo con su nombre
    snprintf(nombreArchivo, sizeof(nombreArchivo), "assets/%s", argv[1]);

    int cantidadCargas, cantidadProcesos;

    int **cargasIniciales = leerArchivo(nombreArchivo, &cantidadCargas, &cantidadProcesos);

    printf("Datos de las cargas:\n");

    imprimirCargas(cargasIniciales, cantidadCargas, cantidadProcesos);

    liberarMemoria(cargasIniciales, cantidadCargas);

    // Almacena memoria para un conjunto con todas las soluciones de O ~ (m * n!)
    int cantidadSoluciones = cantidadProcesos * factorial(cantidadCargas);
    int ***conjuntoSoluciones = (int***)malloc(cantidadSoluciones * sizeof(int**));

    // Crea el conjunto con todas las soluciones;
    for (int i = 0; i < cantidadSoluciones; i++) {
        conjuntoSoluciones[i] = (int**)malloc(cantidadCargas * sizeof(int*));
        for (int j = 0; j < cantidadCargas; j++) {
            conjuntoSoluciones[i][j] = (int*)malloc(2 * (cantidadProcesos) * sizeof(int));
            
        }
    }



    // Aplicar restricciones al conjunto de soluciones


    return 0;
}
