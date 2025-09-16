#ifndef ARVOREB_H
#define ARVOREB_H

#define MAX 4;

typedef struct no{
    int n;
    char *chave[MAX]; // usaremos strdup para colocar os nomes de chave
    struct no* filho[MAX + 1];
    int folha;
    int nivelSpell;
}no;

no* criaNo();

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

void limpar(no *raiz);

#endif
