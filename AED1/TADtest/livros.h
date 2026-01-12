
#ifndef LIVROS_H
#define LIVROS_H
//struct do livro


struct Item {
//string "semente";
int id;
//int *prox;

};

/*
struct mochila {
int slots;
int *prox;

};*/

typedef struct {
struct Item *dados;
int quantItens;
int capacidade;

} Mochila;


Mochila* criarMochila(int capacidade_init);



typedef item
