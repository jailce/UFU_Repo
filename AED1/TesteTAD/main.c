#include <stdio.h>
#include "bau.h"

int main() {
    // --- MUDANÇA PRINCIPAL AQUI ---
    
    // 1. Declaração direta (sem ponteiro, sem malloc)
    Lista minhaLista; 
    
    // 2. Passagem por referência (manda o endereço & para a função)
    inicializar(&minhaLista);

    // 3. Inserção
    inserir(&minhaLista, 10);
    inserir(&minhaLista, 20);

    // 4. Acesso direto na main (usa PONTO)
    printf("Tamanho atual: %d\n", minhaLista.tamanho); 
    printf("Item 1: %d\n", minhaLista.dados[0]);

    return 0;
    // Não precisa de free()! O sistema limpa sozinho ao fechar a chave }.
}