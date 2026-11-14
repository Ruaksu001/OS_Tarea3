#include "disco.h"

int asignar_contigua(Disco *d, Archivo *a) {

    // bloques necesarios usando division redondeada hacia arriba
    int n = (a->tam_bytes + d->tam_bloque - 1) / d->tam_bloque;

    if (n > d->bloques_libres) {
        return ERR_SIN_ESPACIO;
    }

    // algoritmo utilizado: worst-fit
    // la unica razon por la cual elegimos worst-fit es "why not?"

    int mejor_inicio = -1; // donde empieza el espacio mas grande visto
    int mejor_largo = 0; // cuanto mide dicho bloque
    int inicio = -1; // donde empieza bloque que se esta recorriendo
    int largo = 0; // cuanto se ha recorrido

    for (int i = 0; i < d->n_bloques; ++i) {
        if (d->dueno[i] == LIBRE) {
            if (largo == 0) {
                inicio = i; // empieza un espacio nuevo
            }
            largo++; // se avanza en el bloque
            if (largo > mejor_largo) { // se evalua si supera al mas grande hasta ahora
                mejor_largo = largo; // espacio mas grande hasta ahora
                mejor_inicio = inicio;
            }
        } else {
            largo = 0; // el espacio se corto
        }
    }

    // el espacio mas grande no es suficiente para el archivo
    if (mejor_largo < n) {
        return ERR_FRAGMENTACION;
    }

    // marcar bloques como ocupados por el archivo
    for (int i = mejor_inicio; i < mejor_inicio + n; ++i) {
        d->dueno[i] = a->id;
    }
    a->inicio = mejor_inicio;
    a->n_bloques = n;
    d->bloques_libres -= n;
    return OK;
}