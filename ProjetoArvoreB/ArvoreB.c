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
    while(i < raiz->n && (strcmp(elemento, raiz->chave[i]->nome) > 0)) i++; // Compara todas as chaves com a string buscada, se a string buscada tiver dps da chave na ordem alfabética ,i++

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

void splitChildren(no *pai, int pos, int ordem){
    no *menor = pai->filho[pos];
    no *maior = criarNo();

    maior->folha = menor->folha;

    int t = (ordem + 1)/2;

    for(int i = pai->n; i >= pos; i--){
        pai->filho[i + 1] = pai->filho[i];
        if(i != pai->n) pai->chave[i + 1] = pai->chave[i];
    }
    pai->filho[pos + 1] = maior;
    pai->chave[pos] = menor->chave[t - 1];
    pai->n++;

    for(int i = 0; i < t - 1; i++){
        if(!maior->folha) maior->filho[i] = menor->filho[t + i];
        maior->chave[i] = menor->chave[t + i];
        maior->n++;
    }
    maior->filho[maior->n] = menor->filho[menor->n];
    menor->n = t - 1;
}

void insereNaoCheio(no *raiz, char *elemento, int ordem){
    int pos = raiz->n - 1;

    if(raiz->folha){
        while(pos >= 0 && (strcmp(elemento, raiz->chave[pos]->nome) < 0)){
            raiz->chave[pos + 1] = raiz->chave[pos];
            pos--;
        }
        pos++; // Agora pos está na posição de inserção

        raiz->chave[pos]->nome = elemento;
        raiz->n++;
    }else{
        while(pos >= 0 && (strcmp(raiz->chave[pos]->nome, elemento) > 0)) pos--;
        pos++; // Agora pos é posição do filho que pode receber o elemento

        if(raiz->filho[pos]->n == ordem){
            splitChildren(raiz, pos, ordem);

            if(strcmp(raiz->chave[pos]->nome, elemento) < 0) pos++;
        }
        insereNaoCheio(raiz->filho[pos], elemento, ordem);
    }
}

void insercaoCLRS(no **raiz, char *elemento){
    ajustaNome(elemento);

    if(*raiz == NULL){
        *raiz = criaNo();
        (*raiz)->chave[0]->nome = padronizaNome(elemento);
        (*raiz)->n++;
        return;
    }

    if((*raiz)->n == ordem){
        no *novo = criaNo();
        novo->folha = 0;
        novo->filho[0] = *raiz;

        splitChildren(novo, 0, ordem);

        *raiz = novo;
    }
    insereNaoCheio(*raiz, elemento, ordem);
}

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
