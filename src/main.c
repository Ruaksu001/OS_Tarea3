#include<stdio.h>
#include "disco.h"

int main() {
    int mb, kb;
    printf("Tamaño del disco (MB): ");
    scanf("%d", &mb);
    printf("Tamaño del bloque (KB): ");
    scanf("%d", &kb);

    Disco *d = disco_crear(mb, kb);
    printf("Disco con %d bloques de %d bytes\n", d->n_bloques, d->tam_bloque);
    imprimir_disco(d);

    disco_destruir(d);
    return 0;
}