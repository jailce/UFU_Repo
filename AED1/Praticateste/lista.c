#include <stdlib.h>
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
 
// Recebe ponteiro duplo para alterar o inicio
void inserir_inicio(No **lista, int num){
	No *novo = (No*) malloc(sizeof(No));
	novo -> valor = num;
	novo -> prox = *lista;
	*lista = novo;

}

// Recebe ponteiro duplo para poder remover o primeiro
void remover(No **lista, int num){
	if(*lista == NULL){
		return
	}
	else {

	}
}

void imprimir(No * lista){
	No *atual = *lista;
	while(atual != NULL){
		printf('%d ', atual -> valor);
		atual = atual - > prox
	}
}
// Recebe ponteiro simples pois só vai ler