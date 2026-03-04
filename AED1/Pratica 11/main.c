#include <stdio.h> // Não esqueça de incluir o stdio para printf/scanf
#include "roda.h"
#include <time.h>

int main() {
    //Criar a roda
    Roda* minhaRoda = criarRoda();
    int quantidadeDancarinos;

    //Quantidade de dancarinos iniciais
    printf("==============================\n");
    printf("  PROVA DO LIDER SARAJANE    \n");
    printf("=============================\n");
    printf("Vamos abrir a roda!\n");
    printf("-----------------------------\n");
    printf("Digite a quantidade de dancarinos na roda: ");
  
    scanf("%d", &quantidadeDancarinos); // Agora sim, ele só espera o número!
     // Preencher a roda com a quantidade N
    for (int i = 1; i <= quantidadeDancarinos; i++) {
        inserirInicio(minhaRoda, i); 
    }



    printf("Roda criada com %d dancarinos posicionados.\n\n", minhaRoda->quant);

    printf("-----------------------------\n");


     //Inserir o numero K de forma random, aleatoria
    int distanciaK;
   
    srand(time(NULL));  
    distanciaK = rand() % quantidadeDancarinos;  // Sorteia de 1 até N
    printf("Valor da distancia(K) sorteado: %d\n\n", distanciaK);


    // Escolher o lider
    escolherLider( minhaRoda, distanciaK ); // Passar K como distância para os percursos, eliminei k - 1 para evitar auto eliminação

  
    free(minhaRoda);  


    return 0;
}