#include <stdio.h>
#include <string.h>
#include <ctype.h>   
#include "reflorestamento.h"

/*
1. Estrutura de dados:
Lista duplamente ligada de Projetos
Cada projeto possui uma lista duplamente ligada de Árvores
2. Funções básicas por ordem de implementação:
 2.1 Criar lista
2.2 Cadastrar projeto
  Listar projetos
  Buscar projeto por ID
  Excluir projeto
  Cadastrar/adicionar árvore em um projeto
  Remover árvore de um projeto 
  Editar status da árvore 
  Listar árvores de um projeto

3. Menu:
Nível 1 (Menu Principal): Escolhe o projeto.
Nivel 1.2 (Remover projeto): Remove um projeto da lista, junto com suas árvores.  
Nivel 1.3 (Relatório): Exibe um relatório geral de todos os projetos e suas árvores.  
Nível 2 (Sub-menu Detalhes): Recebe o Projeto *p e foca nas árvores.
Nível 3 (Ação Específica): Edita ou remove a árvore dentro daquele contexto.

4. Cruzamento de dados (TO DO):
-Identificar espécies de árvores em mais de um projeto  
-Calcular o total de árvores plantadas 

5. Persistência de dados :
- Salvar os dados em um arquivo (ex: projetos.txt) para que possam ser carregados na próxima execução do programa.
-Implementar funções para ler e escrever os dados dos projetos e árvores no arquivo, garantindo que as informações sejam mantidas entre as execuções do programa.

*/


void salvarDados(ListaProjetos* listaProj) {
    FILE* arquivo = fopen("projetos.txt", "w");
    Projeto* p = listaProj->inicio;
    Arvore* a;
    if (!arquivo) return;

 
    while (p != NULL) {
        // Formato: P|ID|NOME|AREA
        fprintf(arquivo, "P|%d|%s|%.2f\n", p->id, p->nome, p->area);
        
        Arvore* a = p->listaArvores;
        while (a != NULL) {
            // Formato: A|ID|ESPECIE|STATUS
            fprintf(arquivo, "A|%d|%s|%s\n", a->id, a->especie, a->status);
            a = a->prox;
        }
        p = p->prox;
    }
    fclose(arquivo);
}
void carregarDados(ListaProjetos* listaProj) {
    FILE* arquivo = fopen("projetos.txt", "r");
    if (!arquivo) return;

    char linha[256];
    Projeto* projetoAtual = NULL;

    while (fgets(linha, sizeof(linha), arquivo)) 
    
    {
        if (linha[0] == 'P') 
        
        {
            // Linha de projeto
            int id;
            char nome[50];
            float area;
            sscanf(linha, "P|%d|%[^|]|%f", &id, nome, &area);
            cadastrarProjeto(listaProj, nome, area);
            projetoAtual = buscarDetalhesdoProj(listaProj, id); // Buscar o projeto recém-criado para adicionar as árvores
        } 
        
        else if (linha[0] == 'A' && projetoAtual != NULL) {
            // Linha de árvore
            int id;
            char especie[50];
            char status[20];
            sscanf(linha, "A|%d|%[^|]|%[^\r\n]", &id, especie, status);
            cadastrarArvore(listaProj, projetoAtual->nome, especie);
            // Atualizar o status da árvore recém-criada
            Arvore* arvoreAtual = projetoAtual->listaArvores;
            while (arvoreAtual != NULL) {
                if (arvoreAtual->id == id) {
                    strncpy(arvoreAtual->status, status, sizeof(arvoreAtual->status) - 1);
                    arvoreAtual->status[sizeof(arvoreAtual->status) - 1] = '\0'; // Garantir terminação nula
                    break;
                }
                arvoreAtual = arvoreAtual->prox;
            }
        }
    }
    fclose(arquivo);
}

 
//-----------------------------------------  2.1 CRIAR LISTA ---------------------------------------------------------------------
// A função criarLista é responsável por criar e inicializar um novo descritor para a lista de projetos. Ela deixa pronto seus campos (inicio, fim e quantProjetos) e retorna um ponteiro para o descritor criado. 

