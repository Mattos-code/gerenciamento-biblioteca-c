#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca.h"

// Função utilitária estática para remover o \n do final das strings lidas via fgets
static void removerQuebraLinha(char *str) {
    if (str != NULL) {
        str[strcspn(str, "\n")] = '\0';
    }
}

// Limpa o buffer do teclado para evitar resíduos ao alternar entre scanf e fgets
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

// Exibe o menu interativo com a nova opção de devolução
void exibirMenu(void) {
    printf("\n===================================\n");
    printf("     BIBLIOTECA - PARTE 3\n");
    printf("===================================\n");
    printf("1 - Cadastrar Livro\n");
    printf("2 - Listar Livros\n");
    printf("3 - Realizar Emprestimo\n");
    printf("4 - Listar Emprestimos\n");
    printf("5 - Devolver Livro (NOVO)\n");
    printf("0 - Sair\n");
    printf("------------------------------------\n");
    printf("Escolha uma opcao: ");
}

void cadastrarLivros(struct Livros *biblioteca, int *totalLivros) {
    if (biblioteca == NULL || totalLivros == NULL) return;

    if (*totalLivros >= MAX_LIVROS) {
        printf("\n[ERRO] Capacidade maxima da biblioteca atingida (%d livros)!\n", MAX_LIVROS);
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    printf("Digite o nome do livro: ");
    if (fgets(biblioteca[*totalLivros].nome, TAM_STRING, stdin) == NULL) return;
    removerQuebraLinha(biblioteca[*totalLivros].nome);

    printf("Digite o autor: ");
    if (fgets(biblioteca[*totalLivros].autor, TAM_STRING, stdin) == NULL) return;
    removerQuebraLinha(biblioteca[*totalLivros].autor);

    printf("Digite a editora: ");
    if (fgets(biblioteca[*totalLivros].editora, TAM_STRING, stdin) == NULL) return;
    removerQuebraLinha(biblioteca[*totalLivros].editora);

    printf("Digite a edicao: ");
    while (scanf("%d", &biblioteca[*totalLivros].edicao) != 1 || biblioteca[*totalLivros].edicao <= 0) {
        limparBufferEntrada();
        printf("[ERRO] Edicao invalida! Digite um numero inteiro positivo: ");
    }
    limparBufferEntrada();

    biblioteca[*totalLivros].disponivel = 1;
    (*totalLivros)++;

    printf("\nLivro cadastrado com sucesso!\n");
    printf("\nPressione Enter para continuar...");
    getchar();
}

void listarLivros(const struct Livros *biblioteca, int totalLivros) {
    if (biblioteca == NULL) return;

    printf("\n--- Lista de Livros Cadastrados ---\n\n");

    if (totalLivros == 0) {
        printf("Nenhum livro cadastrado ainda.\n");
    } else {
        for (int i = 0; i < totalLivros; i++) {
            printf("-----------------------------\n");
            printf("Livro %d\n", i + 1);
            printf("Nome: %s\n", biblioteca[i].nome);
            printf("Autor: %s\n", biblioteca[i].autor);
            printf("Editora: %s\n", biblioteca[i].editora);
            printf("Edicao: %d\n", biblioteca[i].edicao);
            printf("Status: %s\n", biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
        }
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

void realizarEmprestimo(struct Livros *biblioteca, int totalLivros, struct Emprestimos *emprestimos, int *totalEmprestimos) {
    if (biblioteca == NULL || emprestimos == NULL || totalEmprestimos == NULL) return;

    int indice;

    if (*totalEmprestimos >= MAX_EMPRESTIMOS) {
        printf("\n[ERRO] Limite maximo de emprestimos atingido (%d)!\n", MAX_EMPRESTIMOS);
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    if (totalLivros == 0) {
        printf("\n[ERRO] Nenhum livro cadastrado para emprestar.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    printf("\nLivros cadastrados:\n");
    for (int i = 0; i < totalLivros; i++) {
        printf("%d - %s (%s)\n", i, biblioteca[i].nome,
               biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
    }

    printf("\nEscolha o indice do livro para emprestimo: ");
    if (scanf("%d", &indice) != 1) {
        limparBufferEntrada();
        printf("\n[ERRO] Entrada invalida! Digite um numero valido.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    limparBufferEntrada();

    if (indice < 0 || indice >= totalLivros) {
        printf("\n[ERRO] Indice inexistente!\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    if (!biblioteca[indice].disponivel) {
        printf("\n[ERRO] Este livro ja esta emprestado.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    printf("Digite o nome do usuario: ");
    if (fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin) == NULL) return;
    removerQuebraLinha(emprestimos[*totalEmprestimos].nomeUsuario);

    emprestimos[*totalEmprestimos].indiceLivro = indice;
    biblioteca[indice].disponivel = 0;
    (*totalEmprestimos)++;

    printf("\nEmprestimo realizado com sucesso!\n");
    printf("\nPressione Enter para continuar...");
    getchar();
}

void listarEmprestimos(const struct Livros *biblioteca, const struct Emprestimos *emprestimos, int totalEmprestimos) {
    if (biblioteca == NULL || emprestimos == NULL) return;

    printf("\n--- Lista de Emprestimos ---\n\n");

    if (totalEmprestimos == 0) {
        printf("Nenhum emprestimo realizado.\n");
    } else {
        for (int i = 0; i < totalEmprestimos; i++) {
            printf("Emprestimo %d\n", i + 1);
            printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
            printf("Livro: %s\n", biblioteca[emprestimos[i].indiceLivro].nome);
            printf("-----------------------------\n");
        }
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

// ===========================================================================
// NOVO PROCESSO: DEVOLUÇÃO DE LIVROS COM TRATAMENTO COMPLETO DE ERROS
// ===========================================================================
void devolverLivro(struct Livros *biblioteca, int totalLivros, struct Emprestimos *emprestimos, int *totalEmprestimos) {
    // 1. TRATAMENTO DE ERRO DE PONTEIROS NULOS:
    // Garante que nenhuma estrutura recebida por parâmetro seja NULL.
    // Evita crashes e falhas de segmentação (Segmentation Fault).
    if (biblioteca == NULL || emprestimos == NULL || totalEmprestimos == NULL) {
        return;
    }

    if (totalLivros <= 0) {
        printf("\n[ERRO] Nenhum livro cadastrado para devolver.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    // 2. TRATAMENTO DE ERRO DE ESTADO:
    // Mudança em relação ao primeiro código: Antes não existia verificação de empréstimos ativos.
    // Agora validamos se há registros para devolver.
    if (*totalEmprestimos == 0) {
        printf("\n[ERRO] Nao ha nenhum emprestimo ativo no momento para ser devolvido.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    printf("\n--- Devolucao de Livro ---\n");
    printf("Emprestimos ativos:\n");

    // Exibe a lista formatada de empréstimos ativos com o respectivo índice da transação
    for (int i = 0; i < *totalEmprestimos; i++) {
        int idxLivro = emprestimos[i].indiceLivro;
        if (idxLivro < 0 || idxLivro >= totalLivros) {
            printf("[%d] Usuario: %s | Livro: [indice invalido]\n", i, emprestimos[i].nomeUsuario);
            continue;
        }
        printf("[%d] Usuario: %s | Livro: %s\n", i, emprestimos[i].nomeUsuario, biblioteca[idxLivro].nome);
    }

    int escolha;
    printf("\nDigite o numero do emprestimo que deseja encerrar/devolver: ");

    // 3. TRATAMENTO DE ERRO DE ENTRADA INVÁLIDA (LETRAS/CARACTERES):
    // Verificamos se a leitura do scanf retornou 1 (indica que um inteiro foi lido com sucesso).
    // Se o usuário digitar texto ou letras, o erro é capturado e limpa o buffer do teclado.
    if (scanf("%d", &escolha) != 1) {
        limparBufferEntrada();
        printf("\n[ERRO] Entrada invalida! Voce deve digitar um numero referente ao indice do emprestimo.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }
    limparBufferEntrada();

    // 4. TRATAMENTO DE ERRO DE LIMITES (BOUNDS CHECKING):
    // Garante que o usuário forneça um índice dentro dos limites atuais do vetor de empréstimos (0 até *totalEmprestimos - 1).
    if (escolha < 0 || escolha >= *totalEmprestimos) {
        printf("\n[ERRO] Indice invalido! Escolha um numero correspondente aos emprestimos listados acima.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    // 5. ATUALIZAÇÃO DO STATUS DO LIVRO:
    // Mudança importante: Acessamos o livro vinculado ao empréstimo e alteramos sua flag 'disponivel' para 1.
    // Isso torna o livro visível novamente para novos empréstimos na função realizarEmprestimo.
    int indiceLivroParaDevolver = emprestimos[escolha].indiceLivro;
    if (indiceLivroParaDevolver < 0 || indiceLivroParaDevolver >= totalLivros) {
        printf("\n[ERRO] Registro de emprestimo invalido para um livro cadastrado.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    biblioteca[indiceLivroParaDevolver].disponivel = 1;

    // 6. REORGANIZAÇÃO DE MEMÓRIA DO VETOR (DESLOCAMENTO DE ARRAY):
    // Mudança importante em relação à versão inicial: Ao remover um item do meio do array,
    // é necessário puxar os elementos posteriores uma posição para trás para cobrir o "buraco".
    for (int i = escolha; i < (*totalEmprestimos) - 1; i++) {
        emprestimos[i] = emprestimos[i + 1];
    }

    // Decrementa o ponteiro que rastreia o total de empréstimos ativos
    (*totalEmprestimos)--;

    printf("\n[SUCESSO] Livro \"%s\" devolvido com sucesso!\n", biblioteca[indiceLivroParaDevolver].nome);
    printf("\nPressione Enter para continuar...");
    getchar();
}

void liberarMemoria(struct Livros *biblioteca, struct Emprestimos *emprestimos) {
    free(biblioteca);
    free(emprestimos);
}