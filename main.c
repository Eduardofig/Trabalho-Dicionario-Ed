#include <stdio.h>
#include <string.h>
#include "AVL.h"

struct _avl
{
    int id;
};

int main(int argc, char *argv[])
{
    int seletor, n_palavras, n_dicionarios = 0, i, j;
    ITEM palavra;
    Boolean flag;
    AVL *dicionarios[3];

    for (i = 0; i < 3; ++i) {
        dicionarios[i] = NULL;
    }

    while (flag) {
        scanf("%d", &seletor);
        switch (seletor) {
            case 1:
                for (i = 0; i < 3; ++i) {
                    if (dicionarios[i] == NULL) {
                        dicionarios[i] = avl_criar();
                        dicionarios[i]->id = i + 1;
                        scanf("%d", &n_palavras);
                        for (j = 0; j < n_palavras; ++j) {
                            scanf("%s", palavra);
                            printf("%d\n", avl_inserir(dicionarios[i], palavra));
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
