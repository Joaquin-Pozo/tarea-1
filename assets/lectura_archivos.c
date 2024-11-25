#include <stdio.h>
#include <stdlib.h>
int **leerArchivo (char nombreArchivo[], int *cantidadCargas, int *cantidadProcesos) {
    FILE *archivo = fopen(nombreArchivo, "r");

    // Comprueba el nombre del archivo ingresado
    /*
    if (archivo == NULL) {
    	printf("Error al abrir archivo %s\n", nombreArchivo);
        return NULL;
	}
    */
    if (archivo == NULL) {
    fprintf(stderr, "Error: El archivo '%s' no existe en la carpeta 'assets'. Verifica el nombre e intenta nuevamente.\n", nombreArchivo);
    exit(EXIT_FAILURE);
    }   
    
    // Lee la cantidad de cargas y procesos
    fscanf(archivo, "%d %d", cantidadCargas, cantidadProcesos);

    // Crea un arreglo dinamico para las cargas
    int **cargasIniciales = (int**)malloc(*cantidadCargas * sizeof(int*));

    // Lectura de los datos de cada carga
    for (int i = 0; i < *cantidadCargas; i++) {
        // Crea un arreglo dinámico para cada carga
        cargasIniciales[i] = (int*)malloc(2 * (*cantidadProcesos) * sizeof(int));
        // Lee los datos de cada carga por linea correspondiente
        for (int j = 0; j < 2 * (*cantidadProcesos); j++) {
            fscanf(archivo, "%d", &cargasIniciales[i][j]);
        }
    }
    fclose(archivo);
    return cargasIniciales;
}

void liberarMemoria(int **cargasIniciales, int cantidadCargas) {
    for (int i = 0; i < cantidadCargas; i++) {
        free(cargasIniciales[i]);
    }
    free(cargasIniciales);
}

void imprimirCargas(int **cargasIniciales, int cantidadCargas, int cantidadProcesos) {
    for (int i = 0; i < cantidadCargas; i++) {
        printf("Carga %d:\n", i + 1);
        for (int j = 0; j < cantidadProcesos; j++) {
            printf("  Proceso %d: Tiempo %d\n", 
                   cargasIniciales[i][2 * j], // id
                   cargasIniciales[i][2 * j + 1]); // tiempo
        }
    }
}