#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100 // Limite maximo de produtos

typedef struct {
    int id;
    char nome[50];
    float preco;
    int quantidade;
} Produto;


Produto produtos[MAX_PRODUTOS]; // Lista de produtos
int totalProdutos = 0; // Contador de produtos cadastrados

// Função para salvar produtos no arquivo
//talvez seja uma boa fazer essa funções aq, vai dar menos trabalho nas funções de add e remover
void salvarEmArquivo() {
    FILE *arquivo = fopen("produtos.txt", "w"); // Abrir em modo de escrita
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (int i = 0; i < totalProdutos; i++) {
        fprintf(arquivo, "%d %s %.2f %d\n", 
                produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }

    fclose(arquivo); // Fechar o arquivo
}

// Função para carregar produtos do arquivo
void carregarDeArquivo() {
    FILE *arquivo = fopen("produtos.txt", "r"); // Abrir em modo de leitura
    if (arquivo == NULL) {
        printf("Nenhum produto encontrado. Criando novo arquivo...\n");
        return;
    }

    totalProdutos = 0; // Zerar a contagem antes de carregar
    while (fscanf(arquivo, "%d %49s %f %d", 
                  &produtos[totalProdutos].id, produtos[totalProdutos].nome, 
                  &produtos[totalProdutos].preco, &produtos[totalProdutos].quantidade) != EOF) {
        totalProdutos++;
    }

    fclose(arquivo);
}

// Função para adicionar um produto
void adicionarProduto() {
    if (totalProdutos >= MAX_PRODUTOS) {
        printf("Limite de produtos atingido!\n");
        return;
    }

    Produto novo;
    printf("ID do produto: ");
    scanf("%d", &novo.id);
    printf("Nome do produto: ");
    scanf("%s", &novo.nome);
    printf("Preço: ");
    scanf("%f", &novo.preco);
    printf("Quantidade em estoque: ");
    scanf("%d", &novo.quantidade);

    produtos[totalProdutos++] = novo; // Adicionar à lista
    salvarEmArquivo(); // Salvar no arquivo

    printf("Produto cadastrado com sucesso!\n");
}

// Função para listar produtos
void listarProdutos() {
    if (totalProdutos == 0) {
        printf("Nenhum produto cadastrado!\n");
        return;
    }

    printf("\n=== Lista de Produtos ===\n");
    for (int i = 0; i < totalProdutos; i++) {
        printf("ID: %d | Nome: %s | Preço: R$%.2f | Quantidade: %d\n",
               produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
    }
}

// Menu principal
void menu() {
    int opcao;
    do {
        printf("\n=== Gerenciador de Produtos ===\n");
        printf("1. Adicionar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarProduto();
                break;
            case 2:
                listarProdutos();
                break;
            case 3:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 3);
}

// Função principal
int main() {
    carregarDeArquivo(); // Carregar dados salvos(obs: essa função vai ser feita?)
    menu(); // Iniciar menu
    return 0;
}
