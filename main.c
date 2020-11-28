#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVL.h"

typedef struct _dicionario
{
    int id;
    AVL* avl;
}DICIONARIO;

int main(int argc, char *argv[])
{
    int seletor, i, seletor_atualizacao, indice_dicionario;
    char chave[20], char_flag[20];
    ITEM palavra;
    Boolean flag = TRUE, funcionou;
    DICIONARIO *dicionarios[3];

    for (i = 0; i < 3; ++i) {
        dicionarios[i] = NULL;
    }

    while (flag) {
        scanf("%d", &seletor);
        switch (seletor) {
            case 1:
                funcionou = FALSE;
                for (i = 0; i < 3; ++i) {
                    if (dicionarios[i] == NULL) {
                        dicionarios[i] = (DICIONARIO*) malloc(sizeof(DICIONARIO));
                        dicionarios[i]->avl = avl_criar();
                        dicionarios[i]->id = i + 1;
                        scanf("%s", palavra);
                        while (strcmp(palavra, "#")) {
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
                            funcionou = avl_remover(dicionarios[indice_dicionario]->avl, chave);
                            printf(funcionou? "%s EXCLUIDA DE %d\n" : "%s INEXISTENTE EM %d", chave, dicionarios[indice_dicionario]->id);
                        } else {
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
                    avl_apagar(dicionarios[indice_dicionario]->avl);
                    free(dicionarios[indice_dicionario]);
                    dicionarios[indice_dicionario] = NULL;
                    funcionou = TRUE;
                }
                printf(funcionou? "DICIONARIO %d APAGADO\n" : "DICIONARIO %d INEXISTENTE", indice_dicionario + 1);
                break;
            default:
                flag = FALSE;
                break;
        }
    }

    return 0;
}
