
#include <stdio.h>
#include <string.h>// Para strucspn
#include <stdlib.h>

// --- Constantes globais ---
#define MAX_LIVROS 50
#define TAM_STRING 100
#define MAX_EMPRESTIMOS 50

//--- Definição da Estrutura ---
// struct Livros agora tem um campo 'disponével' para indicar se o livro está disponível ou não.
struct Livros {
    char nome[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int edicao;
    int disponivel; // 1 para disponível, 0 para não disponível.
};

// Nova struct para armazenar informações de empréstimos
struct Emprestimos {
     int indiceLivro; // Para saber qual livro do array 'biblioteca'esta emprestado
     char nomeUsuario[TAM_STRING];
};

// --- Função para limpar o buffer de entrada ---
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
 
// --- Função Principal (main) ---

int main() {
  // 1. ALOCAÇÃO DINÂMICA DE MEMÓRIA
  // Agora, ao em vez de arrays estáticos, usamos ponteiro.
 struct Livros *biblioteca;
 struct Emprestimos *emprestimos;

 // Usamos calloc para o array de livros. calloc(num_elementos, tamanho_elemento) 
 // Vantagem: Inicializa a memória alocada com zero, o que é útil para o campo 'disponível'.
    biblioteca = (struct Livros*) calloc(MAX_LIVROS, sizeof(struct Livros));

// Usando malloc para o array de empréstimos. malloc(tamanho_de_cada_elemento)
// Vantagem: inicializar toda a memória com zero. Isso siginifica que 'disponivel' começa como 0 (não disponível) para todos os livros.
    emprestimos = (struct Emprestimos*) malloc(MAX_EMPRESTIMOS * sizeof(struct Emprestimos));

// VERIFICAÇÃO: É crurcial verificar se a alocação de memória foi bem-sucedida.
 if (biblioteca == NULL || emprestimos == NULL ) {
    printf ("Erro: Falha ao alocar momoria.\n");
    return 1; // Retorna 1 para indicar um erro na execução do programa.
 }   


    int totalLivros = 0;
    int totalEmprestimos = 0;
    int opcao;
   
// --- Laço Pricipal do Menu ---
do{

    // ---Exibir Menu de Opções ---
    printf("======================================\n");
    printf("    BIBLIOTECA - PARTE 1\n");
    printf("======================================\n");
    printf("1 - Cadastrar Livro\n");
    printf("2 - Listar Livros\n");
    printf("3 - Realizar Emprestimo\n");
    printf("4 - Listar Emprestimos\n");
    printf("0 - Sair\n");
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

               biblioteca[totalLivros].disponivel = 1;

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
          
        case 3: // realizar Emprestimos 
        printf ("--- Realizar Emprestimo ---\n");
             
        if (totalEmprestimos >= MAX_EMPRESTIMOS) {
            printf("Limite de emprestimos atingido!.\n");
        } else {
            printf ("Livros disponiveis para emprestimo:\n");
            int disponiveis = 0;
            for (int i = 0; i < totalLivros; i++){
                if (biblioteca[i].disponivel){
                    printf("%d - %s\n", i + 1, biblioteca[i].nome);
                    disponiveis++;
                }
            }
            if (disponiveis == 0){
                printf ("Nenhum livrio disponivel para emprestimo.\n");
            } else {
                printf ("\nDigite o numero do livros que deseja emprestar: ");
                int numLivros;
                scanf("%d", &numLivros);
                limparBufferEntrada();

               int indice = numLivros - 1; //convertendo para índice do array
                
               // Validação da escolha do usuário.
               if (indice >= 0 && indice < totalLivros && biblioteca[indice].disponivel){
                printf ("Digite o nome do usuario que esta realizando o emprestimo: ");
                fgets(emprestimos[totalEmprestimos].nomeUsuario, TAM_STRING, stdin);
                emprestimos[totalEmprestimos].nomeUsuario[strcspn(emprestimos[totalEmprestimos].nomeUsuario, "\n")] = 0; // Remove o '\n' do final da string
                
                // Registrar o empréstimo
                emprestimos[totalEmprestimos].indiceLivro = indice;
            
                // Atualiza o status do livro para não disponível
                biblioteca[indice].disponivel = 0;

                totalEmprestimos++;
                printf("\nEmprestimo realizado com sucesso!\n");
                } else {
                    printf("\nOpcao invalida ou livro indisponivel!\n");

            

                }
            }

        }   
        printf("\nPressione Enter para continuar...");
        getchar();
        break;
        
    case 4: // Listar Emprestimos
        printf("--- Listagem de Emprestimos ---\n\n");  
        if (totalEmprestimos == 0) {
            printf("Nenhum emprestimo realizado ainda.\n");
        } else {
            for (int i = 0; i< totalEmprestimos; i++){
                printf("\n=========================================\n");
                printf("\nEmprestimo #%d\n", i + 1);
                printf("Livro: %s\n", biblioteca[emprestimos[i].indiceLivro].nome);
                printf("Usuario: %s\n", emprestimos[i].nomeUsuario);
            }
            printf("\n=========================================\n");
        }
        printf("\nPressione Enter para continuar...");
        getchar();
        break;

    case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
    }
} while(opcao != 0);

// --- Liberação de Memória ---
// É ESSENCIAL libera a memória alocada, antesa de terminar o programar.
// Isso evitar vazamentos de memória e garantir que o programa seja eficiente, "memory leaks".
    free(emprestimos);
    free(biblioteca);
    // Mensagem de confirmação visual para o usuário
    printf("\n=========================================\n");
    printf(" Memoria liberada com sucesso!\n");
    printf(" Programa encerrado.\n");
    printf("=========================================\n");

    return 0;
}