#include <stdlib.h>
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
 
// Estrutura para representar um nó da lista encadeada
typedef struct No {
    int valor; // Valor armazenado no nó
    struct No *prox; // Ponteiro para o próximo nó
} No;

Descritor* criarLista(){
	Descritor *novaLista = (Descritor*) malloc (sizeof(Descritor));
	return novaLista;
};

//Iniciar a lista encadeada.
void inicializarLista(Descritor *novaLista){
 
	
	if (novaLista !=NULL) {
		novaLista->inicio = NULL;
	    novaLista->fim = NULL;
	    novaLista->quantidade = 0;
	    printf("Lista iniciada");
	}
	else {
		printf("Erro ao iniciar a lista");

}

};


//Adicionar um elemento no início da lista.


//Adicionar um elemento no final da lista.
//Remover o elemento do início da lista.
//Remover o elemento do final da lista.
//Remover um determinado elemento em qualquer posição da lista.
//Exibir todos os elementos da lista e a quantidade de elementos.
