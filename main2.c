#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLrec.h"

int main(int argc, char *argv[]){
    AVLREC *rec;
    
    rec = avlrec_criar();

    avlrec_inserir(rec, "ana");
    avlrec_inserir(rec, "julia");
    avlrec_inserir(rec, "claudia");
    avlrec_inserir(rec, "banana");
    avlrec_inserir(rec, "fernanda");
    avlrec_inserir(rec, "guilherme");
    avlrec_inserir(rec, "gabriel");
    avlrec_inserir(rec, "rafaela");
    avlrec_inserir(rec, "brian");
    avlrec_inserir(rec, "dudu");

    ITEMREC *arr;
    int tam;
    arr = avlrec_toarray(rec, &tam);

    for(int i = 0; i < tam; i++){
        printf("%s\n", arr[i].palavra);
    }

    free(arr);
    return 0;
}