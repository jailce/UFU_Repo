#ifndef REFLORESTAMENTO_H
#define REFLORESTAMENTO_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//lista de lista de projeto de reflorestamento de arvore

typedef struct Arvore {
    int id;
    char especie[50];
    char status[20]; // plantada, não plantada
    struct Arvore* prox;
    struct Arvore* ant;
 

} Arvore;


typedef struct Projeto {
    int id;
    char nome[50];
    float area;//area em alqueire mineiro onde cada unidade equivale a 4.84 hectares ou 48400 metros quadrados.
    Arvore* listaArvores; // ponteiro para a lista de árvores do projeto
    int quantArvores; // contador de árvores no projeto
    struct Projeto* prox;  
    struct Projeto* ant;
} Projeto;

// Estrutura para o descritor da lista de projetos
typedef struct ListaProjetos {
    Projeto* inicio;
    Projeto* fim;
    int quantProjetos;
} ListaProjetos; 


//=====================     FUNÇÕES   ==========================
ListaProjetos* criarLista(); // Criar lista vazia

//=====================     FUNÇÕES PROJETO     ==========================
void cadastrarProjeto(ListaProjetos* listaProj, char* nome, float area);
Projeto* excluirProjeto(ListaProjetos* listaProj, int id);
void listarProjetos(ListaProjetos* listaProj);
Projeto* buscarDetalhesdoProj(ListaProjetos* listaProj, int id);
 

//=====================     FUNÇÕES ARVORES    ==========================
void cadastrarArvore(ListaProjetos* listaProj, char* nomeProjeto, char* especie);
void listarArvores(ListaProjetos* listaProj, Projeto projetoSelecionado);
void excluirArvore(ListaProjetos* listaProj, char* nomeProjeto, int idArvore);
void editarStatusArvore(ListaProjetos* listaProj, char* nomeProjeto, int id_arvore);

//=====================     MENU     ==========================
void menuPrincipal(ListaProjetos* listaProj);
void menuDetalhes(ListaProjetos* listaProj, Projeto* projeto);

// =====================     FUNÇÕES DE ARQUIVO     ==========================
void salvarDados(ListaProjetos* listaProj);
void carregarDados(ListaProjetos* listaProj);



#endif

