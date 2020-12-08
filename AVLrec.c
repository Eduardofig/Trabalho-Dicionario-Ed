#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "AVLrec.h"

struct NOREC{
    ITEMREC info;
    int altura;
    struct NOREC *esq;
    struct NOREC *dir;
};

int rec_maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

AVLREC* avlrec_criar(){
    AVLREC* raiz = (AVLREC*) malloc(sizeof(AVLREC));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void rec_apaga_No(AVLREC no){
    if(no == NULL)
        return;
    rec_apaga_No(no->esq);
    rec_apaga_No(no->dir);
    free(no);
    no = NULL;
}

Boolean avlrec_apagar(AVLREC *arvore){
    if(*arvore == NULL)
        return FALSE;
    rec_apaga_No(*arvore);//libera todos os nos
    free(arvore);//libera a raiz
    return TRUE;
}

int rec_altura_NO(AVLREC no){
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

int rec_fatorBalanceamento_NO(AVLREC no){
    return labs(rec_altura_NO(no->esq) - rec_altura_NO(no->dir));   /*Retornando valor em módulo do fator de balanciamento*/
}

/*Funcoes de rotacao*/
//Esquerda
void rec_RotacaoEsq(AVLREC *av){
    struct NOREC *aux;
    /*Rodando a arvore*/
    aux = (*av)->esq;
    (*av)->esq = aux->dir;
    aux->dir = *av;
    /*Atualizando alturas dos nos*/
    (*av)->altura = rec_maior(rec_altura_NO((*av)->esq), rec_altura_NO((*av)->dir)) + 1;
    aux->altura = rec_maior(rec_altura_NO(aux->esq), (*av)->altura) + 1;
    *av = aux;
}

//Direita
void rec_RotacaoDir(AVLREC *av){
    struct NOREC *aux;
    /*Rodando a arvore*/
    aux = (*av)->dir;
    (*av)->dir = aux->esq;
    aux->esq = (*av);
    /*Atualizando alturas dos nos*/
    (*av)->altura = rec_maior(rec_altura_NO((*av)->esq), rec_altura_NO((*av)->dir)) + 1;
    aux->altura = rec_maior(rec_altura_NO(aux->dir), (*av)->altura) + 1;
    (*av) = aux;
}

//Superior Esquerda, Inferior Direita
void rec_RotacaoDuplaEsqDir(AVLREC *av){
    rec_RotacaoDir(&(*av)->esq);
    rec_RotacaoEsq(av);
}

//Superior Direita, Inferior Esquerda
void rec_RotacaoDuplaDirEsq(AVLREC *av){
    rec_RotacaoEsq(&(*av)->dir);
    rec_RotacaoDir(av);
}
/*Fim funcoes de rotacao*/


Boolean avlrec_inserir(AVLREC *T, char item[MAXREC]){
    int res = FALSE;
    if(*T == NULL){//arvore vazia ou no folha
        struct NOREC *novo;
        novo = (struct NOREC*)malloc(sizeof(struct NOREC));
        if(novo == NULL)
            return FALSE;

        strcpy(novo->info.palavra, item);
        novo->info.recorrencia = 1;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *T = novo;
        return TRUE;
    }

    struct NOREC *atual = *T;
    if(strcmp(item, atual->info.palavra) < 0){
        if((res = avlrec_inserir(&(atual->esq), item)) == 1){
            //Verificando se é necessário realzar rotacoes
            if(rec_fatorBalanceamento_NO(atual) >= 2){
                //Verificando se a rotacao é unica
                if(strcmp(item, (*T)->esq->info.palavra) < 0){
                    rec_RotacaoEsq(T);
                }else{
                    rec_RotacaoDuplaEsqDir(T);
                }
            }
        }
    }else{
        if(strcmp(item, atual->info.palavra) > 0){
            if((res = avlrec_inserir(&(atual->dir), item)) == 1){
                //Verificando se é necessário realzar rotacoes
                if(rec_fatorBalanceamento_NO(atual) >= 2){
                    //Verificando se a rotacao é unica
                    if(strcmp((*T)->dir->info.palavra, item) < 0){
                        rec_RotacaoDir(T);
                    }else{
                        rec_RotacaoDuplaDirEsq(T);
                    }
                }
            }
        }else{
            return ERRO;
        }
    }

    atual->altura = rec_maior(rec_altura_NO(atual->esq),rec_altura_NO(atual->dir)) + 1;

    return res;
}

AVLREC rec_procuraMenor(AVLREC atual){
    AVLREC no1 = atual;
    AVLREC no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

Boolean avlrec_remover(AVLREC *T, char *chave){
    if(*T == NULL){// chave nao existe
        return ERRO;
    }

    int res;
    if(strcmp(chave, (*T)->info.palavra) < 0){
        if((res = avlrec_remover(&(*T)->esq, chave)) == 1){
            //Verificando se é necessário realzar rotacoes
            if(rec_fatorBalanceamento_NO(*T) >= 2){
                //Verificando se a rotacao é unica
                if(rec_altura_NO((*T)->dir->esq) <= rec_altura_NO((*T)->dir->dir))
                    rec_RotacaoDir(T);
                else
                    rec_RotacaoDuplaDirEsq(T);
            }
        }
    }

    if(strcmp((*T)->info.palavra, chave) < 0){
        if((res = avlrec_remover(&(*T)->dir, chave)) == 1){
            //Verificando se é necessário realzar rotacoes
            if(rec_fatorBalanceamento_NO(*T) >= 2){
                //Verificando se a rotacao é unica
                if(rec_altura_NO((*T)->esq->dir) <= rec_altura_NO((*T)->esq->esq) )
                    rec_RotacaoEsq(T);
                else
                    rec_RotacaoDuplaEsqDir(T);
            }
        }
    }

    if(!strcmp((*T)->info.palavra, chave)){
        if(((*T)->esq == NULL || (*T)->dir == NULL)){// tem 1 filho ou nenhum
            AVLREC aux = (*T);
            if((*T)->esq != NULL)
                *T = (*T)->esq;
            else
                *T = (*T)->dir;
            free(aux);
        }else { // tem 2 filhos
            AVLREC temp = rec_procuraMenor((*T)->dir);
            strcpy((*T)->info.palavra, temp->info.palavra);
            avlrec_remover(&(*T)->dir, (*T)->info.palavra);

            //Verificando se é necessário realzar rotacoes
            if(rec_fatorBalanceamento_NO(*T) >= 2){
                //Verificando se a rotacao é unica
                if(rec_altura_NO((*T)->esq->dir) <= rec_altura_NO((*T)->esq->esq))
                    rec_RotacaoEsq(T);
                else
                    rec_RotacaoDuplaEsqDir(T);
            }
        }
        if (*T != NULL)
            (*T)->altura = rec_maior(rec_altura_NO((*T)->esq),rec_altura_NO((*T)->dir)) + 1;
        return TRUE;
    }

    (*T)->altura = rec_maior(rec_altura_NO((*T)->esq),rec_altura_NO((*T)->dir)) + 1;

    return res;
}

ITEMREC* avlrec_buscar(AVLREC *T, char *chave){
    if(T == NULL)
        return NULL;
    AVLREC atual = *T;
    while(atual != NULL){
        if(!strcmp(chave, atual->info.palavra)){
            return &(atual->info);
        }
        if(strcmp(chave, atual->info.palavra) > 0)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return NULL;
}

int avlrec_altura(AVLREC*T){
    return (*T)->altura;
}

int avlrec_inserearray(AVLREC arvore, ITEMREC* array, int i){
    if (arvore == NULL) return i;
    i = avlrec_inserearray(arvore->esq, array, i);
    array[i] = arvore->info;
    i = avlrec_inserearray(arvore->dir, array, i+1);
    return i;
}

ITEMREC* avlrec_toarray(AVLREC *arvore, int *tam){
    ITEMREC *array;

    if (*arvore == NULL) {
        (*tam) = 0;
        return NULL;
    }

    int tammax = (int) pow(2, (*arvore)->altura)+1;
    array = (ITEMREC*) malloc(sizeof(ITEMREC)*tammax);
    
    if(array == NULL){
        (*tam) = 0;
        return NULL;
    }

    (*tam) = avlrec_inserearray(*arvore, array, 0);
    return array;
}

void avlrec_imprimir_no(AVLREC no) {
  if (no == NULL) {
    return;
  }
  avlrec_imprimir_no(no->esq);
  printf("%s %d\n", no->info.palavra, no->info.recorrencia);
  avlrec_imprimir_no(no->dir);
  return;
}

void avlrec_imprimir(AVLREC *T) {
  if (T == NULL) {
    return;
  }
  avlrec_imprimir_no(*T);
  return;
}
