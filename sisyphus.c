#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define IZQUIERDA_A_DERECHA true
#define DERECHA_A_IZQUIERDA false

typedef struct {
    int id_carga;
    int id_proceso;
    int orden_de_ejecucion;
    int tiempo;
} cargas;

void leerArchivo(const char *filename, int *n, int *m, cargas **first_list, int *true_n, int **aux_list) {
    FILE *file = fopen(filename, "r");
    fscanf(file, "%d %d", n, m);
    *true_n = (*n) * (*m);
    
    // Creando la lista de cargas
    *first_list = (cargas *)malloc(*true_n * sizeof(cargas));
    int index = 0;
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *m * 2; j += 2) {
            int id_procesoFor, tiempoFor;
            fscanf(file, "%d %d", &id_procesoFor, &tiempoFor);
            (*first_list)[index].id_carga = i + 1;
            (*first_list)[index].id_proceso = id_procesoFor;
            (*first_list)[index].orden_de_ejecucion = (j / 2) + 1;
            (*first_list)[index].tiempo = tiempoFor;
            index++;
        }
    }
    
    // Creando la lista de numeros a permutar
    *aux_list = (int *)malloc(*true_n * sizeof(int));
    for (int i = 0; i < *true_n; i++) {
        (*aux_list)[i] = i + 1;
    }
    
    fclose(file);
}

int factorial(int n) {
    if (n == 1 || n == 0) return 1;
    return n * factorial(n - 1);
}

int buscarPosicion(int arreglo[], int n, int movil) {
    for (int i = 0; i < n; i++) {
        if (arreglo[i] == movil) return i;
    }
    return -1;
}

int obtenerMovil(int arreglo[], bool direcciones[], int n) {
    int movil_anterior = 0, movil = 0;
    for (int i = 0; i < n; i++) {
        if (direcciones[arreglo[i] - 1] == DERECHA_A_IZQUIERDA && i != 0) {
            if (arreglo[i] > arreglo[i - 1] && arreglo[i] > movil_anterior) {
                movil = arreglo[i];
                movil_anterior = movil;
            }
        }
        if (direcciones[arreglo[i] - 1] == IZQUIERDA_A_DERECHA && i != n - 1) {
            if (arreglo[i] > arreglo[i + 1] && arreglo[i] > movil_anterior) {
                movil = arreglo[i];
                movil_anterior = movil;
            }
        }
    }
    return movil;
}

int **generarPermutaciones(int *lista, int n, int *num_permutaciones) {
    *num_permutaciones = factorial(n);
    int **resultado = (int **)malloc(*num_permutaciones * sizeof(int *));
    for (int i = 0; i < *num_permutaciones; i++) {
        resultado[i] = (int *)malloc(n * sizeof(int));
    }
    int arreglo[n];
    bool direcciones[n];
    for (int i = 0; i < n; i++) {
        arreglo[i] = lista[i];
        direcciones[i] = DERECHA_A_IZQUIERDA;
    }
    for (int i = 0; i < n; i++) {
        resultado[0][i] = arreglo[i];
    }
    for (int p = 1; p < *num_permutaciones; p++) {
        int movil = obtenerMovil(arreglo, direcciones, n);
        int indice = buscarPosicion(arreglo, n, movil);
        if (direcciones[arreglo[indice] - 1] == DERECHA_A_IZQUIERDA) {
            int temp = arreglo[indice];
            arreglo[indice] = arreglo[indice - 1];
            arreglo[indice - 1] = temp;
        } else {
            int temp = arreglo[indice];
            arreglo[indice] = arreglo[indice + 1];
            arreglo[indice + 1] = temp;
        }
        for (int i = 0; i < n; i++) {
            if (arreglo[i] > movil) {
                direcciones[arreglo[i] - 1] = !direcciones[arreglo[i] - 1];
            }
        }
        for (int i = 0; i < n; i++) {
            resultado[p][i] = arreglo[i];
        }
    }
    return resultado;
}

