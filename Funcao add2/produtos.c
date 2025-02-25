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
    FILE *arquivo = fopen("teste.c", "rb+");

    if (arquivo == NULL) {
        // Se o arquivo não existir, cria-o
        arquivo = fopen("teste.c", "wb+");
        if (arquivo == NULL) {
            printf("Erro ao criar o arquivo.\n");
            return;
        }
    }

    Produto temp;
    int ultimo_id = 0;
    while (fread(&temp, sizeof(Produto), 1, arquivo) == 1) {
        ultimo_id = temp.id;
    }
    novo.id = ultimo_id + 1;

    printf("Digite o nome do produto (Ate 50 caracteres): ");
    scanf(" %50[^\n]", novo.nome);

    printf("Digite o preco do produto: ");
    scanf("%f", &novo.preco);

    printf("Digite a quantidade de produtos que vao entrar no estoque: ");
    scanf("%d", &novo.quant_estoque);

    fseek(arquivo, 0, SEEK_END);
    fwrite(&novo, sizeof(Produto), 1, arquivo);

    fclose(arquivo);
    printf("Produto cadastrado com ID %d.\n", novo.id);
}

void imprimir(void) {
    FILE *arquivo = fopen("teste.c", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de produtos.\n");
        return;
    }

    Produto produto;
    int encontrou = 0;

    printf("\n=== Lista de Produtos ===\n");
    while (fread(&produto, sizeof(Produto), 1, arquivo) == 1) {
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
