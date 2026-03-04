#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "reflorestamento.h"

/*
1. Estrutura de dados:
Lista duplamente ligada de Projetos
Cada projeto possui uma lista duplamente ligada de Crvores
2. FunC'C5es bC!sicas por ordem de implementaC'C#o:
 2.1 Criar lista
2.2 Cadastrar projeto
  Listar projetos
  Buscar projeto por ID
  Excluir projeto
  Cadastrar/adicionar C!rvore em um projeto
  Remover C!rvore de um projeto
  Editar status da C!rvore
  Listar C!rvores de um projeto

3. Menu:
NC-vel 1 (Menu Principal): Escolhe o projeto.
Nivel 1.2 (Remover projeto): Remove um projeto da lista, junto com suas C!rvores.
Nivel 1.3 (RelatC3rio): Exibe um relatC3rio geral de todos os projetos e suas C!rvores.
NC-vel 2 (Sub-menu Detalhes): Recebe o Projeto *p e foca nas C!rvores.
NC-vel 3 (AC'C#o EspecC-fica): Edita ou remove a C!rvore dentro daquele contexto.

4. Cruzamento de dados:
-Identificar espC)cies de C!rvores em mais de um projeto
-Calcular o total de C!rvores plantadas

5. PersistC*ncia de dados :
- Salvar os dados em um arquivo (ex: projetos.txt) para que possam ser carregados na prC3xima execuC'C#o do programa.
-Implementar funC'C5es para ler e escrever os dados dos projetos e C!rvores no arquivo, garantindo que as informaC'C5es sejam mantidas entre as execuC'C5es do programa.

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
			fprintf(arquivo, "A|%d|%s|%s\n", a->id, a->especie, (a->status == 1) ? "plantada" : "nao plantada");
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
			projetoAtual = buscarDetalhesdoProj(listaProj, id); // Buscar o projeto recC)m-criado para adicionar as C!rvores
		}

		else if (linha[0] == 'A' && projetoAtual != NULL) {
			// Linha de C!rvore
			int id;
			char especie[50];
			char status[20];
			sscanf(linha, "A|%d|%[^|]|%[^\r\n]", &id, especie, status);
			cadastrarArvore(listaProj, projetoAtual->nome, especie);
			// Atualizar o status da C!rvore recC)m-criada
			Arvore* arvoreAtual = projetoAtual->listaArvores;
			while (arvoreAtual != NULL) {
				if (arvoreAtual->id == id) {
					arvoreAtual->status = (strcmp(status, "plantada") == 0) ? 1 : 0; // Converter status para inteiro (1 para plantada, 0 para nao plantada)
					break;
				}
				arvoreAtual = arvoreAtual->prox;
			}
		}
	}
	fclose(arquivo);
}


//-----------------------------------------  2.1 CRIAR LISTA ---------------------------------------------------------------------
// A funC'C#o criarLista C) responsC!vel por criar e inicializar um novo descritor para a lista de projetos. Ela deixa pronto seus campos (inicio, fim e quantProjetos) e retorna um ponteiro para o descritor criado.

ListaProjetos * criarLista() {
	ListaProjetos * listaProj = (ListaProjetos * ) malloc(sizeof(ListaProjetos)); //Cria um objeto do tipo Descritor de nome descritor, alocando dinamicamente memC3ria para ele usando malloc. O tamanho da memC3ria alocada C) igual ao tamanho da estrutura Descritor.
	if (listaProj != NULL) {
		printf("Lista de projetos criada com sucesso.\n");
		listaProj -> inicio = NULL; // O ponteiro inicio do descritor C) inicializado como NULL
		listaProj -> fim = NULL; // O ponteiro fim do descritor tambC)m C) inicializado como NULL
		listaProj -> quantProjetos = 0; // O contador de projetos do listaProj C) inicializado como 0
	}

	return listaProj; // Retorna o ponteiro para o descritor criado, sendo possivel acessar a lista de projetos e suas funC'C5es atravC)s desse descritor.
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
			listaProj -> inicio = novoProjeto; // Se a lista estava vazia, o inC-cio tambC)m aponta para o novo projeto
		}
		listaProj -> fim = novoProjeto; // O fim sempre aponta para o novo projeto
		listaProj -> quantProjetos++;
	}
	//salvarDadosEmArquivo(listaProj); // Salva os dados no arquivo apC3s cadastrar um novo projeto
}


//----------------------------------------------------- LISTAR PROJETO ---------------------------------------------------------------------
//Lista todos os projetos cadastrados e exibe o ID, nome, C!rea e a quantidade de arvores de cada projeto
//O ID C) gerado automaticamente a partir do contador de projetos do descritor 'quantProjetos' e C) C:nico para cada projeto, garantindo que cada projeto tenha um identificador C:nico.

void listarProjetos(ListaProjetos * listaProj) {
	Projeto * projetoAtual = listaProj -> inicio;

	while (projetoAtual != NULL) {
		printf("[%2d ] Projeto %-35s %8.2f Alqueires   %-4d Arvores \n", // O %-30s garante que nomes longos nC#o empurrem a tabela
		       projetoAtual->id,          //  2 blocos
		       projetoAtual->nome,        //  30 blocos
		       projetoAtual->area,        //  8 blocos (2 casas decimais)
		       projetoAtual->quantArvores); //  4 blocos
		projetoAtual = projetoAtual -> prox;
	}
}

//-------------------------------------------- BUSCAR PROJETO ---------------------------------------------------------------------
//Busca por ID do projeto para acessar os detalhes do projeto e suas C!rvores

Projeto * buscarDetalhesdoProj(ListaProjetos * listaProj, int id) {

	Projeto * projetoAtual = listaProj -> inicio; //declara um ponteiro  rastreador chamado projetoAtual que recebe o valor do inicio da lista de projetos pelo descritor
	while (projetoAtual != NULL) {
		if (projetoAtual -> id == id) {
			return projetoAtual;
		}
		projetoAtual = projetoAtual -> prox; // projetoAtual recebe o prC3ximo projeto da lista, ou seja, o ponteiro prox do projeto atual.
	}
	return NULL; // Retorna NULL se o projeto nC#o for encontrado
}

//-------------------------------------------- EXCLUIR PROJETO ---------------------------------------------------------------------

Projeto * excluirProjeto(ListaProjetos * listaProj, int id) {
	Projeto * projetoAtual = listaProj -> inicio;

	while (projetoAtual != NULL) {
		if (projetoAtual -> id == id) {
			if (projetoAtual -> ant != NULL) {
				projetoAtual -> ant -> prox = projetoAtual -> prox;
			} else {
				listaProj -> inicio = projetoAtual -> prox; // Se for o primeiro projeto, atualiza o inC-cio do listaProj
			}
			if (projetoAtual -> prox != NULL) {
				projetoAtual -> prox -> ant = projetoAtual -> ant;
			} else {
				listaProj -> fim = projetoAtual -> ant; // Se for o C:ltimo projeto, atualiza o fim do listaProj
			}
			free(projetoAtual); // Libera a memC3ria alocada para o projeto excluC-do
			listaProj -> quantProjetos--; // Decrementa o contador de projetos do descritor
			printf("Projeto com ID %d excluido com sucesso.\n", id);
			return NULL; // Projeto excluC-do, retornar NULL
		}
		projetoAtual = projetoAtual -> prox;
	}
	printf("Projeto com ID %d nao encontrado. Exclusao falhou.\n", id);
	return NULL; // Projeto nC#o encontrado, retornar NULL
}
//===============================================================================================================================
//                                                 FUNCCES ARVORES
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
				novaArvore -> status = 0; // 0 para "nao plantada"
				novaArvore -> prox = NULL;
				novaArvore -> ant = NULL;

				if (projetoAtual -> listaArvores == NULL) {
					projetoAtual -> listaArvores = novaArvore; // Se a lista de C!rvores estava vazia, o inC-cio aponta para a nova C!rvore
				} else {
					Arvore * arvoreAtual = projetoAtual -> listaArvores;
					while (arvoreAtual -> prox != NULL) {
						arvoreAtual = arvoreAtual -> prox; // Move para o prC3ximo nC3 atC) chegar ao final da lista
					}
					arvoreAtual -> prox = novaArvore; // O C:ltimo nC3 aponta para a nova C!rvore
					novaArvore -> ant = arvoreAtual; // A nova C!rvore aponta para o C:ltimo nC3
				}
				projetoAtual -> quantArvores++; // Incrementa o contador de C!rvores do projeto
			}
			return; // Crvore cadastrada, sair da funC'C#o
		}
		projetoAtual = projetoAtual -> prox; // Move para o prC3ximo projeto na lista
	}
	printf("Projeto '%s' nao encontrado. Arvore nao cadastrada.\n", nomeProjeto); // Projeto nC#o encontrado, exibe mensagem de erro

}

//-------------------------------------------- EXCLUIR ARVORE --------------------------------------------------

// Quanto excluir a arvore pelo ID deve reordenar os IDs das arvores restantes para manter a sequC*ncia correta, ou seja, se a C!rvore com ID 2 for excluC-da, as C!rvores com IDs 3, 4, etc., devem ser renumeradas para 2, 3, etc., respectivamente.
void excluirArvore(ListaProjetos* listaProj, char* nomeProjeto, int idArvore) {
	Projeto* projetoAtual = listaProj->inicio;
	while (projetoAtual != NULL) {
		if (strcmp(projetoAtual->nome, nomeProjeto) == 0) {
			Arvore* arvoreAtual = projetoAtual->listaArvores;
			while (arvoreAtual != NULL) {
				if (arvoreAtual->id == idArvore) {
					// Remover a C!rvore da lista
					if (arvoreAtual->ant != NULL) {
						arvoreAtual->ant->prox = arvoreAtual->prox;
					} else {
						projetoAtual->listaArvores = arvoreAtual->prox; // Se for a primeira C!rvore, atualiza o inC-cio da lista de C!rvores do projeto
					}
					if (arvoreAtual->prox != NULL) {
						arvoreAtual->prox->ant = arvoreAtual->ant;
					}
					free(arvoreAtual); // Libera a memC3ria alocada para a C!rvore excluC-da
					projetoAtual->quantArvores--; // Decrementa o contador de C!rvores do projeto

					// Reordenar os IDs das C!rvores restantes
					Arvore* arvoreReordenar = projetoAtual->listaArvores;
					int novoId = 1;
					while (arvoreReordenar != NULL) {
						arvoreReordenar->id = novoId++;
						arvoreReordenar = arvoreReordenar->prox;
					}

					printf("Arvore com ID %d excluida com sucesso do projeto '%s'.\n", idArvore, nomeProjeto);
					return; // Crvore excluC-da, sair da funC'C#o
				}
				arvoreAtual = arvoreAtual->prox; // Move para a prC3xima C!rvore na lista
			}
			printf("Arvore com ID %d nao encontrada no projeto '%s'. Exclusao falhou.\n", idArvore, nomeProjeto);
			return; // Projeto encontrado, mas C!rvore nC#o encontrada, sair da funC'C#o
		}
		projetoAtual = projetoAtual->prox; // Move para o prC3ximo projeto na lista
	}
	printf("Projeto '%s' nao encontrado. Exclusao de arvore falhou.\n", nomeProjeto); // Projeto nC#o encontrado, exibe mensagem de erro
}




//----------------------------------------- LISTAR ARVORES ---------------------------------------------------------------------



void listarArvores(ListaProjetos * listaProj, Projeto projetoSelecionado) {
	Projeto * projetoAtual = buscarDetalhesdoProj(listaProj, projetoSelecionado.id);
	if (projetoAtual == NULL) {
		printf("Projeto com ID %d nao encontrado.\n", projetoSelecionado.id);
		return;
	}
	Arvore * arvoreAtual = projetoAtual -> listaArvores; //declara um ponteiro rastreador chamado arvoreAtual que recebe o valor do inicio da lista de C!rvores do projeto encontrado, ou seja, o ponteiro listaArvores do projetoAtual.

	while (arvoreAtual != NULL) {
printf("[%2d] Especie: %-30s  Status: %s\n", 
      arvoreAtual->id, 
      arvoreAtual->especie,
      (arvoreAtual->status == 1) ? "plantada" : "nao plantada");
		arvoreAtual = arvoreAtual -> prox;
	}
}

//--------------------------------------------- EDITAR STATUS ARVORE ---------------------------------------------------------------------

void editarStatusArvore(ListaProjetos* listaProj, char* nomeProjeto, int id_arvore) {
	Projeto* projetoAtual = listaProj->inicio;
	while (projetoAtual != NULL) {
		if (strcmp(projetoAtual->nome, nomeProjeto) == 0) {
			Arvore* arvoreAtual = projetoAtual->listaArvores;
			int contador = 1; // Contador para identificar a C!rvore pelo ID
			while (arvoreAtual != NULL) {
				if (contador == id_arvore) {
					printf("Digite o novo status para a arvore '%s' (1 para plantada, 0 para nao plantada): ", arvoreAtual->especie);
					
					scanf("%d", &arvoreAtual->status); // Lê o novo status diretamente no campo da C!rvore
					printf("Status da arvore '%s' atualizado para '%s'.\n", arvoreAtual->especie, (arvoreAtual->status == 1) ? "plantada" : "nao plantada");
					return; // Status atualizado, sair da funC'C#o
				}
				arvoreAtual = arvoreAtual->prox;
				contador++;
			}
			printf("Arvore com ID %d nao encontrada no projeto '%s'.\n", id_arvore, nomeProjeto);
			return; // Projeto encontrado, mas C!rvore nC#o encontrada, sair da funC'C#o
		}
		projetoAtual = projetoAtual->prox;
	}
	printf("Projeto '%s' nao encontrado.\n", nomeProjeto);
}



//================================================     MENU   ========================================

// NC-vel 1 (Menu Principal): Escolhe o projeto.
void menuPrincipal(ListaProjetos * listaProj) {
	char input[50];
	int sair = 1;
	carregarDados(listaProj);
	do {
		printf("\n=================================================================\n");
		printf("                      PROJETOS CADASTRADOS   \n");
		printf("===================================================================\n");


		// Carrega os dados do arquivo projetos.txt para a lista de projetos ao iniciar o menu principal, garantindo que as informaC'C5es sejam mantidas entre as execuC'C5es do programa
		listarProjetos(listaProj);


		if(listaProj->quantProjetos == 0) {
			printf("Nenhum projeto cadastrado. Por favor, cadastre um projeto para acessar as opCOes.\n");
		}

		printf("\n[S] Selecionar | [C] Cadastrar | [X] Sair\n");
		printf("[E] Excluir projeto | [R] Relatorio | [T] Total por Especie\n");
		printf("------------------------------------\n");
		printf("Instrucoes: Digite o ID do projeto ou uma Letra de comando: ");

		// jC! C) listado os projetos com opC'C#o de entrar no detalhes dele digitando numero do id

		scanf("%s", input);

		char comando = toupper(input[0]); // Converte o primeiro caractere da entrada para maiC:scula para facilitar a comparaC'C#o

		switch (comando)
		{

		case 'S':
		{
			int idProjeto;
			printf("Digite o ID do projeto a ser selecionado: ");
			scanf("%d", &idProjeto);
			Projeto * projetoEncontrado = NULL;
			printf("Acessando projeto por ID %d \n", idProjeto);

			projetoEncontrado = buscarDetalhesdoProj(listaProj, idProjeto); // FunC'C#o para buscar detalhes do projeto por ID retorna o objeto do tipo Projeto* encontrado ou NULL se nC#o encontrado

			if (projetoEncontrado != NULL) {
				menuDetalhes(listaProj, projetoEncontrado); // paramentros sC#o o listaProj, o projeto encontrado do tipo Projeto* e o id do projeto encontrado do tipo int)
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
			printf("Digite o ID do projeto a ser excluC-do: ");
			scanf("%d", &idProjeto);
			excluirProjeto(listaProj, idProjeto);
		}
		break;

		case 'R':
		{
			printf("Gerando relatorio geral de todos os projetos e suas arvores...\n");

      relatorioArvoresPlantadas(listaProj);

		}

		break;
    //buscar e trazer o total de uma especie de arvore em todos os projetos
    case 'T':
    {
      char especieBuscada[50];
      printf("Digite a especie da arvore(Considere as maiusculas): ");
      scanf("%s", especieBuscada);
      printf("Contando o total de arvores da especie '%s' em todos os projetos...\n", especieBuscada);
      int totalEspecie = contarEspecieTotal(listaProj, especieBuscada);
      printf("Total de arvores da especie '%s': %d\n", especieBuscada, totalEspecie);

    }

		default:
			printf("Opcao invalida. Tente novamente.\n");
			break;

		}
		salvarDados(listaProj); // Salva os dados no arquivo apC3s cada aC'C#o no menu principal, garantindo que as informaC'C5es sejam mantidas entre as execuC'C5es do programa
	}
	while (sair == 1); // O loop continua atC) que o usuC!rio escolha sair do programa
}

//NC-vel 2 (Sub-menu Detalhes): Recebe o Projeto *p e foca nas C!rvores.

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
		printf("====================================================================================================\n");



		listarArvores(listaProj, *projetoSelecionado); // funcao listarArvores com os parametros:




		printf("\n[C] Cadastrar Arvore | [M] Voltar ao menu principal | [X] Sair do programa\n");
		printf("\n[E] Excluir Arvore | [A] Alterar Status Arvore \n");
		printf("------------------------------------\n");
		printf("Instrucoes: Um Letra de comando: ");

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
			printf("Digite o ID da C!rvore a ser alterada: ");
			scanf("%d", &idArvore);
			editarStatusArvore(listaProj, projetoSelecionado->nome, idArvore);

		}

		break;

		default:
			printf("Opcao invalida. Tente novamente.\n");


		}

		salvarDados(listaProj); // Salva os dados no arquivo apC3s cada aC'C#o no menu de detalhes do projeto

	}      while(sair == 1);//encerrar o programa

}


// Relatorio geral de todos os projetos e suas arvores  


void relatorioArvoresPlantadas(ListaProjetos* listaProj) {
    int totalPlantadas = 0;
    int totalNaoPlantadas = 0;
    

    Projeto* projetoAtual = listaProj->inicio; 

    while(projetoAtual != NULL) {
        
  
        Arvore* arvoreAtual = projetoAtual->listaArvores; 
        
        while(arvoreAtual != NULL) {
 
         if (arvoreAtual->status == 1) {
                totalPlantadas++;
            }
            else if (arvoreAtual->status == 0) {
                totalNaoPlantadas++;
            }
            arvoreAtual = arvoreAtual->prox;
            
      
        
        }
        
 
        projetoAtual = projetoAtual->prox; 
    }

    printf("\n=== RESUMO DO REFLORESTAMENTO ===\n");
    printf("Arvores efetivamente plantadas: %d\n", totalPlantadas);
    printf("Mudas aguardando plantio: %d\n", totalNaoPlantadas);
    printf("Total Geral: %d\n", totalPlantadas + totalNaoPlantadas);
    printf("=================================\n");
}

// Retorna um int (o número total de árvores daquela espécie)
int contarEspecieTotal(ListaProjetos* listaProj, char* especieBusca) {
    int contador = 0; // O nosso bloquinho de notas começa zerado
    
 
    Projeto* projetoAtual = listaProj->inicio; 

    while (projetoAtual != NULL) {
        
  
        Arvore* arvoreAtual = projetoAtual->listaArvores; 
        
        while (arvoreAtual != NULL) {
      
            if (strcmp(arvoreAtual->especie, especieBusca) == 0) {
                contador++;  
            }
        
            arvoreAtual = arvoreAtual->prox; 
        }
    
        projetoAtual = projetoAtual->prox; 
    }
    
    return contador;  
}

