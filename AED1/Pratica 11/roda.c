#include "roda.h"


//criar lista vazia
Roda * criarRoda() {
    Roda* roda = (Roda*)malloc(sizeof(Roda));
    roda->inicio = NULL;
    roda->fim = NULL;
    roda->quant = 0;
    return roda ;
}

//inserir nó no início


void inserirInicio(Roda* roda, int id) {
    Dancarino* novoDancarino = (Dancarino*)malloc(sizeof(Dancarino));
    novoDancarino->id = id;
    if (roda->quant == 0) {
        novoDancarino->prox = novoDancarino;
        novoDancarino->ant = novoDancarino;
        roda->inicio = novoDancarino;
        roda->fim = novoDancarino;
        printf("Primeiro dancarino %d adicionado.\n", id);
    } else {
        novoDancarino->prox = roda->inicio;
        novoDancarino->ant = roda->fim;
        roda->fim->prox = novoDancarino;
        roda->inicio->ant = novoDancarino;
        roda->inicio = novoDancarino;
        printf("Dancarino %d adicionado\n", id);
    }
    roda->quant++;


}


//remover um nó(dancarino) a partir de um ponteiro
void removerDancarino(Roda* roda, Dancarino* dancarino) {

//lista vazia é caso especial, mas nesse caso não tem como chegar aqui, pois a função de escolha do líder só é chamada quando tem mais de 1 dancarino  
    if (roda->quant == 1) {
        printf("Dancarino [%d] eliminado. Nenhum dancarino restante.\n", dancarino->id);
        free(dancarino);
        roda->inicio = NULL;
        roda->fim = NULL;

    } else {
        Dancarino* ant = dancarino->ant;
        Dancarino* prox = dancarino->prox;
        ant->prox = prox;
        prox->ant = ant;
        if (dancarino == roda->inicio) {
            roda->inicio = prox;
        }
        if (dancarino == roda->fim) {
            roda->fim = ant;
        }
        printf("Dancarino [%d] esta fora!\n\n", dancarino->id);
        free(dancarino);
    }
    roda->quant--;
}


void deslizandoFrente(Roda* roda, int distancia)
{
    for (int i = 0; i < distancia; i++) {
        roda->inicio = roda->inicio->prox;
    }
}
void deslizandoTras(Roda* roda, int distancia)
{
    for (int i = 0; i < distancia; i++) {
        roda->inicio = roda->inicio->ant;
    }
}


void escolherLider(Roda* roda, int distancia) {
    
  //O dançarino 1 está salvo no ponteiro 'fim' então começamos a partir dele
    roda->inicio = roda->fim; 

    while (roda->quant > 1) {
        
    // Eliminar o dancarino da direita
        Dancarino* comCaixa = roda->inicio; 

        
        deslizandoTras(roda, distancia);
        Dancarino* alvoDireita = roda->inicio; 

        printf("Dancarino [%d] esta com a caixa:\nElimina o dancarino [%d] a sua direita >>>>.\n", comCaixa->id, alvoDireita->id);
        
      
        roda->inicio = alvoDireita->ant; 
        removerDancarino(roda, alvoDireita);

       
        if (roda->quant <= 1) {
            break;
        }

        // Eliminar o dancarino da esquerda
        comCaixa = roda->inicio; 

 
        deslizandoFrente(roda, distancia);
        Dancarino* alvoEsquerda = roda->inicio;

        printf("Dancarino [%d] esta com a caixa:\nElimina dancarino [%d] a sua <<<<< esquerda.\n", comCaixa->id, alvoEsquerda->id);
        
     
        roda->inicio = alvoEsquerda->prox;
        removerDancarino(roda, alvoEsquerda);
    }

    if (roda->inicio != NULL) {
        printf("\nO [%d] e o novo lider da semana!\n", roda->inicio->id);
    }
}