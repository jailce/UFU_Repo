#ifndef RODA_H
#define RODA_H

#include <stdlib.h>
#include <stdio.h>


//estrutura para lista duplamente ligada e circular
typedef struct Dancarino {
    int id;
    struct Dancarino* prox;
    struct Dancarino* ant;
} Dancarino;


//estrutura para a lista, onde inicio é o ponteiro para o primeiro nó, fim é o ponteiro para o último nó e tamanho é a quantidade de nós na lista*/
typedef struct Roda {
    Dancarino* inicio;
    Dancarino* fim;
    int quant;
} Roda;




//prototipo das funcoes
void inserirInicio(Roda* roda, int id);
void removerDancarino(Roda* roda, Dancarino* dancarino); // diminuir a rodinha
void deslizandoFrente(Roda* roda, int K);
void deslizandoTras(Roda* roda, int K);
void escolherLider(Roda* roda, int K);
Roda* criarRoda();


#endif