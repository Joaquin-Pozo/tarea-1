#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assets/lectura_archivos.c"
#include "assets/johnson-trotter.c"
#include "assets/procesamiento_cargas.c"

// nombre archivo, nombre archivo que desea leer
int main(int argc, char *argv[]) {
    
    char nombreArchivo[80];

    // Concatena la ruta del archivo con su nombre
    snprintf(nombreArchivo, sizeof(nombreArchivo), "assets/%s", argv[1]);

    int cantidadCargas, cantidadProcesos;

    int **conjuntoInicial = leerArchivo(nombreArchivo, &cantidadCargas, &cantidadProcesos);

    printf("Datos de las cargas:\n");

    imprimirCargas(conjuntoInicial, cantidadCargas, cantidadProcesos);

    // Generar procesos

    int permutaciones = factorial(cantidadCargas);

    printf("\nPermutaciones : %d\n", permutaciones);

    Proceso *procesos = generarProcesos(cantidadCargas, cantidadProcesos, conjuntoInicial, permutaciones);

    mostrarProcesos(procesos, cantidadCargas, cantidadProcesos, permutaciones);



    // Liberar memoria
    liberarMemoria(conjuntoInicial, cantidadCargas);
    liberarProcesos(procesos, cantidadProcesos, cantidadCargas, permutaciones);
}
