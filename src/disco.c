#include <stdio.h>
#include <stdlib.h>
#include "disco.h"

// inicializar disco con parametros
Disco *disco_crear(int tam_mb, int tam_bloque_kb) {
    
    Disco *d = malloc(sizeof(Disco));
    d->tam_bloque = tam_bloque_kb * 1024; // pasar de bytes a kb
    d->n_bloques = (tam_mb * 1024) / tam_bloque_kb; // calculo de bloques
    d->dueno = malloc(d->n_bloques * sizeof(int)); // reservar memoria para arreglo dueno[] de cada bloque   

    for (int i=0; i < d->n_bloques; ++i) {
        d->dueno[i] = LIBRE; // todos los bloques estan libres
    }
    return d;

} 

// liberar memoria ocupada por disco
void disco_destruir(Disco *d) {
    free(d->dueno);
    free(d);
}