#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "AVL.h"

struct NO{
    ITEM info;
    int altura;
    struct NO *esq;
    struct NO *dir;
};

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

AVL* avl_criar(){
    AVL* raiz = (AVL*) malloc(sizeof(AVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void apaga_No(AVL no){
    if(no == NULL)
        return;
    apaga_No(no->esq);
    apaga_No(no->dir);
    free(no);
    no = NULL;
}

Boolean avl_apagar(AVL *arvore){
    if(*arvore == NULL)
        return FALSE;
    apaga_No(*arvore);//libera todos os nos
    free(arvore);//libera a raiz
    return TRUE;
}

int altura_NO(AVL no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

int fatorBalanceamento_NO(AVL no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));   /*Retornando valor em módulo do fator de balanciamento*/
}

/*Funcoes de rotacao*/
//Esquerda
void RotacaoEsq(AVL *av){
    struct NO *aux;
    /*Rodando a arvore*/
    aux = (*av)->esq;
    (*av)->esq = aux->dir;
    aux->dir = *av;
    /*Atualizando alturas dos nos*/
    (*av)->altura = maior(altura_NO((*av)->esq), altura_NO((*av)->dir)) + 1;
    aux->altura = maior(altura_NO(aux->esq), (*av)->altura) + 1;
    *av = aux;
}

//Direita
void RotacaoDir(AVL *av){
    struct NO *aux;
    /*Rodando a arvore*/
    aux = (*av)->dir;
    (*av)->dir = aux->esq;
    aux->esq = (*av);
    /*Atualizando alturas dos nos*/
    (*av)->altura = maior(altura_NO((*av)->esq), altura_NO((*av)->dir)) + 1;
    aux->altura = maior(altura_NO(aux->dir), (*av)->altura) + 1;
    (*av) = aux;
}

//Superior Esquerda, Inferior Direita
void RotacaoDuplaEsqDir(AVL *av){
    RotacaoDir(&(*av)->esq);
    RotacaoEsq(av);
}

//Superior Direita, Inferior Esquerda
void RotacaoDuplaDirEsq(AVL *av){
    RotacaoEsq(&(*av)->dir);
    RotacaoDir(av);
}
/*Fim funcoes de rotacao*/


Boolean avl_inserir(AVL *T, ITEM item){
    int res = FALSE;
    if(*T == NULL){//arvore vazia ou no folha
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return FALSE;

        strcpy(novo->info, item);
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *T = novo;
        return TRUE;
    }

    struct NO *atual = *T;
    if(strcmp(item, atual->info) < 0){
        if((res = avl_inserir(&(atual->esq), item)) == 1){
            //Verificando se é necessário realzar rotacoes
            if(fatorBalanceamento_NO(atual) >= 2){
                //Verificando se a rotacao é unica
                if(strcmp(item, (*T)->esq->info) < 0){
                    RotacaoEsq(T);
                }else{
                    RotacaoDuplaEsqDir(T);
                }
            }
        }
    }else{
        if(strcmp(item, atual->info) > 0){
            if((res = avl_inserir(&(atual->dir), item)) == 1){
                //Verificando se é necessário realzar rotacoes
                if(fatorBalanceamento_NO(atual) >= 2){
                    //Verificando se a rotacao é unica
                    if(strcmp((*T)->dir->info, item) < 0){
                        RotacaoDir(T);
                    }else{
                        RotacaoDuplaDirEsq(T);
                    }
                }
            }
        }else{
            return ERRO;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

AVL procuraMenor(AVL atual){
    AVL no1 = atual;
    AVL no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

Boolean avl_remover(AVL *T, char *chave){
    if(*T == NULL){// chave nao existe
        return ERRO;
    }

    int res;
    if(strcmp(chave, (*T)->info) < 0){
        if((res = avl_remover(&(*T)->esq, chave)) == 1){
            //Verificando se é necessário realzar rotacoes
            if(fatorBalanceamento_NO(*T) >= 2){
                //Verificando se a rotacao é unica
                if(altura_NO((*T)->dir->esq) <= altura_NO((*T)->dir->dir))
                    RotacaoDir(T);
                else
                    RotacaoDuplaDirEsq(T);
            }
        }
    }

    if(strcmp((*T)->info, chave) < 0){
        if((res = avl_remover(&(*T)->dir, chave)) == 1){
            //Verificando se é necessário realzar rotacoes
            if(fatorBalanceamento_NO(*T) >= 2){
                //Verificando se a rotacao é unica
                if(altura_NO((*T)->esq->dir) <= altura_NO((*T)->esq->esq) )
                    RotacaoEsq(T);
                else
                    RotacaoDuplaEsqDir(T);
            }
        }
    }

    if(!strcmp(chave, (*T)->info)){
        if(((*T)->esq == NULL || (*T)->dir == NULL)){// tem 1 filho ou nenhum
            AVL aux = (*T);
            if((*T)->esq != NULL)
                *T = (*T)->esq;
            else
                *T = (*T)->dir;
            free(aux);
        }else { // tem 2 filhos
            AVL temp = procuraMenor((*T)->dir);
            strcpy((*T)->info, temp->info);
            avl_remover(&(*T)->dir, (*T)->info);

            //Verificando se é necessário realzar rotacoes
            if(fatorBalanceamento_NO(*T) >= 2){
                //Verificando se a rotacao é unica
                if(altura_NO((*T)->esq->dir) <= altura_NO((*T)->esq->esq))
                    RotacaoEsq(T);
                else
                    RotacaoDuplaEsqDir(T);
            }
        }
        if (*T != NULL)
            (*T)->altura = maior(altura_NO((*T)->esq),altura_NO((*T)->dir)) + 1;
        return TRUE;
    }

    (*T)->altura = maior(altura_NO((*T)->esq),altura_NO((*T)->dir)) + 1;

    return res;
}

ITEM* avl_buscar(AVL *T, char *chave){
    if(T == NULL)
        return NULL;
    AVL atual = *T;
    while(atual != NULL){
        if(!strcmp(chave, atual->info)){
            return &(atual->info);
        }
        if(strcmp(chave, atual->info) > 0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return NULL;
}

int avl_altura(AVL*T){
    return (*T)->altura;
}
