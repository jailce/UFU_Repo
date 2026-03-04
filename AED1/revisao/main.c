#include "lista.h"

int main() {
    int numNaves, combustivelPorCiclo;
    
    // Ler entrada
    printf("Número de naves: ");
    scanf("%d", &numNaves);
    
    Descritor *frota = criarLista();
    
    // Ler capacidades e combustível inicial
    for (int i = 0; i < numNaves; i++) {
        int cap, combustivel;
        printf("Nave %d - Capacidade: ", i + 1);
        scanf("%d", &cap);
        printf("Nave %d - Combustível inicial: ", i + 1);
        scanf("%d", &combustivel);
        
        adicionarNovoNave(frota, i + 1, cap, combustivel);
    }
    
    printf("Combustível por ciclo: ");
    scanf("%d", &combustivelPorCiclo);
    
    // Abastecer
    abastecerNaves(frota, combustivelPorCiclo);
    
    // Exibir resultado final
    printf("\nEstado final das naves:\n");
    exibirNaves(frota);
    
    // Liberar memória
    liberarLista(frota);
    
    return 0;
}