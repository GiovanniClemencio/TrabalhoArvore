#include "ArvoreB.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

no* criaNo(int ordem){
    no *novo = malloc(sizeof(no));
    if(novo == NULL){
        return NULL;
    }

    novo->n = 0;
    novo->folha = 1;

    novo->chave = malloc(sizeof(info) * ordem); // Aqui aloca dinamicamente os ponteiros de filhos
    if(novo->chave == NULL){
        free(novo);
        printf("Erro ao alocar chave na criacao de no\n");
        return NULL;
    }
    for(int i=0; i< ordem; i++){
        novo->chave[i].nome = NULL;
    }

    novo->filho = malloc(sizeof(no*) * (ordem + 1));
    if(novo->filho == NULL){
        free(novo->chave);
        free(novo);
        printf("Erro ao alocar filho na criacao de no\n");
        return NULL;
    }
    for(int i= 0; i < ordem + 1; i++){
        novo->filho[i] = NULL;
    }

    return novo;
}

char* padronizaNome(char *nome){ // Padroniza para a struct
    char *base = "imagens/";
    size_t total = strlen(base) + strlen(nome) + 5; // O + 5 é pq precisa de 4 chars para o ".png" e 1 para o '\0';

    char *nomeNovo = malloc(total);
    if(nomeNovo == NULL) return NULL;

    memcpy(nomeNovo, base, strlen(base));
    memcpy(nomeNovo + strlen(base), nome, strlen(nome));
    nomeNovo[total - 5] = '.';
    nomeNovo[total - 4] = 'p';
    nomeNovo[total - 3] = 'n';
    nomeNovo[total - 2] = 'g';
    nomeNovo[total - 1] = '\0';

    return nomeNovo;
}

void ajustaNome(char *nome){ // Ajusta para a busca
    if(nome == NULL) return;

    for(size_t i = 0; nome[i] != '\0'; i++){
        if(nome[i] == ' ') nome[i] = '_';
        if((unsigned char)nome[i] >= 'A' && (unsigned char)nome[i]<= 'Z'){
            nome[i] = (char)nome[i] + ('a' - 'A');
        }
    }
}

int arquivoExiste(const char *caminho){
    FILE *f = fopen(caminho, "r");
    if (f) {
        fclose(f);
        return 1; // existe
    }
    return 0; // não existe
}

no* busca(no* raiz, char *elemento){
    if(raiz == NULL) return NULL;

    if(!elemento) return;

    char *temporario = strdup(elemento);
    free(elemento);
    if(!temporario){
        printf("Erro ao criar copia do nome do spell em busca\n");
        return;
    }

    ajustaNome(temporario);

    char *caminho = padronizaNome(temporario);
    free(temporario);
    if(caminho == NULL){
        printf("Erro no malloc de caminho na busca\n");
        return;
    }

    int i = 0;
    while(i < raiz->n && (strcmp(caminho, raiz->chave[i].nome) > 0)) i++; // Compara todas as chaves com a string buscada, se a string buscada tiver dps da chave na ordem alfabética ,i++

    if(i < raiz->n && (strcmp(caminho, raiz->chave[i].nome) == 0 )){
        free(caminho);

        return raiz;
    }else{
        if(!raiz->folha){
            return busca(raiz->filho[i], caminho);
        }else{
            printf("Spell nao esta na lista!\n");
            free(caminho);

            return NULL;
        }
    }
}

void splitChildren(no *pai, int pos, int ordem){
    no *menor = pai->filho[pos];
    no *maior = criaNo(ordem);

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
        while(pos >= 0 && (strcmp(elemento, raiz->chave[pos].nome) < 0)){
            raiz->chave[pos + 1] = raiz->chave[pos];
            pos--;
        }
        pos++; // Agora pos está na posição de inserção

        raiz->chave[pos].nome = elemento;
        raiz->n++;
    }else{
        while(pos >= 0 && (strcmp(raiz->chave[pos].nome, elemento) > 0)) pos--;
        pos++; // Agora pos é posição do filho que pode receber o elemento

        if(raiz->filho[pos]->n == ordem){
            splitChildren(raiz, pos, ordem);

            if(strcmp(raiz->chave[pos].nome, elemento) < 0) pos++;
        }
        insereNaoCheio(raiz->filho[pos], elemento, ordem);
    }
}

void insercaoCLRS(no **raiz, const char *elemento_original, int ordem){
    if(!elemento_original) return;

    char *temporario = strdup(elemento_original);
    if(!temporario){
        printf("Erro ao criar copia do nome do spell em insercaoCLRS\n");
        return;
    }

    ajustaNome(temporario);

    char *caminho = padronizaNome(temporario);
    free(temporario);
    if(caminho == NULL){
        printf("Erro no malloc de caminho na insercaoCLRS\n");
        return;
    }

    if(!arquivoExiste(caminho)){
        printf("Spell nao existe: %s\n", caminho);
        free(caminho);
        return;
    }

    if(*raiz == NULL){
        *raiz = criaNo(ordem);
        if(raiz == NULL){
            printf("Erro ao criar raiz em insercaoCLRS\n");
            free(caminho);
            return;
        }

        (*raiz)->chave[0].nome = caminho;
        (*raiz)->n++;
        return;
    }

    if((*raiz)->n == ordem){
        no *novo = criaNo(ordem);
        if(novo == NULL){
            printf("Erro ao criar novo em insercaoCLRS\n");
            free(caminho);
            return;
        }

        novo->folha = 0;
        novo->filho[0] = *raiz;

        splitChildren(novo, 0, ordem);

        *raiz = novo;
    }
    insereNaoCheio(*raiz, caminho, ordem);
}

int predecessor(no *pai, int pos);

int sucessor(no *pai, int pos);

void rotEsq(no *pai, int pos);

void rotDir(no *pai, int pos);

void mergeChild(no *pai, int pos);

void remover(no *raiz, int elemento);

void imprimirRec(no* atual, int nivel){
    if(atual == NULL){
        return;
    }
    for(int i = 0; i < nivel; i++){
        printf(" ");
    }
    printf("[");
    for(int i = 0; i < atual->n; i++){
        printf("%s", atual->chave[i].nome);
        if(i + 1 != atual->n){
            printf(" , ");
        }
    }
    printf("]\n");

    for(int i = 0; i <= atual->n; i++){
        imprimirRec(atual->filho[i], nivel + 1);
    }
}

void imprimir(no* raiz){
    imprimirRec(raiz, 0);
}

void limpar(no *raiz){
    if(raiz == NULL) return;

    for(int i=0; i< raiz->n + 1; i++){
        limpar(raiz->filho[i]);
    }

    for(int i = 0; i < raiz->n; i++){
        free(raiz->chave[i].nome);
    }

    free(raiz->chave);
    free(raiz->filho);
    free(raiz);
}
