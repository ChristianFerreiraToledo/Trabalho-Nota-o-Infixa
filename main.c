#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a struct elemento, usada na construção da pilha
typedef struct elemento{
    char caracter;
    struct elemento *proximo;
} ELEMENTO;

// Definindo a struct pilha
typedef struct pilha{
    ELEMENTO *topo;
} PILHA;

// Definindo a função criar pilha
PILHA *criar_pilha(){
    PILHA *pilha = malloc(sizeof(PILHA));
    pilha->topo = NULL;
    return pilha;
}

// Definindo a função empilhar
void empilhar(PILHA *pilha, char caracter){
    ELEMENTO *celula = (ELEMENTO *)malloc(sizeof(ELEMENTO));
    celula->proximo = pilha->topo;
    pilha->topo = celula;
    celula->caracter = caracter;

    return;
}

// Definindo a função desenpilhar
char desempilhar(PILHA *pilha){
    if (pilha->topo == NULL){
        return -1;
    }

    ELEMENTO *auxiliar = pilha->topo;
    pilha->topo = pilha->topo->proximo;
    char caracterAuxiliar = auxiliar->caracter;
    free(auxiliar);

    return caracterAuxiliar;
}

// Definindo a função liberar elementos, ou seja, limpa um elemento da pilha
void liberarElementos(ELEMENTO *celula){
    if (celula == NULL){
        return;
    }

    liberarElementos(celula->proximo);
    free(celula);
}

// Definindo a função liberar pilha, ou seja, limpa a pilha como um todo, no caso quando sobra só a pilha é NULL,
// se utilizar essa função ao imprimir o que contém em pilha será mostrado apenas o endereço de memória onde a pilha pilha foi alocada
void liberarPilha(PILHA *pilha){
    liberarElementos(pilha->topo);
    free(pilha);
    return;
}

// Definindo a função que trasformará a notação infixa para pósfixa
char *infixaParaPosfixa(char *inf){
    int tamanho = strlen(inf);
    char *posfixa;
    posfixa = malloc((tamanho + 1) * sizeof(char));
    PILHA *p;
    p = criar_pilha();
    empilhar(p, inf[0]); // empilha o primeiro elemento da notação infixa, esse código leva em consideração somente a notação que inicia com "("

    int j = 0;
    for (int i = 1; inf[i] != '\0'; ++i){
        char caracter;
        if (inf[i] != '\0'){
            if (inf[i] == '('){
                empilhar(p, inf[i]);
            }

            if (inf[i] == ')'){
                caracter = desempilhar(p);
                while (caracter != '('){
                    posfixa[j++] = caracter;
                    caracter = desempilhar(p);
                }
            }

            if (inf[i] == '+' || inf[i] == '-'){
                caracter = desempilhar(p);
                while (caracter != '('){
                    posfixa[j++] = caracter;
                    caracter = desempilhar(p);
                }
                empilhar(p, caracter);
                empilhar(p, inf[i]);
            }

            if (inf[i] == '*' || inf[i] == '/'){
                caracter = desempilhar(p);
                while (caracter != '(' && caracter != '+' && caracter != '-'){
                    posfixa[j++] = caracter;
                    caracter = desempilhar(p);
                }
                empilhar(p, caracter);
                empilhar(p, inf[i]);
            }

            if (inf[i] == '^'){
                caracter = desempilhar(p);
                while (caracter != '(' && caracter != '+' && caracter != '-' && caracter != '*' && caracter != '/'){
                    posfixa[j++] = caracter;
                    caracter = desempilhar(p);
                }
                empilhar(p, caracter);
                empilhar(p, inf[i]);
            }

            //Esse if verifica se o caracter analisado não é nenhum dos casos dos ifs anteriores, ele só entra se for diferente de um opretador ou "()"
            if (inf[i] != '(' && inf[i] != ')' && inf[i] != '+' && inf[i] != '-' && inf[i] != '*' && inf[i] != '/' && inf[i] != '^'){
                posfixa[j++] = inf[i];
            }
        }
    }
    posfixa[j] = '\0';
    // Printa o que sobrou na pilha, que neste caso printa NULL pois a pilha não foi librada
    // printf("%p\n", (void*)p->topo);
    liberarPilha(p);
    // Após usar a função liberar pilha, ao printar, recebemos o endereço de memória onde a pilha foi alocada
    // printf("%p\n", (void*)p->topo);
    return posfixa;
}

int main(int argc, char *argv[]){

    // Cria um vetor de caracteres, string, para armazenar os elementos da notação infixa
    char infixa[100];

    // Escaneia a notação infixa digitada pelo usuário
    scanf("%s", infixa);

    // A função que transforma a notação infixa para pósfixa recebe a notação infixa digitada anteriormente pelo usuário
    char *posfixa = infixaParaPosfixa(infixa);

    // Imprime o resultado da transformação da notação
    printf("%s\n", posfixa);

    return 0;
}