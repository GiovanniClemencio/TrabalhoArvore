#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "ArvoreB.h"

int main()
{
    int ordem = 5; // O valor de ordem é pra ser inserido pelo usuário (é para ser o MAX)
    no *raiz= NULL;

    insercaoCLRS(&raiz, "aid", ordem);
    printf("\nInsere Aid: \n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "bless", ordem);
    printf("\nInsere bless: \n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "cure wounds", ordem);
    printf("\nInsere cure wounds: \n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "eldritch blast", ordem);
    printf("\nInsere eldritch blast: \n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "enthrall", ordem);
    printf("\nInsere enthrall: \n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "confusion", ordem);
    printf("\nInsere Confusion: \n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "color spray", ordem);
    printf("\nInsere color spray: \n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "fireball", ordem);
    printf("\nInsere firaball: \n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "power word kill", ordem);
    printf("\nInsere power word kill: \n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "tongues", ordem);
    printf("\nInsere tongues: \n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "creation", ordem);
    printf("\nInsere creation: \n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "awaken", ordem);
    printf("\nInsere awaken: \n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "scrying", ordem);
    printf("\nInsere scrying: \n");
    imprimir(raiz);

    remover(&raiz, "color spray", ordem);
    printf("\nRemovendo Color Spray\n");
    imprimir(raiz);

    remover(&raiz, "fireball", ordem);
    printf("\nRemovendo fireball\n");
    imprimir(raiz);

    printf("\nArvore final: \n");
    imprimir(raiz);

    limpar(raiz);
    return 0;
}
