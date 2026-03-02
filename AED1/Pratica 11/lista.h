#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdio.h>

// Definição do nó da lista circular
typedef struct no {
    int id;   /                // Identificador da nave
    int capacidadeMaxima;     // Capacidade máxima de combustível
    int combustivelAtual;     // Combustível atual
    struct no* prox;          // Ponteiro para a próxima nave
} No;

// Descritor da lista circular
typedef struct descritor {
    No* inicio;  // Ponteiro para o primeiro nó (define toda a lista circular)
    int tamanho; // Quantidade de naves
} Descritor;

// Declarações de funções
Descritor* criarLista(); // Criar lista vazia
void adicionarNovoNave(Descritor *lista, int id, int capacidadeMax, int combustivelInicial); // Adicionar nova nave
void abastecerNaves(Descritor *lista, int combustivelPorCiclo);
void exibirNaves(Descritor *lista);
void liberarLista(Descritor *lista);

#endif