ListaProjetos * criarLista() {
  ListaProjetos * listaProj = (ListaProjetos * ) malloc(sizeof(ListaProjetos)); //Cria um objeto do tipo Descritor de nome descritor, alocando dinamicamente memória para ele usando malloc. O tamanho da memória alocada é igual ao tamanho da estrutura Descritor.
  if (listaProj != NULL) {
    printf("Lista de projetos criada com sucesso.\n");
    listaProj -> inicio = NULL; // O ponteiro inicio do descritor é inicializado como NULL
    listaProj -> fim = NULL; // O ponteiro fim do descritor também é inicializado como NULL
    listaProj -> quantProjetos = 0; // O contador de projetos do listaProj é inicializado como 0
  }
  printf("Falha ao criar a lista de projetos.\n");
  return listaProj; // Retorna o ponteiro para o descritor criado, sendo possivel acessar a lista de projetos e suas funções através desse descritor.
}

//----------------------------------------- CADASTRAR PROJETO ---------------------------------------------------------------------

void cadastrarProjeto(ListaProjetos * listaProj, char * nome, float area) {
  Projeto * novoProjeto = (Projeto * ) malloc(sizeof(Projeto));
  if (novoProjeto != NULL) {
    strncpy(novoProjeto -> nome, nome, sizeof(novoProjeto -> nome) - 1);
    novoProjeto -> nome[sizeof(novoProjeto -> nome) - 1] = '\0';
    novoProjeto -> id = listaProj -> quantProjetos + 1;
    novoProjeto -> area = area;
    novoProjeto -> listaArvores = NULL;
    novoProjeto -> quantArvores = 0;
    novoProjeto -> prox = NULL;
    novoProjeto -> ant = listaProj -> fim;

    if (listaProj -> fim != NULL) {
      listaProj -> fim -> prox = novoProjeto;
    } else {
      listaProj -> inicio = novoProjeto; // Se a lista estava vazia, o início também aponta para o novo projeto
    }
    listaProj -> fim = novoProjeto; // O fim sempre aponta para o novo projeto
    listaProj -> quantProjetos++;
  }
  //salvarDadosEmArquivo(listaProj); // Salva os dados no arquivo após cadastrar um novo projeto
}


//----------------------------------------------------- LISTAR PROJETO ---------------------------------------------------------------------
//Lista todos os projetos cadastrados e exibe o ID, nome, área e a quantidade de arvores de cada projeto
//O ID é gerado automaticamente a partir do contador de projetos do descritor 'quantProjetos' e é único para cada projeto, garantindo que cada projeto tenha um identificador único.

void listarProjetos(ListaProjetos * listaProj) {
  Projeto * projetoAtual = listaProj -> inicio;

  while (projetoAtual != NULL) {
printf("[%2d ] Projeto %-35s %8.2f Alqueires   %-4d Arvores \n", // O %-30s garante que nomes longos não empurrem a tabela
       projetoAtual->id,          //  2 blocos
       projetoAtual->nome,        //  30 blocos
       projetoAtual->area,        //  8 blocos (2 casas decimais)
       projetoAtual->quantArvores); //  4 blocos
    projetoAtual = projetoAtual -> prox;
  }
}

//-------------------------------------------- BUSCAR PROJETO ---------------------------------------------------------------------
//Busca por ID do projeto para acessar os detalhes do projeto e suas árvores

Projeto * buscarDetalhesdoProj(ListaProjetos * listaProj, int id) {

  Projeto * projetoAtual = listaProj -> inicio; //declara um ponteiro  rastreador chamado projetoAtual que recebe o valor do inicio da lista de projetos pelo descritor
  while (projetoAtual != NULL) {  
    if (projetoAtual -> id == id) {
      return projetoAtual;
    }
      projetoAtual = projetoAtual -> prox; // projetoAtual recebe o próximo projeto da lista, ou seja, o ponteiro prox do projeto atual.
  }
  return NULL; // Retorna NULL se o projeto não for encontrado  
}

//-------------------------------------------- EXCLUIR PROJETO ---------------------------------------------------------------------

Projeto * excluirProjeto(ListaProjetos * listaProj, int id) {
  Projeto * projetoAtual = listaProj -> inicio;

  while (projetoAtual != NULL) {
    if (projetoAtual -> id == id) {
      if (projetoAtual -> ant != NULL) {
        projetoAtual -> ant -> prox = projetoAtual -> prox;
      } else {
        listaProj -> inicio = projetoAtual -> prox; // Se for o primeiro projeto, atualiza o início do listaProj
      }
      if (projetoAtual -> prox != NULL) {
        projetoAtual -> prox -> ant = projetoAtual -> ant;
      } else {
        listaProj -> fim = projetoAtual -> ant; // Se for o último projeto, atualiza o fim do listaProj
      }
      free(projetoAtual); // Libera a memória alocada para o projeto excluído
      listaProj -> quantProjetos--; // Decrementa o contador de projetos do descritor
      printf("Projeto com ID %d excluido com sucesso.\n", id);
      return NULL; // Projeto excluído, retornar NULL
    }
    projetoAtual = projetoAtual -> prox;
  }
  printf("Projeto com ID %d nao encontrado. Exclusao falhou.\n", id);
  return NULL; // Projeto não encontrado, retornar NULL
}
//===============================================================================================================================
//                                                 FUNÇÕES ARVORES
//===============================================================================================================================

