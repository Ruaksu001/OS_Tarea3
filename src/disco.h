#ifndef DISCO_H
#define DISCO_H

#define LIBRE -1

typedef struct {
    int n_bloques; // cantidad de bloques
    int tam_bloque; // bytes
    int *dueno;
} Disco;

// inicializar disco
Disco *disco_crear(int tam_mb, int tam_bloque_kb);

// liberar memoria ocupada por disco
void disco_destruir(Disco *d);

// imprimir disco en terminal
void imprimir_disco(Disco *d);

#endif