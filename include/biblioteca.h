#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

// Constantes globais do sistema
#define MAX_LIVROS 50
#define TAM_STRING 100
#define MAX_EMPRESTIMOS 50

// Estrutura para armazenar os dados de cada livro
struct Livros {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 = Disponível, 0 = Emprestado
};

// Estrutura para armazenar o registro de empréstimos
struct Emprestimos {
    int indiceLivro;              // Guarda a posição do livro na biblioteca
    char nomeUsuario[TAM_STRING]; // Nome da pessoa que pegou o livro
};

// Protótipos das funções
void limparBufferEntrada(void);
void exibirMenu(void);
void cadastrarLivros(struct Livros *biblioteca, int *totalLivros);
void listarLivros(const struct Livros *biblioteca, int totalLivros);
void realizarEmprestimo(struct Livros *biblioteca, int totalLivros, struct Emprestimos *emprestimos, int *totalEmprestimos);
void listarEmprestimos(const struct Livros *biblioteca, const struct Emprestimos *emprestimos, int totalEmprestimos);

// NOVO: Protótipo da função de devolução com tratamento de erros
void devolverLivro(struct Livros *biblioteca, int totalLivros, struct Emprestimos *emprestimos, int *totalEmprestimos);

void liberarMemoria(struct Livros *biblioteca, struct Emprestimos *emprestimos);

#endif