//----------------------------------------- CADASTRAR/ADICIONAR ARVORE ---------------------------------------------------------------------
//adicionar arvore a um projeto
// cadastrar arvore colocando o ultimo por ultimo

void cadastrarArvore(ListaProjetos * listaProj, char * nomeProjeto, char * especie) 
{
  Projeto * projetoAtual = listaProj -> inicio;

  while (projetoAtual != NULL) {
    if (strcmp(projetoAtual -> nome, nomeProjeto) == 0) {
      Arvore * novaArvore = (Arvore * ) malloc(sizeof(Arvore));

      if (novaArvore != NULL) {
        novaArvore -> id = projetoAtual -> quantArvores + 1;
        strncpy(novaArvore -> especie, especie, sizeof(novaArvore -> especie) - 1);
        novaArvore -> especie[sizeof(novaArvore -> especie) - 1] = '\0';
        strncpy(novaArvore -> status, "nao plantada", sizeof(novaArvore -> status) - 1);
        novaArvore -> status[sizeof(novaArvore -> status) - 1] = '\0';
        novaArvore -> prox = NULL;
        novaArvore -> ant = NULL;

        if (projetoAtual -> listaArvores == NULL) {
          projetoAtual -> listaArvores = novaArvore; // Se a lista de árvores estava vazia, o início aponta para a nova árvore
        } else {
          Arvore * arvoreAtual = projetoAtual -> listaArvores;
          while (arvoreAtual -> prox != NULL) {
            arvoreAtual = arvoreAtual -> prox; // Move para o próximo nó até chegar ao final da lista
          }
          arvoreAtual -> prox = novaArvore; // O último nó aponta para a nova árvore
          novaArvore -> ant = arvoreAtual; // A nova árvore aponta para o último nó
        }
        projetoAtual -> quantArvores++; // Incrementa o contador de árvores do projeto
      }
      return; // Árvore cadastrada, sair da função
    }
    projetoAtual = projetoAtual -> prox; // Move para o próximo projeto na lista
  }
  printf("Projeto '%s' nao encontrado. Arvore nao cadastrada.\n", nomeProjeto); // Projeto não encontrado, exibe mensagem de erro

}

//-------------------------------------------- EXCLUIR ARVORE --------------------------------------------------

// Quanto excluir a arvore pelo ID deve reordenar os IDs das arvores restantes para manter a sequência correta, ou seja, se a árvore com ID 2 for excluída, as árvores com IDs 3, 4, etc., devem ser renumeradas para 2, 3, etc., respectivamente.
void excluirArvore(ListaProjetos* listaProj, char* nomeProjeto, int idArvore) {
    Projeto* projetoAtual = listaProj->inicio;
    while (projetoAtual != NULL) {
        if (strcmp(projetoAtual->nome, nomeProjeto) == 0) {
            Arvore* arvoreAtual = projetoAtual->listaArvores;
            while (arvoreAtual != NULL) {
                if (arvoreAtual->id == idArvore) {
                    // Remover a árvore da lista
                    if (arvoreAtual->ant != NULL) {
                        arvoreAtual->ant->prox = arvoreAtual->prox;
                    } else {
                        projetoAtual->listaArvores = arvoreAtual->prox; // Se for a primeira árvore, atualiza o início da lista de árvores do projeto
                    }
                    if (arvoreAtual->prox != NULL) {
                        arvoreAtual->prox->ant = arvoreAtual->ant;
                    }
                    free(arvoreAtual); // Libera a memória alocada para a árvore excluída
                    projetoAtual->quantArvores--; // Decrementa o contador de árvores do projeto

                    // Reordenar os IDs das árvores restantes
                    Arvore* arvoreReordenar = projetoAtual->listaArvores;
                    int novoId = 1;
                    while (arvoreReordenar != NULL) {
                        arvoreReordenar->id = novoId++;
                        arvoreReordenar = arvoreReordenar->prox;
                    }

                    printf("Arvore com ID %d excluida com sucesso do projeto '%s'.\n", idArvore, nomeProjeto);
                    return; // Árvore excluída, sair da função
                }
                arvoreAtual = arvoreAtual->prox; // Move para a próxima árvore na lista
            }
            printf("Arvore com ID %d nao encontrada no projeto '%s'. Exclusao falhou.\n", idArvore, nomeProjeto);
            return; // Projeto encontrado, mas árvore não encontrada, sair da função
        }
        projetoAtual = projetoAtual->prox; // Move para o próximo projeto na lista
    }
    printf("Projeto '%s' nao encontrado. Exclusao de arvore falhou.\n", nomeProjeto); // Projeto não encontrado, exibe mensagem de erro
}



 
//----------------------------------------- LISTAR ARVORES ---------------------------------------------------------------------



