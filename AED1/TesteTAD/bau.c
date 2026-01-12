#include <stdlib.h>
#include "bau.h"
#include <stdio.h>

void inicializar(Lista *l) {
    l->tamanho = 0; // Dentro da função, como é ponteiro, continua usando seta ->
}

int inserir(Lista *l, int valor) {
    if (l->tamanho < MAX) {
        l->dados[l->tamanho] = valor;
        l->tamanho++;
        return 1;
    }
    return 0;
}