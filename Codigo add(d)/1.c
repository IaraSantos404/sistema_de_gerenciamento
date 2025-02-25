#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produto {
    int id;
    char nome[51];
    float preco;
    int quant_estoque;
} Produto;

void add(void) {
    Produto novo;
    FILE *arquivo = fopen("teste.txt", "a");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Produto temp;
    int ultimo_id = 0;

    // Procurando o último ID já cadastrado
    FILE *arquivo_leitura = fopen("teste.txt", "r");
    if (arquivo_leitura != NULL) {
        while (fscanf(arquivo_leitura, "%d\t%50[^\t]\t%f\t%d\n", &temp.id, temp.nome, &temp.preco, &temp.quant_estoque) != EOF) {
            ultimo_id = temp.id;
        }
        fclose(arquivo_leitura);
    }

    novo.id = ultimo_id + 1;

    printf("Digite o nome do produto (Até 50 caracteres): ");
    scanf(" %50[^\n]", novo.nome);

    printf("Digite o preco do produto: ");
    scanf("%f", &novo.preco);

    printf("Digite a quantidade de produtos que vao entrar no estoque: ");
    scanf("%d", &novo.quant_estoque);

    // Salvando os dados no arquivo no formato de banco de dados
    fprintf(arquivo, "%d\t%s\t%.2f\t%d\n", novo.id, novo.nome, novo.preco, novo.quant_estoque);

    fclose(arquivo);
    printf("Produto cadastrado com ID %d.\n", novo.id);
}

void imprimir(void) {
    FILE *arquivo = fopen("teste.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }

    Produto produto;
    int encontrou = 0;

    printf("\n=== Lista de Produtos ===\n");
    while (fscanf(arquivo, "%d\t%50[^\t]\t%f\t%d\n", &produto.id, produto.nome, &produto.preco, &produto.quant_estoque) != EOF) {
        encontrou = 1;
        printf("ID: %d\n", produto.id);
        printf("Nome: %s\n", produto.nome);
        printf("Preco: %.2f\n", produto.preco);
        printf("Quantidade no Estoque: %d\n", produto.quant_estoque);
        printf("--------------------------\n");
    }

    if (!encontrou) {
        printf("Nenhum produto encontrado.\n");
    }

    fclose(arquivo);
}

int main(void) {
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1 - Adicionar produto\n");
        printf("2 - Imprimir produtos\n");
        printf("3 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                add();
                break;
            case 2:
                imprimir();
                break;
            case 3:
                printf("Encerrando...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 3);

    return 0;
}
