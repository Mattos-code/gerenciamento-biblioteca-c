//===========================================================================================
//SISTEMA DE BIBLIOTECAN - PARTE 1
//
//OBJETIVO DESTA PARTE : 
//Implementar o cadastro e a listagem de livros usando um arrays estaticos.
//Foco emn structs, entrada e saída de dados e uma organização básica.

//===========================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>// Para strucspn

// --- Constantes globais ---
#define MAX_LIVROS 50
#define TAM_STRING 100

// Definição da Estrutura (struct) para armazenar informações de um livro  
typedef struct {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
} Livro;

// --- Função para limpar o buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
 
// --- Função Principal (main) ---

int main() {
    Livro biblioteca[MAX_LIVROS];
    int totalLivros = 0;
    int opcao;

// --- Laço Pricipal do Menu ---
do{

    // ---Exibir Menu de Opções ---
    printf("======================================\n");
    printf("    BIBLIOTECA - PARTE 1\n");
    printf("======================================\n");
    printf("1 - Cadastrar Livro\n");
    printf("2 - Listar Livros\n");
    printf("3 - Sair\n");
    printf("---------------------------------------\n");
    printf("Escolha uma opcao: ");

    // --- Lê opção do usuário ---
    scanf("%d", &opcao);
    limparBufferEntrada(); // Limpa o buffer do teclado
          
    // --- Processamento da opção ---
    switch(opcao) {
        case 1:// Cadastrar de Livro
        printf("--- Cadastro de Novo Livro ---\n");
            if(totalLivros < MAX_LIVROS) {
                printf("Digite o nome do livro: ");
                fgets(biblioteca[totalLivros].nome, TAM_STRING, stdin);
               
                printf("Digite o autor: ");
                fgets(biblioteca[totalLivros].autor, TAM_STRING, stdin);
                
                printf("Digite a editora: ");
                fgets(biblioteca[totalLivros].editora, TAM_STRING, stdin);
               
                biblioteca[totalLivros].nome[strcspn(biblioteca[totalLivros].nome, "\n")] = 0; 
                biblioteca[totalLivros].autor[strcspn(biblioteca[totalLivros].autor, "\n")] = 0;
                biblioteca[totalLivros].editora[strcspn(biblioteca[totalLivros].editora, "\n")] = 0;

               printf("Digite a edicao: ");
               scanf("%d", &biblioteca[totalLivros].edicao);
               limparBufferEntrada(); 

                totalLivros++;
                 printf("\nLivro cadastrado com sucesso!\n");
            } else {
                printf("\nBiblioteca cheia! Nao é possivel cadastrar mais livros.\n");
            }
            
            printf("\nPressione Enter para continuar...");
            getchar(); // pausa para o usuário ler a mensagem antes de voltar ao menu
            break;

        case 2:// LIstagem de Livros
            printf("--- Listagem de Livros Cadastrados ---\n\n"); 
            if(totalLivros == 0) {
                printf("Nenhum livro cadastrado ainda.\n");
            } else {
                printf("\n=========================================\n");
                printf("           LIVROS CADASTRADOS            \n");
                printf("=========================================\n");
                for(int i = 0; i < totalLivros; i++) {
                    printf("\nLivro #%d\n", i + 1);
                    printf("Titulo: %s\n", biblioteca[i].nome);
                    printf("Autor: %s\n", biblioteca[i].autor);
                    printf("Editora: %s\n", biblioteca[i].editora);
                    printf("Edicao: %d\n", biblioteca[i].edicao);
                }
            }
            printf("\nPressione Enter para continuar...");
            getchar(); 
            break;
        case 3:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
    }
} while(opcao != 3);

    return 0;
}