#pragma once
/*------------- TDA carga -------------*/

/*------------- estructura de datos -------------*/

typedef struct { 
	int id; 
	int orden;
    int tiempo;
}carga;


/*------------- operaciones -------------*/

// crea_carga() retorna una nueva carga con un numero, orden y tiempo
carga* crea_carga(int id, int orden, int tiempo);

// destruye_carga() libera la memoria asignada a la carga c
void destruye_carga(carga *c);