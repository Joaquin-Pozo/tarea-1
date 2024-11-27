#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assets/lectura_archivos.c"
#include "assets/johnson-trotter.c"
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

    int **conjuntoInicial = leerArchivo(nombreArchivo, &cantidadCargas, &cantidadProcesos);

    printf("Datos de las cargas:\n");

    imprimirCargas(conjuntoInicial, cantidadCargas, cantidadProcesos);

    // Generar conjunto de soluciones
    int permutaciones = factorial(cantidadCargas);
    int **conjuntoSoluciones = generarPermutaciones(cantidadCargas);

    printf("\nPermutaciones generadas:\n");
    for (int i = 0; i < permutaciones; i++) {
        for (int j = 0; j < cantidadCargas; j++) {
            printf("%d ", conjuntoSoluciones[i][j]);
        }
        printf("\n");
    }

    liberarMemoria(conjuntoInicial, cantidadCargas);

    // Liberar memoria del conjunto de soluciones
    for (int i = 0; i < permutaciones; i++) {
        free(conjuntoSoluciones[i]);
    }
    free(conjuntoSoluciones);

    return 0;
}
