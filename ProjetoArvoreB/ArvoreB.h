#ifndef ARVOREB_H
#define ARVOREB_H

typedef struct info{
    char *nome; // usaremos strdup para colocar os nomes de chave
    int nivel;
}info;

typedef struct no{
    int n;
    info *chave;
    struct no **filho;
    int folha;
}no;

no* criaNo(int ordem);

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
