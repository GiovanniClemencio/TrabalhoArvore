#include "ArvoreB.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

no* criaNo(int ordem){
    no *novo = malloc(sizeof(no));
    if(novo == NULL){
        return 1;
    }

    novo->n = 0;
    novo->folha = 1;

    novo->chave = malloc(sizeof(info) * ordem); // Aqui aloca dinamicamente os ponteiros de filhos
    for(int i=0; i< ordem; i++){
        chave[i]->nome = NULL;
    }

    novo->filho = malloc(sizeof(no*) * (ordem + 1));
    for(int i= 0; i < ordem + 1; i++){
        novo->filho[i] = NULL;
    }

    return novo;
}

no* busca(no* raiz, int elemento);

void splitChildren(no *pai, int pos);

void insereNaoCheio(no *raiz, int elemento);

void insercaoCLRS(no **raiz, int elemento);

int predecessor(no *pai, int pos);

int sucessor(no *pai, int pos);

void rotEsq(no *pai, int pos);

void rotDir(no *pai, int pos);

void mergeChild(no *pai, int pos);

void remover(no *raiz, int elemento);

void imprimirRec(no* atual, int nivel);

void imprimir(no* raiz);

void limpar(no *raiz, int ordem){
    for(int i=0; i< ordem + 1; i++){
        limpar(raiz->filho[i], ordem);
    }

    for(int i = 0; i < ordem; i++){
        free(raiz->chave[i]->nome);
    }

    free(raiz->chave);
    free(raiz->filho);
    free(raiz);
}
