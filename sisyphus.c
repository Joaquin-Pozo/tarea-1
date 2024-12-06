#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define IZQUIERDA_A_DERECHA true
#define DERECHA_A_IZQUIERDA false

/* 
Hice todo de nuevo porque no entiendo bien como usas las cosas jfkjf asi que use todo lo mas simple que pude nomas
pero el j trotter es lo mismo que el tuyo pero en numeros (ahi si quieres lo revisas) pero lei directo en el main 
y guarde todo en unas listas simples

para compilar es puro gcc sisyphus.c y se ejecuta igual que siempre: ./NOMBREQUELEPUSISTE procesamiento_3_3.IN > ejemplo3.txt
(> ejemploN.txt) por si lo quieres guardar en el txt, pq ahora como imprimire todo hasta se demora jajaa


PD: guarde un procesamiento_3_3.IN afuera de la carpeta assets pq no uso assests aca jfjf

 */


//cada carga seria como una carga chica del txt
typedef struct {
    int id_carga;
    int id_proceso;
    int orden_de_ejecucion;
    int tiempo;
} cargas;


// le pase tu johnson trotter a chatgpt y le dije que lo hiciera solo con numeros
// funciona pero yo no entiendo nada jaja


// =================================
// AQUI INICIA J TROTTER (no me hago cargo pero funciona de pana)
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
// AQUI FINALIZA J TROTTER
// =================================


// funciona para imprimir las permutaciones, va a recibir:
// la lista permutable [1,2,..,n] con su tamaño y la lista de cargas (que seria como su ingrediente)
// con eso hace match al numero que le da la permutacion y las imprime
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

/*
Funcion para restringir cargas superpuestas; un proceso solo puede trabajar en una carga a la vez.
*/
int cargasSuperpuestas(int *permutacion, int n, cargas *first_list) {
    for (int i = 3; i < n; i += 3) {
        for (int j = 0; j < 3; j++) {
            int carga_index_anterior = permutacion[i - 3 + j] - 1;
            int carga_index_actual = permutacion[i + j] - 1;
            if (first_list[carga_index_anterior].id_carga == first_list[carga_index_actual].id_carga) {
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

int main(int argc, char *argv[]) {
    int i, j, n, m;
    FILE *file = fopen(argv[1], "r");
    fscanf(file, "%d %d", &n, &m);
    int true_n = n * m;
    cargas *first_list = (cargas *)malloc(true_n * sizeof(cargas)); //creo el espacio para n*m cargas
    int index = 0; 
    for (i = 0; i < n; i++) {
        for (j = 0; j < m * 2; j += 2) {
            int id_procesoFor, tiempoFor;
            fscanf(file, "%d %d", &id_procesoFor, &tiempoFor); //guardo el proceso y el tiemop en auxilaires
            first_list[index].id_carga = i + 1; // guardo la carga (su fila indica el n de la carga)
            first_list[index].id_proceso = id_procesoFor; // guardo el identificador del proceso
            first_list[index].orden_de_ejecucion = (j / 2) + 1; // guardo el orden (las columnas me indican que orden debe ejecutar cada carga)
            first_list[index].tiempo = tiempoFor; // el tiempo del proceso
            index++; //aumento el index, para completar los n*m elementos (ya que el for es hasta n)
        }
    }
    fclose(file);

    // lista auxliar dinamica que se crea de n*m; ejemplo: 3x3 = aux_lista = [1,2,3,4,5,6,7,8,9]
    // se inicia con 1 y se usara para crear las permutaciones
    int *aux_list = (int*)malloc(true_n * sizeof(int));
    for (i = 0; i < true_n; i++) {
        aux_list[i] = i + 1;
    }

    // creamos las permutaciones 
    int num_permutaciones;
    int **permutaciones = generarPermutaciones(aux_list, true_n, &num_permutaciones);

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


    /* 
    aqui ya faltaria guardar esas permutaciones[i] y guardarlas en una planificacion tipo pl[i][j] y convertimos
    las cargas como estan en la matriz.

    EJEMPLO:

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

    (si cachai el orden de los procesos estan bien, las primeras 3 van en el proceso 1 etc, por eso creo que funcionara asi de pana)
    y una idea de planificacion con esta seria como:

    cargas **planificacion[0][0] = Carga 1;
    cargas **planificacion[0][1] = Carga 4;
    cargas **planificacion[0][2] = Carga 8;
    cargas **planificacion[1][0] = Carga 7;
    cargas **planificacion[1][1] = Carga 2;
    cargas **planificacion[1][2] = Carga 6;
    cargas **planificacion[2][0] = Carga 5;
    cargas **planificacion[2][1] = Carga 3;
    cargas **planificacion[2][2] = Carga 9;

    Y DE AHI podemos aplicar las restricciones, tipo por columnas como dijo el gianello

    Pero por el momento tenemos la lista de permutaciones guardando las cargas en esas listas 

    */


    //liberamos todo re chill
    for (i = 0; i < num_permutaciones; i++) {
        free(permutaciones[i]);
    }
    free(permutaciones);
    free(first_list);
    free(aux_list);
    return 0;
}
