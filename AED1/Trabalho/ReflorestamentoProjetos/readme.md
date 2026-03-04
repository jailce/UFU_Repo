# 📊 Nova Estimativa: ~75-80% concluído

## ✅ Implementado (70%)
- ✅ Todas as 5 funções básicas obrigatórias (100%)
    - Cadastrar / Listar / Buscar / Excluir projeto / Listar arvores
- ✅3 funções extras além do solicitado (excluir árvore, editar status, busca por ID)
- ✅Contador automático de árvores (atende ao requisito de "contar árvores por projeto")
- ✅ Menu principal e submenu de detalhes funcionais

---

## ❌ Faltam (20-25%):

### 1. Relatório e Cruzamento de dados  (~10%)
- [ ] Relatório geral (total de projetos, total de árvores, plantadas *vs* não plantadas)
- [ ] Identificar espécies repetidas em múltiplos projetos


### 2. Persistência de dados (~10-15%)
- [ ] Salvar toda a estrutura em arquivo `.txt` ou `.dat`
- [ ] Carregar dados no início do programa
- [ ] **Lidar com:**
  - Formato do arquivo (CSV, texto estruturado ou binário)
  - Reconstruir ponteiros ao carregar
  - Validação de Atualização incremental vs reescrita total

# Requitos do Trabalho

# 📄 Estrutura do Relatório

O relatório deve conter as seguintes seções:

* **Introdução:** Explicação de como foi compreendido o problema, como a solução foi desenhada, que estruturas de dados foram utilizadas e como o problema foi resolvido.
* **Documentação do código:** Explicação detalhada das funções implementadas, com a descrição de como cada função foi construída e seu propósito no funcionamento geral das listas. É necessário que as funções básicas de inclusão, busca e remoção estejam presentes e além das básicas, funções adicionais (favoritar um item, gerar relatório geral, etc). 
* **Exemplos de uso:** Demonstração de algumas operações feitas pela lista, com exemplos de código, entrada de dados e as saídas obtidas. 
* **Conclusão:** Reflexão sobre os desafios enfrentados durante a implementação e as principais lições aprendidas.

---

# 🌳 Tema 2 – Projeto de Reflorestamento

### 🧱 Estrutura de Dados
* Lista duplamente ligada de **Projetos**.
* Cada projeto possui uma lista duplamente ligada de **Árvores**.

### ⚙️ Funções Básicas
* [x] Cadastrar projeto
* [x] Remover projeto
* [x] Listar projetos
* [x] Cadastrar árvore em um projeto
* [x] Listar árvores de um projeto

### ➕ Funções Extras (Exemplos)
* [x] Contar árvores por projeto (exemplo)
* [ ] Listar árvores por espécie (exemplo)
* [x] Remover árvore (proposta pela aluna)
* [x] Editar status da árvore (proposta pela aluna)
* [x] Buscar projeto por ID (proposta pela aluna)


### 🔀 Cruzamento de Dados (Exemplos)
* [ ] Identificar espécies de árvores em mais de um projeto
* [ ] Calcular o total de árvores plantadas