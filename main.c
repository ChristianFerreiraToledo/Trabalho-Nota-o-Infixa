#include <stdio.h>
#include <stdlib.h>

typedef struct elemento{
    char caracter;
    struct elemento *proximo;
}ELEMENTO;

typedef struct pilha{
    ELEMENTO* topo;
}PILHA;

PILHA* criar_pilha(){
    PILHA *pilha = malloc(sizeof(PILHA));
    pilha->topo = NULL;
    return pilha;
}

void empilhar(PILHA *pilha, char caracter){
    ELEMENTO *celula = (ELEMENTO*) malloc(sizeof(ELEMENTO));
    celula->proximo = pilha->topo;
    pilha->topo = celula;
    celula->caracter = caracter;
    
    return;
}

char desempilhar(PILHA *pilha){
    if(pilha->topo == NULL){
        return -1;
    }

    ELEMENTO *auxiliar = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    char caracterAuxiliar = auxiliar->caracter;
    free(auxiliar);

    return caracterAuxiliar;
}

void liberarElementos(ELEMENTO *celula){
    if(celula == NULL){
        return;
    }

    liberarElementos(celula->proximo);
    free(celula);
}

void liberarPilha(PILHA *pilha){
    liberarElementos(pilha->topo);
    free(pilha);
    return;
}

int main(int argc, char * argv[]){


    return 0;
}