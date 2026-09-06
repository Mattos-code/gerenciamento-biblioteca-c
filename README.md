# 📚 Sistema de Biblioteca em C

Projeto desenvolvido para aplicar conceitos fundamentais da linguagem C, evoluindo de estruturas de dados estáticas até a alocação dinâmica de memória e modularização de funcionalidades.

---

## 📌 Histórico de Desenvolvimento

### 🔴 Parte 1 - Versão 1.0 (Concluída)
* **Objetivo:** Implementar o cadastro e a listagem de livros usando arrays estáticos.
* **Foco do Módulo:** Declaração de `structs`, manipulando entradas e saídas de dados no terminal e organização inicial do fluxo.
* **Detalhes da Estrutura:** Criação de uma `struct` para armazenar informações do livro (nome, autor, editora e edição).

### 🟡 Parte 2 - Incrementos e Memória (Concluída)
* **Módulo de Empréstimos:** Implementação de funções para realizar e consultar empréstimos de livros por usuário.
* **Gerenciamento Dinâmico de Memória:** Uso de ponteiros e alocação dinâmica com `malloc()` e `calloc()`.
* **Desalocação Consciente:** Liberação adequada de memória com `free()` ao encerrar o sistema.

---

## 🛠️ Como Executar o Projeto

1. Compilar o arquivo principal no terminal:
   ```bash
   gcc main.c -o biblioteca