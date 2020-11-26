/*! \struct _avl
 *  \brief Brief struct description
 *
 *  Detailed description
 */


#ifndef AVL
#define AVL

#define Boolean int
#define TRUE 1
#define FALSE 0
#define ERRO -32000
#define MAX 46

typedef struct _avl AVL;

typedef char ITEM[MAX] ;

AVL	*avl_criar(void);	
void avl_apagar(AVL	**arvore);	
Boolean avl_inserir(AVL	*T,	ITEM item);	
Boolean avl_remover(AVL	*T,	int	chave);	
ITEM* avl_buscar(AVL	*T,	int	chave);	
int avl_altura(AVL*T);	

#endif /* ifndef AVL */
