/*! \struct _avlrec
 *  \brief Brief struct description
 *
 *  Detailed description
 */


#ifndef AVLrec_HEADER
#define AVLrec_HEADER

#define Boolean int
#define TRUE 1
#define FALSE 0
#define ERRO -32000
#define ERRO_STRING "ERROR 47389204710378 abcdefg"
#define MAXREC 46

typedef struct NOREC *AVLREC;

typedef struct itemrec{
    char palavra[MAXREC];
    int recorrencia;
}ITEMREC;

AVLREC* avlrec_criar();
Boolean avlrec_apagar(AVLREC *arvore);
Boolean avlrec_inserir(AVLREC *T, char item[MAXREC]);
Boolean avlrec_remover(AVLREC *T, char *chave);
ITEMREC* avlrec_buscar(AVLREC *T, char *chave);
int avlrec_altura(AVLREC*T);
ITEMREC* avlrec_toarray(AVLREC *arvore, int *tam);
void avlrec_imprimir(AVLREC *T);

#endif /* ifndef AVLrec_HEADER */
