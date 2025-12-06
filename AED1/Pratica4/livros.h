
#ifndef LIVROS_H
#define LIVROS_H
//struct do livro
struct Livro {
    char titulo[30], autor[30];
    int ano;
    float preco; 
};

//escopo da lista
typedef struct {
    struct Livro *dados;  
    int quantidade;       
    int capacidade;      //  capacidade inicial definida pelo usuário
} Lista;

//prototipocs de funções
Lista* iniciarLista( int capacidade_inicial_valor);

#endif