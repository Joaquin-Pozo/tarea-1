#include <stdio.h>
#include <stdlib.h>
#include "johnson-trotter.c"

typedef struct {
    int id;
    int orden;
    int proceso;
    int tiempo;
} Carga;


Carga *generarCargas(int cantidadCargas, int cantidadProcesos, int **conjuntoInicial) {
    int n = cantidadCargas*cantidadProcesos;
    Carga *arregloCargas = (Carga *)malloc(n * sizeof(Carga));
    int k = 0;
    while (k < n) {
        for (int i = 0; i < cantidadCargas; i++) {
            arregloCargas[i].id = i + 1;
            arregloCargas[i].orden = k;
        }
    }
    
}



/*

typedef struct {
    int id;
    int *proceso;
    int *tiempo;
} Carga;

Carga *generarCargas(int cantidadCargas, int cantidadProcesos, int **conjuntoInicial) {
    Carga *arregloCargas = (Carga *)malloc(cantidadCargas * sizeof(Carga));
    for (int i = 0; i < cantidadCargas; i++) {
        arregloCargas[i].id = i + 1;
        arregloCargas[i].proceso = (int *)malloc(cantidadProcesos * sizeof(int));
        arregloCargas[i].tiempo = (int *)malloc(cantidadProcesos * sizeof(int));
        for (int j = 0; j < cantidadProcesos; j++) {
            arregloCargas[i].proceso[j] = conjuntoInicial[i][2 * j];
            arregloCargas[i].tiempo[j] = conjuntoInicial[i][2 * j + 1];
        }
    }
    return arregloCargas;
}



void mostrarCargas(Carga *arregloCargas, int cantidadCargas, int cantidadProcesos) {
    for (int i = 0; i < cantidadCargas; i++) {
        printf("Carga %d:\n", i + 1);
        for (int j = 0; j < cantidadProcesos; j++) {
            printf("Orden Proceso: %d, Tiempo: %d\n", arregloCargas[i].proceso[j], arregloCargas[i].tiempo[j]);
        }
        printf("\n");
    }
}
*/




void mostrarPermutaciones(int n, int permutaciones) {
    int **arregloPermutaciones = generarPermutaciones(n, permutaciones);
    printf("Permutaciones totales:\n");
    for (int i = 0; i < permutaciones; i++) {
        printf("  Permutacion %d: ", i + 1);
        for (int j = 0; j < n; j++) {
            printf("%d ", arregloPermutaciones[i][j]);
        }
        printf("\n");
    }
}









