#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"

typedef struct _dicionario
{
    int id;
    AVL* avl;
}DICIONARIO;

typedef struct _recorrentes
{
    ITEM palavra;
    int recorrencias;
}RECORRENTES;

typedef struct _arrayRecorrentes
{
    RECORRENTES *array;
    int usado;
    size_t tamanho;
} ARRAY_RECORRENTES;

void initArray(ARRAY_RECORRENTES *a, size_t tamanho_inicial)
{
    a->array = malloc(tamanho_inicial * sizeof(RECORRENTES));
    a->usado = 0;
    a->tamanho = tamanho_inicial;
}

void insertArray(ARRAY_RECORRENTES *a, RECORRENTES elemento)
{
    // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
    // Therefore a->used can go up to a->size
    if (a->usado == a->tamanho) {
        a->tamanho *= 2;
        a->array = realloc(a->array, a->tamanho * sizeof(RECORRENTES));
    }
    a->array[a->usado++] = elemento;
}

void freeArray(ARRAY_RECORRENTES *a)
{
    free(a->array);
    a->array = NULL;
    a->usado = a->tamanho = 0;
}

int comparador_recorrentes(const void *a, const void *b)
{
    RECORRENTES *recorrente_a = (RECORRENTES *)a;
    RECORRENTES *recorrente_b = (RECORRENTES *)b;
    return (recorrente_a->recorrencias - recorrente_b->recorrencias);
}

int main(int argc, char *argv[])
{
    int seletor, i, seletor_atualizacao, indice_dicionario, n_palavras, n_palavras_recorrentes;
    ITEM chave, char_flag, palavra, *recorrencia;
    Boolean flag = TRUE, funcionou, ja_inserido;
    DICIONARIO *dicionarios[3];
    RECORRENTES recorrentes;
    ARRAY_RECORRENTES *array_recorrentes;


    for (i = 0; i < 3; ++i) {
        dicionarios[i] = NULL;
    }

    while (flag) {
        scanf("%d", &seletor);
        switch (seletor) {
            case 1:
                funcionou = FALSE;
                for (i = 0; i < 3; ++i) {
                    /*Itera pelo array de dicionarios ate achar um que ainda nao foi alocado*/
                    if (dicionarios[i] == NULL) {
                        /*Alocacao do dicionario*/
                        dicionarios[i] = (DICIONARIO*) malloc(sizeof(DICIONARIO));
                        dicionarios[i]->avl = avl_criar();
                        dicionarios[i]->id = i + 1;
                        /*Insercao das palavras*/
                        scanf("%s", palavra);
                        while (strcmp(palavra, "#") != 0) {
                            avl_inserir(dicionarios[i]->avl, palavra);
                            /*PALAVRAS REPETIDAS DEVEM SER IGNORADAS, TRATAR ESSA EXCESSAO NO TAD*/
                            scanf("%s", palavra);
                        }
                        funcionou = TRUE;
                        break;
                    }
                }
                funcionou? printf("DICIONARIO %d CRIADO\n", dicionarios[i]->id): printf("IMPOSSIVEL CRIAR\n");
                break;
            case 2:
                scanf("%d", &indice_dicionario);
                --indice_dicionario;
                if (dicionarios[indice_dicionario] != NULL) {
                    scanf("%s", char_flag);
                    while (strcmp(char_flag, "#") != 0) {
                        scanf("%s", palavra);
                        seletor_atualizacao = atoi(char_flag);
                        if (seletor_atualizacao == 0) {
                            /*Remocao de palavra do dicionario*/
                            funcionou = avl_remover(dicionarios[indice_dicionario]->avl, chave);
                            printf(funcionou? "%s EXCLUIDA DE %d\n" : "%s INEXISTENTE EM %d", chave, dicionarios[indice_dicionario]->id);
                        } else {
                            /*Insercao de palavra no dicionario*/
                            funcionou = avl_inserir(dicionarios[indice_dicionario]->avl, chave);
                            printf(funcionou? "%s INSERIDA EM %d\n" : "%s JA EXISTE EM %d", chave, dicionarios[indice_dicionario]->id);
                        }
                        scanf("%s", char_flag);
                    }
                    break;
                }
                printf("DICIONARIO %d INEXISTENTE\n", indice_dicionario + 1);
                break;
            case 3:
                funcionou = FALSE;
                scanf("%d", &indice_dicionario);
                --indice_dicionario;
                if (dicionarios[indice_dicionario] != NULL) {
                    /*Desalocacao do dicionario*/
                    avl_apagar(dicionarios[indice_dicionario]->avl);
                    free(dicionarios[indice_dicionario]);
                    dicionarios[indice_dicionario] = NULL;
                    funcionou = TRUE;
                }
                printf(funcionou? "DICIONARIO %d APAGADO\n" : "DICIONARIO %d INEXISTENTE", indice_dicionario + 1);
                break;
            case 4:
                scanf("%d %d", &indice_dicionario,&n_palavras_recorrentes);
                --indice_dicionario;
                funcionou = FALSE;
                if (dicionarios[indice_dicionario] != NULL) {
                    funcionou = TRUE;
                    initArray(array_recorrentes, sizeof(RECORRENTES));/*DOUBLE CHECK*/
                    scanf("%s", recorrentes.palavra);
                    while (strcmp(recorrentes.palavra, "#") != 0) {
                        ja_inserido = FALSE;
                        /*Busca da palavra no dicionario, caso ache entra no if*/
                        recorrencia = avl_buscar(dicionarios[indice_dicionario]->avl, recorrentes.palavra);
                        if (strcmp(recorrentes.palavra, ERRO_STRING) != 0) {
                            for (i = 0; i < array_recorrentes->usado; ++i) {
                                if (strcmp(recorrentes.palavra, array_recorrentes->array[i].palavra) == 0) {
                                    ++array_recorrentes->array[i].recorrencias;
                                    ja_inserido = TRUE;
                                    break;
                                }
                            }
                            if (!ja_inserido) {
                                insertArray(array_recorrentes, recorrentes);
                            }
                        } else {
                            /*Caso nao ache, imprime a palavra*/
                            printf("%s\n", recorrentes.palavra);
                        }
                        scanf("%s", recorrentes.palavra);
                    }
                }
                qsort(array_recorrentes->array,array_recorrentes->usado, sizeof(RECORRENTES), comparador_recorrentes);
                for (i = 0; i < n_palavras_recorrentes; ++i) {
                    printf("%s %d\n", array_recorrentes->array->palavra, array_recorrentes->array->recorrencias);
                }
                freeArray(array_recorrentes);
                break;
            default:
                flag = FALSE;
                break;
        }
    }

    return 0;
}
