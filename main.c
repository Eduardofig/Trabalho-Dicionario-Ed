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
    int diferenca = recorrente_a->recorrencia - recorrente_b->recorrencia;
    return diferenca == 0? strcmp(recorrente_a->palavra, recorrente_b->palavra) : diferenca; /*DOUBLE CHECK*/
}

int main(int argc, char *argv[])
{
    int seletor, i, seletor_atualizacao, indice_dicionario,n_palavras_recorrentes, tamanho_arr_recorrentes;
    ITEM chave, char_flag, palavra, *recorrencia;
    Boolean flag = TRUE, funcionou;
    DICIONARIO *dicionarios[3];
    ITEMREC recorrentes, *recorrentes_aux;
    ITEMREC *array_recorrentes;
    AVLREC *AVLrec;

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
                if (dicionarios[indice_dicionario] != NULL) {
                    AVLrec = avlrec_criar();
                    scanf("%s", recorrentes.palavra);
                    while (strcmp(recorrentes.palavra, "#") != 0) {;
                        /*Busca da palavra no dicionario, caso ache entra no if*/
                        recorrencia = avl_buscar(dicionarios[indice_dicionario]->avl, recorrentes.palavra);
                        if (strcmp(*recorrencia, ERRO_STRING) != 0) {
                            recorrentes_aux = avlrec_buscar(AVLrec, recorrentes.palavra);
                            if (strcmp(recorrentes_aux->palavra, ERRO_STRING) != 0) {
                                ++recorrentes_aux->recorrencia;
                            } else {
                                avlrec_inserir(AVLrec, recorrentes.palavra);
                            }
                        } else {
                            /*Caso nao ache, imprime a palavra*/
                            printf("%s\n", recorrentes.palavra);
                        }
                        scanf("%s", recorrentes.palavra);
                    }
                    array_recorrentes = avlrec_toarray(AVLrec, &tamanho_arr_recorrentes);
                    qsort(array_recorrentes, tamanho_arr_recorrentes, sizeof(ITEMREC), comparador_recorrentes);
                    for (i = 0; i < (n_palavras_recorrentes > tamanho_arr_recorrentes? tamanho_arr_recorrentes : n_palavras_recorrentes); ++i) {
                        printf("%s %d\n", array_recorrentes[i].palavra, array_recorrentes[i].recorrencia);
                    }
                    free(array_recorrentes);
                    avlrec_apagar(AVLrec);
                    AVLrec = NULL;
                    break;
                }
                printf("DICIONARIO %d INEXISTENTE\n", indice_dicionario + 1);
                break;
            default:
                flag = FALSE;
                break;
        }
    }
    return 0;
}
