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
        novo->chave[i]->nome = NULL;
    }

    novo->filho = malloc(sizeof(no*) * (ordem + 1));
    for(int i= 0; i < ordem + 1; i++){
        novo->filho[i] = NULL;
    }

    return novo;
}

char* padronizaNome(char *nome){ // Padroniza para a struct
    char *base = "\imagens\";
    size_t total = strlen(base) + strlen(nome) + 1;
    char *nomeNovo = malloc(total);

    memcpy(nomeNovo, base, strlen(base));
    memcpy(nomeNovo + strlen(base), nome, strlen(nome));
    nomeNovo[total - 1] = '\0';

    return nomeNovo;
}

void ajustaNome(char *nome){ // Ajusta para a busca
    for(int i = 0; i < strlen(nome); i++){
        if(nome[i] == ' ') nome[i] = '_';
        if(nome[i] >= 65 && nome[i]<=90){
            nome[i] = nome[i] + 32;
        }
    }
}

no* busca(no* raiz, char *elemento){
    if(raiz == NULL){
        return NULL;
    }

    int i = 0;
    while(i < raiz->n && (strcmp(elemento, raiz->chave[i]->nome) > 0 )) i++; // Compara todas as chaves com a string buscada, se a string buscada tiver dps da chave na ordem alfabética ,i++

    if(i < raiz->n && (strcmp(elemento, raiz->chave[i]->nome) == 0 )){
        return raiz;
    }else{
        if(!raiz->folha){
            busca(raiz->filho[i], elemento);
        }else{
            printf("Spell nao esta na lista!\n");
            return;
        }
    }
}

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
