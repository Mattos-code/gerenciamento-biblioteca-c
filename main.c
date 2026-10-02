#include <stdio.h>
#include <stdlib.h>
#include "biblioteca.h"

int main(void) {
    // Alocação dinâmica de memória para a biblioteca e os empréstimos
    struct Livros *biblioteca = calloc(MAX_LIVROS, sizeof(struct Livros));
    struct Emprestimos *emprestimos = malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimos));
    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao = 0;

    // Validação da alocação de memória
    if (biblioteca == NULL || emprestimos == NULL) {
        printf("[ERRO] Falha ao alocar memoria para a biblioteca ou emprestimos.\n");
        return 1;
    }

    do {
        exibirMenu();

        // Tratamento de erro na leitura da opção do menu
        if (scanf("%d", &opcao) != 1) {
            opcao = -1; // Força ceder ao caso padrão (default)
        }
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarLivros(biblioteca, &totalLivros);
                break;
            case 2:
                listarLivros(biblioteca, totalLivros);
                break;
            case 3:
                realizarEmprestimo(biblioteca, totalLivros, emprestimos, &totalEmprestimos);
                break;
            case 4:
                listarEmprestimos(biblioteca, emprestimos, totalEmprestimos);
                break;
            case 5:
                // Chamada da nova funcionalidade de devolução de livros
                devolverLivro(biblioteca, totalLivros, emprestimos, &totalEmprestimos);
                break;
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida! Pressione Enter para tentar novamente. ");
                getchar();
                break;
        }
    } while (opcao != 0);

    // Libera a memória alocada dinamicamente ao sair do programa
    liberarMemoria(biblioteca, emprestimos);
    return 0;
}