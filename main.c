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
    int seletor, n_palavras, n_dicionarios = 0, i, j;
    ITEM palavra;
    Boolean flag;
    DICIONARIO *dicionarios[3];

    for (i = 0; i < 3; ++i) {
        dicionarios[i] = NULL;
    }

    while (flag) {
        scanf("%d", &seletor);
        switch (seletor) {
            case 1:
                for (i = 0; i < 3; ++i) {
                    if (dicionarios[i] == NULL) {
                        dicionarios[i] = (DICIONARIO*) malloc(sizeof(DICIONARIO));
                        dicionarios[i]->avl = avl_criar();
                        dicionarios[i]->id = i + 1;
                        scanf("%d", &n_palavras);
                        for (j = 0; j < n_palavras; ++j) {
                            scanf("%s", palavra);
                            printf("%d\n", avl_inserir(dicionarios[i]->avl, palavra));
                        }
                        printf("DICIONARIO %d CRIADO\n", dicionarios[i]->id);
                        break;
                    }
                }
                printf("IMPOSSIVEL CRIAR\n");
                break;
            default:
                flag = FALSE;
                break;
        }
    }

    return 0;
}