void imprimirPermutacion(int *permutacion, int n, cargas *first_list) {
    printf("Permutación:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", permutacion[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        int carga_index = permutacion[i] - 1;
        printf("Carga %d -> id_carga %d, id_proceso %d, orden %d, tiempo %d\n",
               carga_index + 1,
               first_list[carga_index].id_carga,
               first_list[carga_index].id_proceso,
               first_list[carga_index].orden_de_ejecucion,
               first_list[carga_index].tiempo);
    }
}

/*
Funcion para restringir el orden de las cargas; solo pueden ordenarse en sus respectivos procesos.
*/
int cumpleOrdenDeProceso(int *permutacion, int n, cargas *first_list) {
    for (int i = 0; i < n; i = i += 3) {
        int proceso = i/3 + 1;
        for (int j = 0; j < 3; j++) {
            int carga_index = permutacion[i + j] - 1;
            // verifico que la carga se encuentre en el proceso correspondiente
            if (first_list[carga_index].id_proceso != proceso) {
                return 0;     
            }
        }
    }
    return 1;
}




int calcularTiempo(int *permutacion, int n, cargas *first_list) {
    int tiempoMayor = 0;
    for (int i = 0; i < n; i += 3) {
        int tiempo = 0;
        for (int j = 0; j < 3; j++) {
            int carga_index = permutacion[i + j] - 1;
            tiempo += first_list[carga_index].tiempo;
        }
        if (tiempo > tiempoMayor) {
            tiempoMayor = tiempo;
        }
    }
    return tiempoMayor;
}

void imprimirMatriz(int **matriz, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}


/*
Funcion para restringir el orden de las cargas; solo pueden ordenarse en sus respectivos procesos.
*/
int cumpleOrdenDeProcesoM(int **matriz, int n, int m, cargas *first_list) {
    // itera sobre los procesos
    for (int i = 0; i < n; i++) {
        int proceso = i + 1;
        // itera sobre las filas
        for (int j = 0; j < m; j++) {
            int carga_index = matriz[i][j] - 1;
            // verifico que la carga se encuentre en el proceso correspondiente
            if (first_list[carga_index].id_proceso != proceso) {
                return 0;
            }
        }
    }
    return 1;
}


int cargasSuperpuestas(int *permutacion, int n, cargas *first_list) {
    int tiempoMayor = 0;
    for (int i = 3; i < n; i += 3) {
        int k = i;
        while (k > 0) {
            int tiempoAcumuladoActual = 0;
            int tiempoAcumuladoAnterior = 0;
            for (int j = 0; j < 3; j++) {
                int carga_index_anterior = permutacion[k - 3 + j] - 1;
                int carga_index_actual = permutacion[i + j] - 1;
                int mayorTiempoActual = first_list[carga_index_actual].tiempo + tiempoAcumuladoActual;
                int mayorTiempoAnterior = first_list[carga_index_anterior].tiempo + tiempoAcumuladoAnterior;
                
                if (first_list[carga_index_anterior].id_carga == first_list[carga_index_actual].id_carga) {
                    return 0;
                }
                
            }
            k = k - 3;
        }
    }
    return 1;
}





/* 
la permutacion ganadora seria:
#34939:
Permutación:
1 4 8 7 2 6 5 3 9 
Carga 1 -> id_carga 1, id_proceso 1, orden 1, tiempo 3
Carga 4 -> id_carga 2, id_proceso 1, orden 1, tiempo 2
Carga 8 -> id_carga 3, id_proceso 1, orden 2, tiempo 2
Carga 7 -> id_carga 3, id_proceso 2, orden 1, tiempo 3
Carga 2 -> id_carga 1, id_proceso 2, orden 2, tiempo 3
Carga 6 -> id_carga 2, id_proceso 2, orden 3, tiempo 4
Carga 5 -> id_carga 2, id_proceso 3, orden 2, tiempo 3
Carga 3 -> id_carga 1, id_proceso 3, orden 3, tiempo 3
Carga 9 -> id_carga 3, id_proceso 3, orden 3, tiempo 1
*/

// MAIN
//================
int main(int argc, char *argv[]) {
    int i, j, n, m, true_n;
    cargas *first_list = NULL;
    int *aux_list = NULL;
    int num_permutaciones;
    
    leerArchivo(argv[1], &n, &m, &first_list, &true_n, &aux_list);

    // creamos las permutaciones 
    int **permutaciones = generarPermutaciones(aux_list, true_n, &num_permutaciones);
    
    int ***planificacion = (int ***)malloc(num_permutaciones * sizeof(int **));
    for (int i = 0; i < num_permutaciones; i++) {
        planificacion[i] = (int **)malloc(n * sizeof(int *));
        for (int j = 0; j < n; j++) {
            planificacion[i][j] = (int *)malloc(m * sizeof(int));
            for (int k = 0; k < m; k++) {
                planificacion[i][j][k] = permutaciones[i][j * m + k];
            }
        }
    }

    /*

    // imprimimos las permutaciones, usando la lista first_list que contiene todos los struct cargas
    int cantidadSoluciones = 1;
    for (i = 0; i < num_permutaciones; i++) {
        if (cumpleOrdenDeProceso(permutaciones[i], true_n, first_list) == 1 && cargasSuperpuestas(permutaciones[i], true_n, first_list) == 1) {
            int tiempo = calcularTiempo(permutaciones[i], true_n, first_list);
            printf("Solución N°: %d. Tiempo: %d.\n", cantidadSoluciones, tiempo);
            printf("#%d:\n", i + 1);
            imprimirPermutacion(permutaciones[i], true_n, first_list);
            printf("\n");
            cantidadSoluciones++;
        }
    }

    
    */
    int cantidadSolucionesM = 1;
    // Imprimir la planificación
    for (int i = 0; i < num_permutaciones; i++) {
        if (cumpleOrdenDeProcesoM(planificacion[i], n, m, first_list) == 1) {
            printf("Solución N°: %d.\n", cantidadSolucionesM);
            printf("Permutación %d:\n", i + 1);
            imprimirMatriz(planificacion[i], n, m);
            printf("\n");
            cantidadSolucionesM++;
        }     
    }
    

    for (i = 0; i < num_permutaciones; i++) {
        free(permutaciones[i]);
    }
    free(permutaciones);
    free(first_list);
    free(aux_list);
    free(planificacion);
    return 0;
}
