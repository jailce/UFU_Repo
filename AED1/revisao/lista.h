#include <stdio.h>
#include <stdlib.h>
#ifndef LISTA_H
#define LISTA_H


//nó ou celula da lista que carrega um valor(De si) e um endereço(Da proxima celula)
typedef struct No { // define No(celula ou item da lista) como um tipo de dado e ainda por cima diz q é uma struct (objeto)
    int valor; // valor da celula/item da lista que é um objeto
    struct No* prox; // ponteiro do nó
}No; //apesar deter declarado nó no typedef deve-se incluir o apelido(no qual sera chamado) do no/celula, pode ser outra palavra mas normalmente usa a mesma

//struct é como um objeto q é um item com varios atributos


#endif