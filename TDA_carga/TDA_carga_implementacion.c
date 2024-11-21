#include <stdlib.h>
#include "TDA_carga.h"

carga* crea_carga(int id, int orden, int tiempo) {
    carga *nueva_carga = malloc(sizeof(carga));
    nueva_carga->id = id;
    nueva_carga->orden = orden;
    nueva_carga->tiempo = tiempo;
    return nueva_carga;
}

void destruye_carga(carga *c) {
    free(c);
}