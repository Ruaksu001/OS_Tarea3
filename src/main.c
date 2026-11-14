#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

#include "disco.h"

int main() {
    int mb, kb, min_kb, max_kb;
    printf("Tamaño del disco (MB): ");
    scanf("%d", &mb);
    printf("Tamaño del bloque (KB): ");
    scanf("%d", &kb);
    printf("Tamaño mínimo de archivo (KB): ");
    scanf("%d", &min_kb);
    printf("Tamaño máximo de archivo (KB): ");
    scanf("%d", &max_kb);

    srand(time(NULL)); // seed para numeros aleatorios

    Disco *d = disco_crear(mb, kb);
    printf("Disco con %d bloques de %d bytes\n", d->n_bloques, d->tam_bloque);
    
    int siguiente_id = 0; // asignar id a archivos
    int resultado = OK;

    for(int t = 1; resultado == OK; t++) {
        sleep(1);

        // crear archivo cada 2 segundos
        if (t % 2 == 0) {
            Archivo a;
            a.id = siguiente_id;
            siguiente_id++;
            a.tam_bytes = (long)(min_kb + rand() % (max_kb - min_kb + 1)) * 1024;

            resultado = asignar_contigua(d, &a);

            if (resultado == OK) {
                agregar_archivo(d, a);
                printf("[t=%ds] Archivo %d: %ld KB, %d bloques desde el %d\n",
                       t, a.id, a.tam_bytes / 1024, a.n_bloques, a.inicio);
                imprimir_disco(d);
            } else if (resultado == ERR_SIN_ESPACIO) {
                printf("[t=%ds] Archivo %d (%ld KB) no cabe: sin espacio\n",
                       t, a.id, a.tam_bytes / 1024);
            } else {
                printf("[t=%ds] Archivo %d (%ld KB) no cabe: fragmentación externa\n",
                       t, a.id, a.tam_bytes / 1024);
            }
        }
    }

    printf("Fin de simulación. Archivos creados: %d\n", d->n_archivos);
    disco_destruir(d);
    return 0;
}