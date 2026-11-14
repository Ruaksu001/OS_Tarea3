#include <stdio.h>
#include <stdlib.h>
#include "disco.h"

// inicializar disco con parametros
Disco *disco_crear(int tam_mb, int tam_bloque_kb) {
    
    Disco *d = malloc(sizeof(Disco));
    d->tam_bloque = tam_bloque_kb * 1024; // pasar de kb a bytes
    d->n_bloques = (tam_mb * 1024) / tam_bloque_kb; // calculo de bloques
    d->dueno = malloc(d->n_bloques * sizeof(int)); // reservar memoria para arreglo dueno[] de cada bloque   

    for (int i=0; i < d->n_bloques; ++i) {
        d->dueno[i] = LIBRE; // todos los bloques estan libres
    }

    d->bloques_libres = d->n_bloques; // al inicio todo esta libre

    d->n_archivos = 0;
    d->capacidad_archivos = 16;
    d->archivos = malloc(d->capacidad_archivos * sizeof(Archivo));

    return d;

} 

// liberar memoria ocupada por disco
void disco_destruir(Disco *d) {
    free(d->dueno);
    free(d->archivos);
    free(d);
}

void imprimir_disco(Disco *d) {
    if (d->n_bloques > 512) {
        return; // demasiado grande para mostrar en terminal
    }
    for (int i = 0; i < d->n_bloques; ++i) {
        if (d->dueno[i] == LIBRE) {
            printf(".");
        } else {
            printf("%c", 'A' + d->dueno[i] % 26); // recorrer abecedario
        }

        // salto de linea cada 64 bloques
        if ((i + 1) % 64 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void agregar_archivo(Disco *d, Archivo a) {
    // agrandar tabla si esta llena
    if (d->n_archivos == d->capacidad_archivos) {
        // duplicar capacidad
        d->capacidad_archivos *= 2;
        // agregar memoria
        d->archivos = realloc(d->archivos, d->capacidad_archivos * sizeof(Archivo));
    }
    // agregar archivo al disco
    d->archivos[d->n_archivos] = a;
    d->n_archivos++;
}