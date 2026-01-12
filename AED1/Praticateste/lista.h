
#ifndef LISTA_H
#define LISTA_H

typedef struct No {
    int valor;
    struct No *prox;
} No;

// --- PROTÓTIPOS DAS FUNÇÕES ---
// Aqui a gente só diz "o que" a função faz, não "como".

// Recebe ponteiro duplo para alterar o inicio
void inserir_inicio(No **lista, int num);

// Recebe ponteiro duplo para poder remover o primeiro
void remover(No **lista, int num);


// Recebe ponteiro simples, pois a função apenas lê e não modifica a lista
void imprimir(No *lista);

#endif