void listarArvores(ListaProjetos * listaProj, Projeto projetoSelecionado) {
  Projeto * projetoAtual = buscarDetalhesdoProj(listaProj, projetoSelecionado.id);
  if (projetoAtual == NULL) {
    printf("Projeto com ID %d nao encontrado.\n", projetoSelecionado.id);
    return;
  }
  Arvore * arvoreAtual = projetoAtual -> listaArvores; //declara um ponteiro rastreador chamado arvoreAtual que recebe o valor do inicio da lista de árvores do projeto encontrado, ou seja, o ponteiro listaArvores do projetoAtual.
 
  while (arvoreAtual != NULL) {
    printf("[%2d] Especie: %-30s  Status (%-4s)\n", 
      arvoreAtual -> id, 
      arvoreAtual -> especie, 
      arvoreAtual -> status);

    arvoreAtual = arvoreAtual -> prox;
  }
}

//--------------------------------------------- EDITAR STATUS ARVORE ---------------------------------------------------------------------

void editarStatusArvore(ListaProjetos* listaProj, char* nomeProjeto, int id_arvore) {
    Projeto* projetoAtual = listaProj->inicio;
    while (projetoAtual != NULL) {
        if (strcmp(projetoAtual->nome, nomeProjeto) == 0) {
            Arvore* arvoreAtual = projetoAtual->listaArvores;
            int contador = 1; // Contador para identificar a árvore pelo ID
            while (arvoreAtual != NULL) {
                if (contador == id_arvore) {
                    printf("Digite o novo status para a arvore '%s' (plantada/nao plantada): ", arvoreAtual->especie);
                    char novoStatus[20];
                    scanf("%s", novoStatus);
                    strncpy(arvoreAtual->status, novoStatus, sizeof(arvoreAtual->status) - 1);
                    printf("Status da arvore '%s' atualizado para '%s'.\n", arvoreAtual->especie, arvoreAtual->status);
                    return; // Status atualizado, sair da função
                }
                arvoreAtual = arvoreAtual->prox;
                contador++;
            }
            printf("Arvore com ID %d nao encontrada no projeto '%s'.\n", id_arvore, nomeProjeto);
            return; // Projeto encontrado, mas árvore não encontrada, sair da função
        }
        projetoAtual = projetoAtual->prox;
    }
    printf("Projeto '%s' nao encontrado.\n", nomeProjeto);
}



//================================================     MENU   ========================================

