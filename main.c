#include <stdio.h>
#include <string.h>
#include "AVL.h"

struct _avl
{
    int id;
};

int main(int argc, char *argv[])
{
    int seletor, n_palavras, n_dicionarios = 0;
    ITEM palavra;
    Boolean flag;
    AVL *dicionarios[3];

    while (flag == TRUE) {
        scanf("%d", &seletor);
        switch (seletor) {
            case 1:
                if (n_dicionarios < 3) {
                    dicionarios[n_dicionarios] = avl_criar();
                    dicionarios[n_dicionarios]->id = n_dicionarios + 1;
                    scanf("%d", &n_palavras);
                    for (int i = 0; i < n_palavras; ++i) {
                        scanf("%s", palavra);
                        printf("%d\n", avl_inserir(dicionarios[n_dicionarios], palavra));
                    }
                    printf("DICIONARIO %d CRIADO\n", dicionarios[n_dicionarios]->id);
                    ++n_dicionarios;
                } else {
                    printf("IMPOSSIVEL CRIAR\n");
                }
                break;
            default:
                flag = FALSE;
                break;
        }
    }

    return 0;
}
