#include "lista.h"

// Criar lista vazia (primeiro nó aponta para si mesmo)
Descritor* criarLista() {// Alocar memória para o descritor
    Descritor *desc = malloc(sizeof(Descritor)); // Inicializar campos
    desc->inicio = NULL;
    desc->tamanho = 0;
    return desc;
}

// Adicionar nave no final (mantém a circularidade)
void adicionarNovoNave(Descritor *lista, int id, int capacidadeMax, int combustivelInicial) {
    No *novo = malloc(sizeof(No));
    novo->id = id;
    novo->capacidadeMaxima = capacidadeMax;
    novo->combustivelAtual = combustivelInicial;
    
    if (lista->inicio == NULL) {
        // Primeiro nó aponta para si mesmo
        novo->prox = novo;
        lista->inicio = novo;
    } else {
        // Encontrar o último nó e apontá-lo para o novo
        No *atual = lista->inicio;
        while (atual->prox != lista->inicio) {
            atual = atual->prox;
        }
        atual->prox = novo;
        novo->prox = lista->inicio;  // Manter a circularidade
    }
    lista->tamanho++;
}

// Abastecer todas as naves em ciclos
void abastecerNaves(Descritor *lista, int combustivelPorCiclo) {
    if (lista->inicio == NULL) return;
    
    No *atual = lista->inicio;
    int todasCheias = 0;
    
    while (!todasCheias) {
        todasCheias = 1;
        No *temp = atual;
        
        // Verificar cada nave
        for (int i = 0; i < lista->tamanho; i++) {
            if (temp->combustivelAtual < temp->capacidadeMaxima) {
                todasCheias = 0;
                // Abastecer a nave
                temp->combustivelAtual += combustivelPorCiclo;
                if (temp->combustivelAtual > temp->capacidadeMaxima) {
                    temp->combustivelAtual = temp->capacidadeMaxima;
                }
            }
            temp = temp->prox;
        }
    }
}

// Exibir estado de todas as naves
void exibirNaves(Descritor *lista) {
    if (lista->inicio == NULL) return;
    
    No *atual = lista->inicio;
    for (int i = 0; i < lista->tamanho; i++) {
        printf("Nave %d: %d/%d\n", atual->id, atual->combustivelAtual, atual->capacidadeMaxima);
        atual = atual->prox;
    }
}

// Liberar memória da lista
void liberarLista(Descritor *lista) {
    if (lista->inicio == NULL) return;
    
    No *atual = lista->inicio;
    No *temp;
    
    for (int i = 0; i < lista->tamanho; i++) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(lista);
}