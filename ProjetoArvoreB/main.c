#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "ArvoreB.h"

int main()
{
    int ordem = 5; // O valor de ordem é pra ser inserido pelo usuário (é para ser o MAX)
    no *raiz= NULL;

    insercaoCLRS(&raiz, "acid Splash", ordem);
    printf("\nInsere Acid Splash: \n");
    imprimir(raiz);
    insercaoCLRS(&raiz, "alter self", ordem);
    printf("\nInsere Alter Self: \n");
    imprimir(raiz);
    insercaoCLRS(&raiz, "blight", ordem);
    printf("\nInsere Blight: \n");
    imprimir(raiz);
    insercaoCLRS(&raiz, "color spray", ordem);
    printf("\nInsere Color Spray: \n");
    imprimir(raiz);
    insercaoCLRS(&raiz, "compulsion", ordem);
    printf("\nInsere Compulsion: \n");
    imprimir(raiz);

    printf("\nArvore antes de split na raiz\n");
    imprimir(raiz);

    insercaoCLRS(&raiz, "commune", ordem);
    printf("\nInsere Commmune: \n");
    imprimir(raiz);
    insercaoCLRS(&raiz, "aid", ordem);
    printf("\nInsere aid: \n");
    imprimir(raiz);
    insercaoCLRS(&raiz, "BLUR", ordem);
    printf("\nInsere blur: \n");
    imprimir(raiz);

    printf("\nArvore final: \n");
    imprimir(raiz);

    no* recebedor = busca(raiz, "commune");
    printf("\nNo encontrado na busca: \n");
    imprimir(recebedor);

    limpar(raiz);
    return 0;
}
