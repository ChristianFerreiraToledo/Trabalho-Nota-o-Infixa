#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char *infixaParaPosfixa (char *inf) {
   int n = strlen (inf);
   char *posf; 
   posf = malloc ((n+1) * sizeof (char));
   PILHA *p;
   p = criar_pilha ();
   empilhar (p, inf[0]);       // empilha '('

   int j = 0;
   for (int i = 1; inf[i] != '\0'; ++i) {
      switch (inf[i]) {
         char x;
         case '(': empilhar (p, inf[i]);
                   break;
         case ')': x = desempilhar (p);
                   while (x != '(') {
                      posf[j++] = x;
                      x = desempilhar (p);
                   }
                   break;
         case '+' || '-': x = desempilhar (p);
                   while (x != '(') {
                      posf[j++] = x;
                      x = desempilhar (p);
                   }
                   empilhar (p, x);
                   empilhar (p, inf[i]);
                   break;
         case '*' || '/': x = desempilhar (p);
                   while (x != '(' && x != '+' && x != '-') {
                      posf[j++] = x;
                      x = desempilhar (p);
                   }
                   empilhar (p, x);
                   empilhar (p, inf[i]);
                   break;

         case '^': x = desempilhar(p);
                   while(x != '(' && x != '+' && x != '-' && x != '*' && x != '/'){
                    posf[j++] = x;
                    x = desempilhar(p);
                   }
                   empilhar(p, x);
                   empilhar(p, inf[i]);
                   break;
         default:  posf[j++] = inf[i];
      }
   }
   posf[j] = '\0';
   //printf("%p\n", (void*)p->topo);
   liberarPilha(p);
   //printf("%p\n", (void*)p->topo);  
   return posf;

}

int main(int argc, char * argv[]){

    char infixa[100];

    scanf("%s", infixa);

    char *posfixa = infixaParaPosfixa (infixa);

    printf("%s\n", posfixa);

    return 0;
}