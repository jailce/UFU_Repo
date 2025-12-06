#include <stdlib.h>
#include "livros.h"
#include <stdlib.h>

Lista* iniciarLista( int capacidade_inicial_valor)
{
	//  Lista *l = (Lista*) malloc(sizeof(Lista));
	Lista *l;
	l = (Lista*) malloc(sizeof(Lista));

	if (l !=NULL) {
		l-> dados = (struct Livro*) malloc(capacidade_inicial_valor * sizeof(struct Livro));

		                                   l -> quantidade = 0;
		                                   l -> capacidade = capacidade_inicial_valor;
	}

	            return l;
}