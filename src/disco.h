#ifndef DISCO_H
#define DISCO_H

#define LIBRE -1

// codigos de error al asignar
#define OK 0
#define ERR_SIN_ESPACIO -1
#define ERR_FRAGMENTACION -2

typedef struct {
    int id;
    long tam_bytes; // tamano en bytes
    int inicio; // primer bloque
    int n_bloques; // cantidad de bloques que ocupa
} Archivo;

typedef struct {
    int n_bloques; // cantidad de bloques
    int tam_bloque; // bytes
    int bloques_libres; // contador de bloques libres
    int *dueno;

    Archivo *archivos; // archivos existentes
    int n_archivos; // numero de archivos
    int capacidad_archivos; // cuantos archivos caben en la memoria
} Disco;

// inicializar disco
Disco *disco_crear(int tam_mb, int tam_bloque_kb);

// liberar memoria ocupada por disco
void disco_destruir(Disco *d);

// imprimir disco en terminal
void imprimir_disco(Disco *d);

// agregar archivo a la lista de archivos
void agregar_archivo(Disco *d, Archivo a);

// asignacion contigua
int asignar_contigua(Disco *d, Archivo *a);

#endif