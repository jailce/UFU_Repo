# Relatório Técnico: Sistema de Gestão de Reflorestamento

**Aluna:** Jailce Fernanda Leal  
**Código Fonte / Execução:** [Reflorestamento - GDB online Debugger](COLE_SEU_LINK_AQUI)

---

## 1. Introdução

O presente projeto tem como objetivo solucionar o problema de gerenciamento e monitoramento de áreas de reflorestamento, permitindo o controle preciso de diferentes projetos locais (como parques e reservas) e do inventário individual das árvores inseridas em cada um deles.

Para modelar essa hierarquia, a solução foi desenhada utilizando **Listas Encadeadas Aninhadas**. A estrutura principal consiste em uma **Lista Duplamente Encadeada com Descritor** para gerenciar os Projetos. Cada nó de Projeto, por sua vez, contém um ponteiro para a sua própria **Lista Duplamente Encadeada de Árvores**.

A escolha dessa estrutura de dados permite uma alocação dinâmica de memória, garantindo que o sistema escale sem desperdício de recursos, independentemente do volume de mudas cadastradas. O uso do nó Descritor possibilita inserções no final da fila de projetos com complexidade $O(1)$, otimizando o desempenho geral. Para garantir a viabilidade da aplicação no mundo real, o sistema conta com persistência de dados em arquivos de texto plano (`projetos.txt`), permitindo a gravação e o carregamento contínuo do estado do sistema entre diferentes execuções.

## 2. Documentação do Código

O sistema foi modularizado em `main.c`, `reflorestamento.h` e `reflorestamento.c` para separar a lógica de negócio da interface. Abaixo estão detalhadas as principais funções implementadas:

### 2.1. Estruturas Base

* **`ListaProjetos` (Descritor):** Guarda os ponteiros de controle `inicio` e `fim`, além do contador total de projetos (`quantProjetos`).
* **`Projeto`:** Armazena o ID, nome e área (em alqueires). Contém os ponteiros de navegação `prox` e `ant`, além do ponteiro `listaArvores` (que age como o início da sublista de mudas).
* **`Arvore`:** Armazena o ID, a espécie e um inteiro `status` (onde `0` representa "não plantada" e `1` representa "plantada", uma decisão de arquitetura para otimizar o uso de memória em comparação a vetores de caracteres).

### 2.2. Funções Básicas (CRUD)

* **`cadastrarProjeto` e `cadastrarArvore` (Inclusão):** Realizam a alocação dinâmica (`malloc`) de um novo nó. A inserção é feita sempre no final da lista, aproveitando a referência do último nó. Os IDs são gerados automaticamente com base na quantidade atual de itens, garantindo identificadores sequenciais e únicos.
* **`buscarDetalhesdoProj` (Busca):** Utiliza um ponteiro rastreador para percorrer a lista de projetos. Recebe um ID como parâmetro e retorna o endereço de memória do nó correspondente, ou `NULL` se não encontrado.
* **`excluirProjeto` e `excluirArvore` (Remoção):** Realizam o redirecionamento dos ponteiros `prox` e `ant` dos nós vizinhos antes de invocar a liberação de memória (`free()`). Na exclusão de árvores, a função conta com uma rotina de reordenação de IDs para manter a integridade sequencial visual da lista após uma deleção.

### 2.3. Funções Adicionais e Cruzamento de Dados

* **`relatorioArvoresPlantadas`:** Percorre toda a matriz de dados (Projetos e Árvores) contabilizando o status booleano. Imprime um balanço geral de quantas mudas efetivamente foram para o solo e quantas aguardam plantio.
* **`contarEspecieTotal`:** Recebe uma string e cruza essa informação iterando por todas as sublistas. Retorna a contagem exata de espécimes idênticos cadastrados em toda a base de dados do município.
* **`editarStatusArvore`:** Localiza uma árvore específica e altera seu atributo de status de forma direta (`0` ou `1`), com tratamento de interface (UX) para exibir o resultado em formato de texto amigável.

### 2.4. Persistência de Dados

* **`salvarDados` e `carregarDados`:** Manipulam o arquivo `projetos.txt`. O carregamento utiliza `fgets` e `sscanf` para interpretar as linhas de texto utilizando separadores (`|`). O princípio DRY (*Don't Repeat Yourself*) foi aplicado: a função de leitura reaproveita as funções `cadastrarProjeto` e `cadastrarArvore` para reconstruir os nós dinamicamente na memória RAM, abstraindo a complexidade de alocação durante a inicialização.

## 3. Exemplos de Uso

### Exemplo 1: Navegação e Geração de Relatório de Espécies

```text
=================================================================
                      PROJETOS CADASTRADOS   
=================================================================
[ 1 ] Projeto Parque do Sabia                       4.50 Alqueires   5    Arvores 
[ 2 ] Projeto Reserva Ecologica do Cerrado         25.00 Alqueires   12   Arvores 

[S] Selecionar | [C] Cadastrar | [X] Sair
[E] Excluir projeto | [R] Relatorio | [T] Total por Especie
------------------------------------
Instrucoes: Digite o ID do projeto ou uma Letra de comando: T
Digite a especie da arvore(Considere as maiusculas): Ipe_Amarelo
Contando o total de arvores da especie 'Ipe_Amarelo' em todos os projetos...
Total de arvores da especie 'Ipe_Amarelo': 4