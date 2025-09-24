#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Minha struct dos "nós" da pilha
typedef struct celula{
    char valor;
    CELULA *proximo;
}CELULA;

//Minha pilha que sempre aponta para o ultima celula que entro na pilha
typedef struct pilha{
    CELULA *topo;
}PILHA;

//Função que cria minha pilha dinamicamente na Heap e retorna um enereço para funçao main na stack
PILHA *criar_pilha(){
    PILHA *endereço_pilha_na_heap;
    endereço_pilha_na_heap = (PILHA*)malloc(sizeof(PILHA));
    endereço_pilha_na_heap->topo = NULL;//começa vazia olhando para nada
    return endereço_pilha_na_heap; //retorna o enereço para localizar a pilha(topo) na heap
}

//Função que empilha minhas celulas na pilha,recebe como parâmetro o endereço da pilha e um caracter
void empilhar(PILHA *p,char caracter){
    CELULA *elemento = (CELULA*) malloc(sizeof(CELULA));
    elemento->proximo = p->topo;
    p->topo = elemento;
    elemento->valor = caracter;
    return;
}

//Função que desempilha uma celula(a ultima celula que entrou na pilha) e retorna o valor que esta armazenado nela
char desempilhar(PILHA *p){ //Unico parâmetro é a minha pilha(topo)
    if(p->topo == NULL){
        printf("A pilha esta vazia"); //verifica se minha pilha está vazia
        return -1;
    }
    CELULA *aux = p->topo;
    p->topo = p->topo->proximo;
    char salvar_caractere = aux->valor;
    free(aux); //apaga a celula para ela nao ficar peria na heap
    return salvar_caractere;
}