// Nível 1 (Menu Principal): Escolhe o projeto.
void menuPrincipal(ListaProjetos * listaProj) {
  char input[50];
  int sair = 1;
  carregarDados(listaProj); 
  do {
    printf("\n=================================================================\n");
    printf("                      PROJETOS CADASTRADOS Arquivo   \n");
    printf("===================================================================\n");

    
  // Carrega os dados do arquivo projetos.txt para a lista de projetos ao iniciar o menu principal, garantindo que as informações sejam mantidas entre as execuções do programa
   listarProjetos(listaProj);


    if(listaProj->quantProjetos == 0) {
      printf("Nenhum projeto cadastrado. Por favor, cadastre um projeto para acessar as opCOes.\n");
    }

    printf("\n[S] Selecionar | [C] Cadastrar | [X] Sair\n");
    printf("[E] Excluir projeto | [R] Relatorio\n");
    printf("------------------------------------\n");
    printf("Instrucoes: Digite o ID do projeto ou uma Letra de comando: ");

    // já é listado os projetos com opção de entrar no detalhes dele digitando numero do id

    scanf("%s", input);

    char comando = toupper(input[0]); // Converte o primeiro caractere da entrada para maiúscula para facilitar a comparação

      switch (comando) 
      {

      case 'S':
      {
        int idProjeto;
        printf("Digite o ID do projeto a ser selecionado: ");
        scanf("%d", &idProjeto);
             Projeto * projetoEncontrado = NULL;
      printf("Acessando projeto por ID %d \n", idProjeto);

      projetoEncontrado = buscarDetalhesdoProj(listaProj, idProjeto); // Função para buscar detalhes do projeto por ID retorna o objeto do tipo Projeto* encontrado ou NULL se não encontrado

      if (projetoEncontrado != NULL) {
        menuDetalhes(listaProj, projetoEncontrado); // paramentros são o listaProj, o projeto encontrado do tipo Projeto* e o id do projeto encontrado do tipo int)
      } else {
        printf("Projeto com ID %d nao encontrado.\n", idProjeto);
      }

      }
        // Selecionar um projeto para ver detalhes
        break;

      case 'C': {
        //Cadastrar um novo projeto
        char nomeProjeto[50];
        float areaProjeto;
        printf("Digite o nome do projeto: ");
        scanf("%s", nomeProjeto);
        printf("Digite a area do projeto (em alqueires): ");
        scanf("%f", & areaProjeto);
        cadastrarProjeto(listaProj, nomeProjeto, areaProjeto);
      }
      break;

      case 'X':
        exit(0); // Sair do programa
        break;

      case 'E':
      // Excluir projeto
        {
          int idProjeto;
          printf("Digite o ID do projeto a ser excluído: ");
          scanf("%d", &idProjeto);
          excluirProjeto(listaProj, idProjeto);
        }
        break;

      case 'R':
        // Exibe o relatório
        break;
      default:
        printf("Opçao invalida. Tente novamente.\n");
        break;

      }
    salvarDados(listaProj); // Salva os dados no arquivo após cada ação no menu principal, garantindo que as informações sejam mantidas entre as execuções do programa
    } 
    while (sair == 1); // O loop continua até que o usuário escolha sair do programa
}
 
//Nível 2 (Sub-menu Detalhes): Recebe o Projeto *p e foca nas árvores.

void menuDetalhes(ListaProjetos * listaProj, Projeto * projetoSelecionado) 
{
    int sair = 1;
    char input[50];

    do 
    {

      printf("\n===================================================================================================\n");
      printf("ID do projeto: %d\n", projetoSelecionado -> id);
      printf("Nome do projeto: %s\n", projetoSelecionado -> nome);
      printf("Area do projeto: %.2f alqueires\n", projetoSelecionado -> area);
      printf("Quantidade de arvores: %d\n", projetoSelecionado -> quantArvores);
      printf("===================================================================================================\n");



      listarArvores(listaProj, *projetoSelecionado); // funcao listarArvores com os parametros: 

 
   

      printf("\n[C] Cadastrar Arvore | [M] Voltar ao menu principal | [X] Sair do programa\n");
      printf("\n[E] Excluir Arvore | [A] Alterar Status Arvore \n");
      printf("------------------------------------\n");
      printf("Instrucoes: Digite o ID da arvore ou uma Letra de comando: ");
     
      scanf("%s", input);

       
        char comando = toupper(input[0]);

        switch (comando) {

         case 'C':
          {
            char especie[50];
            printf("Digite a especie da arvore: ");
            scanf("%s", especie);
            cadastrarArvore(listaProj, projetoSelecionado -> nome, especie);
          }
          break;

          case 'M':
          sair = 0; // Voltar ao menu principal
          break;

           case 'X':
           exit(0); // Sair do programa
           break;

          case 'E': 
          {

          int idArvore;
          printf("Digite o ID da arvore a ser excluida: ");
          scanf("%d", &idArvore);
          excluirArvore(listaProj, projetoSelecionado->nome, idArvore);
          

          }

          break;

          case 'A': 
          {
           int idArvore;
          printf("Digite o ID da árvore a ser alterada: ");
          scanf("%d", &idArvore);
          editarStatusArvore(listaProj, projetoSelecionado->nome, idArvore);

          }
  
          break;

          default:
          printf("Opçao invalida. Tente novamente.\n");


        }
      
   salvarDados(listaProj); // Salva os dados no arquivo após cada ação no menu de detalhes do projeto

    }      while(sair == 1);//encerrar o programa
    
}


    //Nível 3 (Ação Específica): Edita ou remove a árvore dentro daquele contexto.

  