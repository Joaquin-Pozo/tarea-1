#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma once

// Direcciones de movimiento
#define IZQUIERDA_A_DERECHA true
#define DERECHA_A_IZQUIERDA false

/*
Pasos a repetir en el algoritmo de Jonhson-Trotter (hasta que no queden números móviles o bien para este caso, hasta factorial(n)):
1. Generar la permutación inicial
2. Identificar el número móvil más grande
3. Intercambiar el número móvil más grande con el elemento adyacente según la dirección
4. Invertir la dirección de los elementos mayores que el número móvil
*/

// Calcula el factorial de un número
int factorial(int n) {
    if (n == 1 || n == 0) {
        return 1;
    }
    return n * factorial(n - 1);
}
// Busca la posición de un nuḿero móvil en el arreglo
int buscarPosicion(int arreglo[], int n, int movil) {
    for (int i = 0; i < n; i++) {
        if (arreglo[i] == movil)
            return i;
    }
    return -1; // si no encuentra el número móvil en el arreglo
}

// Encuentra el nuḿero móvil más grande
int obtenerMovil(int arreglo[], bool direcciones[], int n) {
    int movil_anterior = 0;
    int movil = 0;
    for (int i = 0; i < n; i++) {
        // Si la dirección es de derecha a izquierda
        if (direcciones[arreglo[i] - 1] == DERECHA_A_IZQUIERDA && i != 0) {
            if (arreglo[i] > arreglo[i - 1] && arreglo[i] > movil_anterior) {
                movil = arreglo[i];
                movil_anterior = movil;
            }
        }

        // Si la dirección es de izquierda a derecha
        if (direcciones[arreglo[i] - 1] == IZQUIERDA_A_DERECHA && i != n - 1) {
            if (arreglo[i] > arreglo[i + 1] && arreglo[i] > movil_anterior) {
                movil = arreglo[i];
                movil_anterior = movil;
            }
        }
    }
    return movil;
}

// Genera todas las permutaciones y las guarda en un arreglo
int **generarPermutaciones(int n, int permutaciones) {
    // Arreglo para guardar todas las permutaciones
    int **resultado = (int **)malloc(permutaciones * sizeof(int *));
    for (int i = 0; i < permutaciones; i++) {
        resultado[i] = (int *)malloc(n * sizeof(int));
    }

    // Inicializa el arreglo con la primera permutación
    int arreglo[n];
    bool direcciones[n];
    for (int i = 0; i < n; i++) {
        arreglo[i] = i + 1;
        direcciones[i] = DERECHA_A_IZQUIERDA; // Todas las direcciones a la izquierda inicialmente
    }

    // Copia la primera permutación al resultado
    for (int i = 0; i < n; i++) {
        resultado[0][i] = arreglo[i];
    }

    // Genera las permutaciones restantes
    for (int p = 1; p < permutaciones; p++) {
        int movil = obtenerMovil(arreglo, direcciones, n);
        int indice = buscarPosicion(arreglo, n, movil);

        // Intercambia según la dirección del número móvil
        if (direcciones[arreglo[indice] - 1] == DERECHA_A_IZQUIERDA) {
            int temp = arreglo[indice];
            arreglo[indice] = arreglo[indice - 1];
            arreglo[indice - 1] = temp;
        } else if (direcciones[arreglo[indice] - 1] == IZQUIERDA_A_DERECHA) {
            int temp = arreglo[indice];
            arreglo[indice] = arreglo[indice + 1];
            arreglo[indice + 1] = temp;
        }

        // Cambia direcciones de los elementos mayores al número móvil
        for (int i = 0; i < n; i++) {
            if (arreglo[i] > movil) {
                direcciones[arreglo[i] - 1] = !direcciones[arreglo[i] - 1];
            }
        }

        // Copia la permutación actual al resultado
        for (int i = 0; i < n; i++) {
            resultado[p][i] = arreglo[i];
        }
    }

    return resultado;
}