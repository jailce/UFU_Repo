
#include <stdlib.h>
#include "livros.h"
#include <stdlib.h>

// Criar mochila
// m == mochila geral

Mochila  criarMochila(int capacidade_init) {
Mochila *m = (Mochila*) malloc(sizeof(Mochila));
m -> dados =  (struct Mochila*) malloc (capacidade_init) * sizeof(struct Mochila));
m -> quantiItens = 10;
m -> capacidade = capacidadeInicial_User;
return l;
// cria a função criarMochila com argumento de capacidade inicial (inteiro).
// tudo dentro da função vai referenciar a estrutura Mochila que contem o vetor de itens.
// declara-se um ponteiro *m do tipo Mochila que recebe o malloc do tamanho da struct.
/// já o vetor de dados em m terá o tamanho do tipo Item multiplicado pela capacidade inicial
// todos os atributos de mochila são inicializados aqui: quantItens (0) e capacidade (valor vindo da main
}
