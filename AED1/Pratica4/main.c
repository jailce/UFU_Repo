#include <stdio.h>
#include "livros.h"

int main() {
    Lista *minhaBiblioteca;
    int capacidade_inicial_usuario;


    printf("Digite a capacidade inicial da biblioteca ");
    scanf("%d", &capacidade_inicial_usuario); 


    minhaBiblioteca = iniciarLista(capacidade_inicial_usuario);

    
    
    if (minhaBiblioteca != NULL) {
        printf("Lista foi criada com capacidade para %d livros!\n", capacidade_inicial_usuario);
    }

    return 0;
}