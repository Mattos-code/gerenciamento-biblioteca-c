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
### 🟢 Parte 3 - Modularização e Correções (Concluída)
* **Objetivo:** Melhorar a arquitetura do sistema, tornando o código mais organizado, legível e sustentável.
* **Foco do Módulo:** Separação de responsabilidades em funções especializadas para cadastro, listagem, empréstimos, menu e gerenciamento de memória.
* **Detalhes da Estrutura:** Organização do fluxo principal na função `main()`, uso de protótipos e passagem de parâmetros por referência e por valor.
* **Incrementos:** Melhorias na estrutura do programa, padronização das operações e redução de redundâncias no código.
* **Correções aplicadas:** Ajuste de protótipos, eliminação de chaves sobrando, correção de erros de sintaxe e resolução do typo `prinf` para `printf`.
* **Validação:** O programa foi compilado com sucesso usando `gcc`, confirmando que a versão está estável e funcional.
---

1. Compilar o arquivo principal no terminal:
   ```bash
   gcc main.c -o biblioteca
