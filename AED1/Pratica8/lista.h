
#ifndef LISTA_H
#define LISTA_H

// Estrutura para o nó descritor
struct descritor {
   struct No *inicio; // Ponteiro para o início da lista
   struct No *fim; // Ponteiro para o final da lista
    int quantidade; // Quantidade de elementos na lista
};

 
typedef struct descritor Descritor;
Descritor* criarLista();
void inicializarLista(Descritor *lista);
void adicionarNoInicio(Descritor *lista, int valor);
void adicionarNoFinal(Descritor *lista, int valor);
void removerDoInicio(Descritor *lista);
void removerDoFinal(Descritor *lista);
void removerElemento(Descritor *lista, int elemento);
void exibirLista(Descritor *lista);

#endif