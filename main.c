#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"
#include "AVLrec.h"

typedef struct _dicionario
{
    int id;
    AVL* avl;
}DICIONARIO;

int comparador_recorrentes(const void *a, const void *b)
{
    ITEMREC *recorrente_a = (ITEMREC *)a;
    ITEMREC *recorrente_b = (ITEMREC *)b;
    int diferenca = recorrente_b->recorrencia - recorrente_a->recorrencia;
    return diferenca == 0? strcmp(recorrente_a->palavra, recorrente_b->palavra) : diferenca; /*DOUBLE CHECK*/
}

int main(int argc, char *argv[])
{
    int seletor, i, seletor_atualizacao, indice_dicionario,n_palavras_recorrentes, tamanho_arr_recorrentes;
    ITEM char_flag, palavra, *recorrencia;
    Boolean flag = TRUE, funcionou;
    DICIONARIO *dicionarios[3];
    ITEMREC *recorrentes_aux, *array_recorrentes;
    AVLREC *AVLrec;
    AVL * AVLrejects;

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
                /*Caso nao seja possivel criar o dicionario*/
                if (!funcionou) {
                    scanf("%s", palavra);
                    while (strcmp(palavra, "#") != 0) {
                        scanf("%s", palavra);
                    }
                    printf("IMPOSSIVEL CRIAR\n");
                    break;
                }
                printf("DICIONARIO %d CRIADO\n", dicionarios[i]->id);
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
                            funcionou = avl_remover(dicionarios[indice_dicionario]->avl, palavra);
                            printf(funcionou == TRUE? "%s EXCLUIDA DE %d\n" : "%s INEXISTENTE EM %d\n", palavra, dicionarios[indice_dicionario]->id);
                        } else {
                            /*Insercao de palavra no dicionario*/
                            funcionou = avl_inserir(dicionarios[indice_dicionario]->avl, palavra);
                            printf(funcionou == TRUE? "%s INSERIDA EM %d\n" : "%s JA EXISTE EM %d\n", palavra, dicionarios[indice_dicionario]->id);
                        }
                        scanf("%s", char_flag);
                    }
                    break;
                }
                /*Caso o dicionario nao exista*/
                scanf("%s", char_flag);
                while (strcmp(char_flag, "#") != 0) {
                    scanf("%s", palavra);
                    scanf("%s", char_flag);
                }
                printf("DICIONARIO %d INEXISTENTE\n", indice_dicionario + 1);
                break;
            case 3:
                scanf("%d", &indice_dicionario);
                --indice_dicionario;
                if (dicionarios[indice_dicionario] != NULL) {
                    /*Desalocacao do dicionario*/
                    avl_apagar(dicionarios[indice_dicionario]->avl);
                    free(dicionarios[indice_dicionario]);
                    dicionarios[indice_dicionario] = NULL;
                    printf("DICIONARIO %d APAGADO\n", indice_dicionario + 1);
                    break;
                }
                printf("DICIONARIO %d INEXISTENTE\n", indice_dicionario + 1);
                break;
            case 4:
                scanf("%d %d", &indice_dicionario,&n_palavras_recorrentes);
                --indice_dicionario;
                if (dicionarios[indice_dicionario] != NULL) {
                    AVLrec = avlrec_criar();
                    AVLrejects = avl_criar();
                    scanf("%s", palavra);
                    while (strcmp(palavra, "#") != 0) {
                        /*Busca da palavra no dicionario, caso ache entra no if*/
                        recorrencia = avl_buscar(dicionarios[indice_dicionario]->avl, palavra);
                        if (recorrencia != NULL) {
                            recorrentes_aux = avlrec_buscar(AVLrec, palavra);
                            if (recorrentes_aux != NULL) {
                                ++recorrentes_aux->recorrencia;
                            } else {
                                avlrec_inserir(AVLrec, palavra);
                            }
                        } else {
                            /*Caso nao ache, imprime a palavra*/
                            avl_inserir(AVLrejects, palavra);
                        }
                        scanf("%s", palavra);
                    }
                    avl_imprimir(AVLrejects);
                    array_recorrentes = avlrec_toarray(AVLrec, &tamanho_arr_recorrentes);
                    qsort(array_recorrentes, tamanho_arr_recorrentes, sizeof(ITEMREC), comparador_recorrentes);
                    if (n_palavras_recorrentes <= 0) {
                        /*Para n menor que zero*/
                        printf("IMPOSSIVEL INFORMAR %d PALAVRAS MAIS FREQUENTES\n", n_palavras_recorrentes);
                        free(array_recorrentes);
                        avlrec_apagar(AVLrec);
                        avl_apagar(AVLrejects);
                        AVLrec = NULL;
                        break;
                    }
                    for (i = 0; i < (n_palavras_recorrentes > tamanho_arr_recorrentes? tamanho_arr_recorrentes : n_palavras_recorrentes); ++i) {
                        printf("%s %d\n", array_recorrentes[i].palavra, array_recorrentes[i].recorrencia);
                    }
                    free(array_recorrentes);
                    avlrec_apagar(AVLrec);
                    avl_apagar(AVLrejects);
                    AVLrec = NULL;
                    break;
                }
                /*Caso o dicionario nao exista*/
                scanf("%s", palavra);
                while (strcmp(palavra, "#")) {
                    scanf("%s", palavra);
                }
                printf("DICIONÁRIO INEXISTENTE\n");
                break;
            default:
                flag = FALSE;
                for (i = 0; i < 3; ++i) {
                    if (dicionarios[i] != NULL) {
                        avl_apagar(dicionarios[i]->avl);
                        free(dicionarios[i]);
                        dicionarios[i] = NULL;
                    }
                }
                break;
        }
    }
    return 0;
}
