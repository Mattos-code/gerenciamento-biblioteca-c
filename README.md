# 📚 Sistema de Gerenciamento de Biblioteca em C — Versão 3 (Parte 3)

Este repositório contém a evolução do **Sistema de Gerenciamento de Biblioteca** desenvolvido em C. O projeto transicionou de uma estrutura monolítica inicial para uma **arquitetura modularizada dividida em subpastas**, aplicando boas práticas de separação de responsabilidades (interface, definições de tipos e regras de negócio).

---

## 🔄 Evolução da Modelagem: Anterior vs. Atual (Versão 3)

### 1. Estrutura de Arquivos e Subpastas
* **Versão Anterior:** O projeto contava com código-fonte, definições de estruturas e funções centralizadas sem modularização por diretórios.
* **Versão Atual (Parte 3):** O sistema foi refatorado e dividido estrategicamente nas subpastas `include/` e `src/`:

├── include/
│   └── biblioteca.h       # Protótipos das funções, constantes e structs
├── src/
│   ├── biblioteca.c       # Implementação das regras de negócio e validações
│   └── main.c             # Ponto de entrada, menu interativo e alocação dinâmica
└── README.md

### 2. Quadro Comparativo das Implementações

| Funcionalidade / Aspecto | Versões Anteriores | Versão 3 (Atual) |
| :--- | :--- | :--- |
| **Arquitetura** | Monolítica / Arquivo Único | Modularizada por subpastas (`include/` e `src/`) |
| **Headers e Definições** | Inclusões diretas | Centralizado em `biblioteca.h` com *Include Guards* |
| **Gerenciamento de Memória** | Alocação simples | Alocação dinâmica com `calloc`/`malloc` e desalocação com `liberarMemoria()` |
| **Tratamento de Erros** | Validações básicas de entrada | Tratamento defensivo com `scanf`, limpeza de buffer e checagem de ponteiros (`NULL`) |
| **Devolução de Livros** | Não disponível | Função `devolverLivro()` com reorganização dinâmica de vetores (*array shift*) |

---
🚀 Compilação e Execução
Pré-requisitos
Compilador GCC instalado.

Comando de Compilação
Para compilar o projeto considerando as subpastas include/ e src/, execute na raiz do diretório:

Bash
# Compilação unificando as subpastas
gcc -Iinclude src/main.c src/biblioteca.c -o biblioteca_app

# Executar no Linux / macOS
./biblioteca_app

# Executar no Windows
.\biblioteca_app.exe
📌 Funcionalidades do Menu
Cadastrar Livro: Leitura de dados cadastrais com tratamento de estouro de capacidade (MAX_LIVROS).

Listar Livros: Exibição do acervo com status de disponibilidade (Disponível / Emprestado).

Realizar Empréstimo: Associação de usuário a livro com alteração de status.

Listar Empréstimos: Exibição detalhada de transações ativas.

Devolver Livro (NOVO): Baixa no empréstimo, alteração de status do livro e ajuste no vetor.

Sair: Desalocação segura da memória dinâmica alocada via free().
---

## 🛠️ Principais Destaques do Código (Parte 3)

### 1. Modularização e Header Guard (`biblioteca.h`)
* Uso de `#ifndef BIBLIOTECA_H` para evitar redefinições em tempo de compilação.
* Estruturas de dados unificadas: `struct Livros` e `struct Emprestimos`.

### 2. Tratamento Defensivo na Devolução (`devolverLivro`)
* **Verificação de Ponteiros:** Previne erros de falha de segmentação (*Segmentation Fault*) checando se referências são nulas.
* **Limpeza do Buffer:** Evita loops infinitos ao sanitizar entradas do usuário via `limparBufferEntrada()`.
* **Reorganização de Array:** Ao devolver um livro, os registros posteriores no vetor são deslocados para preencher a lacuna:
  ```c
  for (int i = escolha; i < (*totalEmprestimos) - 1; i++) {
      emprestimos[i] = emprestimos[i + 1];
  }
