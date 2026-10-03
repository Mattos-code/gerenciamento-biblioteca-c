# 📚 Sistema de Biblioteca em C

Projeto desenvolvido para aplicar conceitos fundamentais da linguagem C, evoluindo progressivamente de estruturas estáticas simples até uma arquitetura modularizada profissional, com gerenciamento dinâmico de memória e tratamento defensivo de exceções.

---

## 📌 Histórico e Evolução do Desenvolvimentos

### 🔴 Parte 1 - Versão Initial 1.0 (Concluída)
* **Objetivo:** Criar a estrutura base do sistema usando registros e entradas simples.
* **Mapeamento:** Implementação de cadastro e listagem de livros.
* **Estrutura:** Uso de `struct` para dados do livro (nome, autor, editora, edição) e manipulação básica de entrada/saída no terminal via array estático.

---

### 🟡 Parte 2 - Incrementos e Memória Dinâmica (Concluída)
* **Módulo de Empréstimos:** Implementação de funções para registrar e consultar empréstimos por usuário.
* **Gerenciamento de Memória:** Transição de arrays fixos para alocação dinâmica com `malloc()` e `calloc()`, utilizando ponteiros.
* **Desalocação Consciente:** Introdução da liberação explícita de memória com `free()` ao encerrar o sistema, prevenindo *memory leaks*.

---

### 🟢 Parte 3 - Refatoração Arquitetural e Tratamento Defensivo (Atual)
* **Objetivo:** Organizar o projeto em padrão de diretórios profissional (`include/` e `src/`) e tornar a aplicação resiliente a falhas do usuário e *runtime errors*.
* **Novas Funcionalidades:** Módulo de **Devolução de Livros (`devolverLivro`)**, reativando o status do acervo e reorganizando os registros em memória.
* **Resiliência e Tratamento de Exceções:**
  * **Proteção contra Ponteiros Nulos (`NULL` Check):** Checagem preventiva em todas as funções para evitar *Segmentation Fault*.
  * **Sanitização de Entradas:** Validação do retorno do `scanf()` com função dedicada (`limparBufferEntrada()`) para impedir loops infinitos com entradas inválidas.
  * **Validação de Limites (*Bounds Checking*):** Controle rigoroso dos índices de vetores e capacidade máxima do sistema.

---

## 🔄 Quadro Comparativo: Versão Anterior vs. Versão 3

| Funcionalidade / Aspecto | Versões Anteriores (1 e 2) | Versão 3 (Atual) |
| :--- | :--- | :--- |
| **Arquitetura de Pastas** | Arquivos na raiz do projeto | Modularizada nas subpastas `include/` e `src/` |
| **Cabeçalhos e Definições** | Inclusões diretas | Centralizado em `biblioteca.h` com *Include Guards* (`#ifndef`) |
| **Gerenciamento de Memória** | Alocação simples/direta | Alocação dinâmica tratada e desalocação centralizada (`liberarMemoria`) |
| **Tratamento de Erros** | Validações básicas de entrada | Programação defensiva: checagem de `NULL`, validação de `scanf` e limpeza de buffer |
| **Devolução de Livros** | Não disponível | Função `devolverLivro()` com reorganização de memória via *array shift* |

---

## 📁 Estrutura do Diretório

```text
.
├── include/
│   └── biblioteca.h    # Protótipos das funções, constantes e structs
├── src/
│   ├── biblioteca.c    # Implementação das regras de negócio e validações
│   └── main.c          # Ponto de entrada, menu interativo e gestão de memória
└── README.md[i + 1];
  }
---
📌 Funcionalidades do Menu
Cadastrar Livro: Leitura cadastral com controle de capacidade (MAX_LIVROS).

Listar Livros: Exibição do acervo com status de disponibilidade (Disponível / Emprestado).

Realizar Empréstimo: Vinculação de usuário ao livro com atualização de status.

Listar Emprestimos: Exibição detalhada das transações ativas.

Devolver Livro (NOVO): Encerramento do empréstimo, liberação do livro e reorganização do vetor (array shift).

Sair: Encerramento seguro da aplicação com liberação da memória dinâmica.

---


🚀 Compilação e Execução
1. Compilação via Terminal (gcc)
Como o projeto agora está dividido entre include/ e src/, informe o diretório de cabeçalho com a flag -I:

Bash
# Compilar o projeto
gcc -Iinclude src/main.c src/biblioteca.c -o biblioteca_app

# Executar no Linux / macOS
./biblioteca_app

# Executar no Windows
.\biblioteca_app.exe
  
