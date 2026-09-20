// ===========================================================================
//  SISTEMA DE GERENCIAMENTO DE BIBLIOTECA - PARTE 3
//
//  OBJETIVO DESTA PARTE:
//  Modularizar o código com funções especializadas, aplicando boas práticas.
//  - Passagens por valor (para exibição) e por referência (para modificação).
//  - Funções para cada funcionalidade principal do sistema.
//  - Função main() se torna um "orquestrador", chamando as outras.
// ===========================================================================

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LIVROS 50
#define TAM_STRING 100
#define MAX_EMPRESTIMOS 50

struct Livros {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel;
};

struct Emprestimos {
    int indiceLivro;
    char nomeUsuario[TAM_STRING];
};

void limparBufferEntrada(void);
void exibirMenu(void);
void cadastrarLivros(struct Livros *biblioteca, int *totalLivros);
void listarLivros(const struct Livros *biblioteca, int totalLivros);
void realizarEmprestimo(struct Livros *biblioteca, int totalLivros, struct Emprestimos *emprestimos, int *totalEmprestimos);
void listarEmprestimos(const struct Livros *biblioteca, const struct Emprestimos *emprestimos, int totalEmprestimos);
void liberarMemoria(struct Livros *biblioteca, struct Emprestimos *emprestimos);

int main(void) {
    struct Livros *biblioteca = calloc(MAX_LIVROS, sizeof(struct Livros));
    struct Emprestimos *emprestimos = malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimos));
    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao = 0;

    if (biblioteca == NULL || emprestimos == NULL) {
        printf("Erro: Falha ao alocar memoria.\n");
        return 1;
    }

    do {
        exibirMenu();
        scanf("%d", &opcao);
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
            case 0:
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpcao invalida! Pressione Enter para tentar novamente. ");
                getchar();
                break;
        }
    } while (opcao != 0);

    liberarMemoria(biblioteca, emprestimos);
    return 0;
}

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void exibirMenu(void) {
    printf("===================================\n");
    printf("    BIBLIOTECA - PARTE 3\n");
    printf("===================================\n");
    printf("1 - Cadastrar Livro\n");
    printf("2 - Listar Livros\n");
    printf("3 - Realizar Emprestimo\n");
    printf("4 - Listar Emprestimos\n");
    printf("0 - Sair\n");
    printf("------------------------------------\n");
    printf("Escolha uma opcao: ");
}

void cadastrarLivros(struct Livros *biblioteca, int *totalLivros) {
    if (*totalLivros >= MAX_LIVROS) {
        printf("Biblioteca cheia!\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    printf("Digite o nome do livro: ");
    fgets(biblioteca[*totalLivros].nome, TAM_STRING, stdin);
    printf("Digite o autor: ");
    fgets(biblioteca[*totalLivros].autor, TAM_STRING, stdin);
    printf("Digite a editora: ");
    fgets(biblioteca[*totalLivros].editora, TAM_STRING, stdin);
    printf("Digite a edicao: ");
    scanf("%d", &biblioteca[*totalLivros].edicao);
    limparBufferEntrada();

    biblioteca[*totalLivros].nome[strcspn(biblioteca[*totalLivros].nome, "\n")] = '\0';
    biblioteca[*totalLivros].autor[strcspn(biblioteca[*totalLivros].autor, "\n")] = '\0';
    biblioteca[*totalLivros].editora[strcspn(biblioteca[*totalLivros].editora, "\n")] = '\0';
    biblioteca[*totalLivros].disponivel = 1;

    (*totalLivros)++;
    printf("\nLivro cadastrado com sucesso!\n");
    printf("\nPressione Enter para continuar...");
    getchar();
}

void listarLivros(const struct Livros *biblioteca, int totalLivros) {
    printf("--- Lista de Livros Cadastrados ---\n\n");

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
    int indice;

    if (totalLivros == 0) {
        printf("Nenhum livro cadastrado para emprestar.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    printf("Livros disponiveis:\n");
    for (int i = 0; i < totalLivros; i++) {
        printf("%d - %s (%s)\n", i, biblioteca[i].nome,
               biblioteca[i].disponivel ? "Disponivel" : "Emprestado");
    }

    printf("Escolha o livro para emprestimo: ");
    scanf("%d", &indice);
    limparBufferEntrada();

    if (indice < 0 || indice >= totalLivros) {
        printf("Indice invalido!\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    if (!biblioteca[indice].disponivel) {
        printf("Este livro ja esta emprestado.\n");
        printf("\nPressione Enter para continuar...");
        getchar();
        return;
    }

    printf("Digite o nome do usuario: ");
    fgets(emprestimos[*totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
    emprestimos[*totalEmprestimos].nomeUsuario[strcspn(emprestimos[*totalEmprestimos].nomeUsuario, "\n")] = '\0';
    emprestimos[*totalEmprestimos].indiceLivro = indice;

    biblioteca[indice].disponivel = 0;
    (*totalEmprestimos)++;

    printf("Emprestimo realizado com sucesso!\n");
    printf("\nPressione Enter para continuar...");
    getchar();
}

void listarEmprestimos(const struct Livros *biblioteca, const struct Emprestimos *emprestimos, int totalEmprestimos) {
    printf("--- Lista de Emprestimos ---\n\n");

    if (totalEmprestimos == 0) {
        printf("Nenhum emprestimo realizado.\n");
    } else {
        for (int i = 0; i < totalEmprestimos; i++) {
            printf("Emprestimo %d\n", i + 1);
            printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
            printf("Livro: %s\n", biblioteca[emprestimos[i].indiceLivro].nome);
        }
    }

    printf("\nPressione Enter para continuar...");
    getchar();
}

void liberarMemoria(struct Livros *biblioteca, struct Emprestimos *emprestimos) {
    free(biblioteca);
    free(emprestimos);
    
}
