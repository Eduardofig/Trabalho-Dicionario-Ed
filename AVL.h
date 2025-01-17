/*! \struct _avl
 *  \brief Brief struct description
 *
 *  Detailed description
 */


#ifndef AVL_HEADER
#define AVL_HEADER

#define Boolean int
#define TRUE 1
#define FALSE 0
#define ERRO -32000
#define ERRO_STRING "ERROR 47389204710378 abcdefg"
#define MAX 46

typedef struct NO *AVL;

typedef char ITEM[MAX] ;

AVL* avl_criar();
Boolean avl_apagar(AVL *arvore);
Boolean avl_inserir(AVL *T, ITEM item);
Boolean avl_remover(AVL *T, char *chave);
ITEM* avl_buscar(AVL *T, char *chave);
int avl_altura(AVL*T);
void avl_imprimir(AVL *T);

#endif /* ifndef AVL_HEADER */
