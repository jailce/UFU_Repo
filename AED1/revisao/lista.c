#include "lista.h"


// criando funcoes

//disse em h q No é um tipo de dado alem de ser uma struct então a função será um nomedafunção do tipo nomedafunção
 
No* inserirInicio(No* inicioAtual, int novoValor) // No* é um tipo de retorno, é reservado a memoria do tamanho q no precisa afinal essa funcao vai criar um no novo

{
    No* novoNo = (No*)malloc(sizeof(No)); // reserva um espaço compativel com o tamanho do no
        novoNo->valor = novoValor; // o valor do novo nó recebe o valor passado como parametro
       // tenho q dizer pro cara q ficou pra tras o endereço de quem ficou atras dele
     // o inicioAtual recebe o endereço de NovoNo
       inicioAtual->prox = novoNo; // o endereço do inicioAtual recebe o endereço do novo nó, ou seja, o novo nó aponta para o nó que era o início da lista antes da inserção

    return novoNo
};